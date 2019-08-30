#include "config.h"

!  Created by Madu Manathunga on 08/07/2019 
!  Copyright 2019 Michigan State University. All rights reserved.
!
!-------------------------------------------------------
!  scfoperator
!-------------------------------------------------------
!  08/07/2019 Madu Manathunga: Reorganized and improved content 
!                             written by previous authors
!  11/14/2010 Yipu Miao: Clean up code with the integration of
!                       some subroutines
!  03/21/2007 Alessandro Genoni: Implemented ECP integral contribution
!                       for operator matrix
!  11/27/2001 Ed Brothers: wrote the original code
!-------------------------------------------------------

subroutine scf_operator(oneElecO, deltaO)
!-------------------------------------------------------
!  The purpose of this subroutine is to form the operator matrix
!  for a full Hartree-Fock/DFT calculation, i.e. the Fock matrix.  The
!  Fock matrix is as follows:  O(I,J) =  F(I,J) = KE(I,J) + IJ attraction
!  to each atom + repulsion_prim
!  with each possible basis  - 1/2 exchange with each
!  possible basis. Note that the Fock matrix is symmetric.
!  This code now also does all the HF energy calculation. Ed.
!-------------------------------------------------------
   use allmod
   implicit none

#ifdef MPI
   include "mpif.h"
#endif
   double precision oneElecO(nbasis,nbasis)
   logical :: deltaO
   integer II,JJ,KK,LL,NBI1,NBI2,NBJ1,NBJ2,NBK1,NBK2,NBL1,NBL2, I, J
   common /hrrstore/II,JJ,KK,LL,NBI1,NBI2,NBJ1,NBJ2,NBK1,NBK2,NBL1,NBL2
#ifdef MPI
   integer ierror
   double precision,allocatable:: temp2d(:,:)
   allocate(temp2d(nbasis,nbasis))
#endif
!-----------------------------------------------------------------
!  Step 1. evaluate 1e integrals
!-----------------------------------------------------------------

#ifdef MPI
   if(master) then
#endif

!  fetch 1e-integral from 1st time
   call copyDMat(oneElecO,quick_qm_struct%o,nbasis)

!  Now calculate kinetic and attraction energy first.
   if (quick_method%printEnergy) call get1eEnergy()

!  Sum the ECP integrals to the partial Fock matrix
   if (quick_method%ecp) call ecpoperator()

#ifdef MPI
   endif
#endif

!  if only calculate operation difference
   if (deltaO) then
!     save density matrix
      call CopyDMat(quick_qm_struct%dense,quick_qm_struct%denseSave,nbasis)
      call CopyDMat(quick_qm_struct%oSave,quick_qm_struct%o,nbasis)

      do I=1,nbasis; do J=1,nbasis
         quick_qm_struct%dense(J,I)=quick_qm_struct%dense(J,I)-quick_qm_struct%denseOld(J,I)
      enddo; enddo

   endif

!  Delta density matrix cutoff
   call densityCutoff()

#ifdef MPI
   if(master) then
#endif
!  Start the timer for 2e-integrals
   call cpu_time(timer_begin%T2e)
#ifdef MPI
   endif
#endif

#ifdef MPI
!  Reset the operator value for slave nodes.
   if (.not.master) then
      do i=1,nbasis
         do j=1,nbasis
            quick_qm_struct%o(i,j)=0
         enddo
      enddo
   endif   

!  sync every nodes
   call MPI_BARRIER(MPI_COMM_WORLD,mpierror)
#endif

#ifdef CUDA
   if (quick_method%bCUDA) then

      if(quick_method%HF)then      
         call gpu_upload_method(0)
      elseif(quick_method%uselibxc)then
         call gpu_upload_method(3)
         call gpu_upload_hyb_coeff(quick_method%x_hybrid_coeff)
      elseif(quick_method%BLYP)then
         call gpu_upload_method(2)
      elseif(quick_method%B3LYP)then
         call gpu_upload_method(1)
      endif

      call gpu_upload_calculated(quick_qm_struct%o,quick_qm_struct%co, &
      quick_qm_struct%vec,quick_qm_struct%dense)
      call gpu_upload_cutoff(cutmatrix,quick_method%integralCutoff,quick_method%primLimit)

   endif
#endif

   if (quick_method%nodirect) then
#ifdef CUDA
      call gpu_addint(quick_qm_struct%o, intindex, intFileName)
#else
#ifndef MPI
      call addInt
#endif
#endif
   else
!-----------------------------------------------------------------
! Step 2. evaluate 2e integrals
!-----------------------------------------------------------------
!
! The previous two terms are the one electron part of the Fock matrix.
! The next two terms define the two electron part.
!-----------------------------------------------------------------
#ifdef CUDA
      if (quick_method%bCUDA) then
         call gpu_get2e(quick_qm_struct%o)
      else
#endif
!  Schwartz cutoff is implemented here. (ab|cd)**2<=(ab|ab)*(cd|cd)
!  Reference: Strout DL and Scuseria JCP 102(1995),8448.

#ifdef MPI
!  Every nodes will take about jshell/nodes shells integrals such as 1 water, which has 
!  4 jshell, and 2 nodes will take 2 jshell respectively.
   if(bMPI) then
      do i=1,mpi_jshelln(mpirank)
         ii=mpi_jshell(mpirank,i)
         call get2e(II)
      enddo
   else
      do II=1,jshell
         call get2e(II)
      enddo
   endif        
#else
      do II=1,jshell
         call get2e(II)
      enddo
#endif

#ifdef CUDA
      endif
#endif
   endif

#ifdef MPI
call MPI_BARRIER(MPI_COMM_WORLD,mpierror)
!  After evaluation of 2e integrals, we can communicate every node so
!  that we can sum all integrals. slave node will send infos.
   if(.not.master) then
!  Copy Opertor to a temp array and then send it to master
      call copyDMat(quick_qm_struct%o,temp2d,nbasis)
!  Send operator to master node
      call MPI_SEND(temp2d,nbasis*nbasis,mpi_double_precision,0,mpirank,MPI_COMM_WORLD,IERROR)
   else

!  master node will receive infos from every nodes
      do i=1,mpisize-1
!  receive opertors from slave nodes
         call MPI_RECV(temp2d,nbasis*nbasis,mpi_double_precision,i,i,MPI_COMM_WORLD,MPI_STATUS,IERROR)
!   Sum them into operator
         do ii=1,nbasis
            do jj=1,nbasis
               quick_qm_struct%o(ii,jj)=quick_qm_struct%o(ii,jj)+temp2d(ii,jj)
            enddo
         enddo
      enddo
   endif
!  Sync all nodes
   call MPI_BARRIER(MPI_COMM_WORLD,mpierror)
#endif

!  recover density if calculate difference
   if (deltaO) call CopyDMat(quick_qm_struct%denseSave,quick_qm_struct%dense,nbasis)

#ifdef MPI
   if (master) then
#endif
!  Remember the operator is symmetric
   call copySym(quick_qm_struct%o,nbasis)

!  Give the energy, E=1/2*sigma[i,j](Pij*(Fji+Hcoreji))
   if(quick_method%printEnergy) call get2eEnergy()

!  Terminate the timer for 2e-integrals
   call cpu_time(timer_end%T2e)

!  add the time to cumer
   timer_cumer%T2e=timer_cumer%T2e+timer_end%T2e-timer_begin%T2e
#ifdef MPI
   endif
#endif

!-----------------------------------------------------------------
!  Step 3. If DFT, evaluate the exchange/correlation contribution 
!          to the operator
!-----------------------------------------------------------------

   if (quick_method%DFT) then

#ifdef MPI
   if(master) then
#endif
!  Start the timer for exchange correlation calculation
      call cpu_time(timer_begin%TEx)
#ifdef MPI
   endif
#endif

!  Calculate exchange correlation contribution & add to operator    
      call get_xc

!  Remember the operator is symmetric
      call copySym(quick_qm_struct%o,nbasis)

#ifdef MPI
   if(master) then
#endif

!  Stop the exchange correlation timer
      call cpu_time(timer_end%TEx)

!  Add time total time
      timer_cumer%TEx=timer_cumer%TEx+timer_end%TEx-timer_begin%TEx
   endif

#ifdef MPI
   endif
#endif

return

end subroutine scf_operator

subroutine get_xc
!----------------------------------------------------------------
!  The purpose of this subroutine is to calculate the exchange
!  correlation contribution to the Fock operator. 
!  The angular grid code came from CCL.net.  The radial grid
!  formulas (position and wieghts) is from Gill, Johnson and Pople,
!  Chem. Phys. Lett. v209, n 5+6, 1993, pg 506-512.  The weighting scheme
!  is from Stratmann, Scuseria, and Frisch, Chem. Phys. Lett., v 257,
!  1996, pg 213-223.
!
!  The actual element is:
!  F alpha mu nu = Integral((df/drhoa Phimu Phinu)+
!  (2 df/dgaa Grad(rho a) + df/dgab Grad(rho b)) doT Grad(Phimu Phinu))
!  where F alpha mu nu is the the alpha spin portion of the operator matrix
!  element mu, nu,
!  df/drhoa is the derivative of the functional by the alpha density,
!  df/dgaa is the derivative of the functional by the alpha gradient
!  invariant, i.e. the dot product of the gradient of the alpha
!  density with itself.
!  df/dgab is the derivative of the functional by the dot product of
!  the gradient of the alpha density with the beta density.
!  Grad(Phimu Phinu) is the gradient of Phimu times Phinu. 
!----------------------------------------------------------------
   use allmod
   use xc_f90_types_m
   use xc_f90_lib_m
   implicit double precision(a-h,o-z)

#ifdef MPI
   include "mpif.h"
#endif

   !integer II,JJ,KK,LL,NBI1,NBI2,NBJ1,NBJ2,NBK1,NBK2,NBL1,NBL2, I, J
   !common /hrrstore/II,JJ,KK,LL,NBI1,NBI2,NBJ1,NBJ2,NBK1,NBK2,NBL1,NBL2

   double precision, dimension(1) :: libxc_rho
   double precision, dimension(1) :: libxc_sigma
   double precision, dimension(1) :: libxc_exc
   double precision, dimension(1) :: libxc_vrhoa
   double precision, dimension(1) :: libxc_vsigmaa
   type(xc_f90_pointer_t), dimension(quick_method%nof_functionals) :: xc_func
   type(xc_f90_pointer_t), dimension(quick_method%nof_functionals) :: xc_info   
#ifdef MPI
   double precision,allocatable:: temp2d(:,:)
   integer, dimension(0:mpisize-1) :: itotgridspn
   integer, dimension(0:mpisize-1) :: igridptul
   integer, dimension(0:mpisize-1) :: igridptll
   integer :: ierror
   double precision :: Eelxc, Eelxcslave
   allocate(temp2d(nbasis,nbasis))

!  Braodcast libxc information to slaves
   call MPI_BCAST(quick_method%nof_functionals,1,mpi_integer,0,MPI_COMM_WORLD,mpierror)        
   call MPI_BCAST(quick_method%functional_id,size(quick_method%functional_id),mpi_integer,0,MPI_COMM_WORLD,mpierror)
   call MPI_BCAST(quick_method%xc_polarization,1,mpi_double_precision,0,MPI_COMM_WORLD,mpierror)
#endif

   quick_qm_struct%aelec=0.d0
   quick_qm_struct%belec=0.d0

#ifdef MPI
!  Set the values of slave operators to zero
   if (.not.master) then
      call zeroMatrix(quick_qm_struct%o, nbasis)
      Eelxc=0
   endif
   call zeroMatrix(temp2d, nbasis)
#endif

#ifdef CUDA
   if(quick_method%bCUDA) then
      call gpu_upload_calculated(quick_qm_struct%o,quick_qm_struct%co, &
            quick_qm_struct%vec,quick_qm_struct%dense)
      call gpu_getxc(quick_method%isg, sigrad2, Eelxc, &
            quick_qm_struct%aelec, quick_qm_struct%belec, &
            quick_qm_struct%o, quick_method%nof_functionals, &
            quick_method%functional_id,quick_method%xc_polarization)
   endif
#else

!  Initiate the libxc functionals
   do ifunc=1, quick_method%nof_functionals
      if(quick_method%xc_polarization > 0 ) then
         call xc_f90_func_init(xc_func(ifunc), xc_info(ifunc), &
               quick_method%functional_id(ifunc),XC_POLARIZED)
      else
         call xc_f90_func_init(xc_func(ifunc), &
               xc_info(ifunc),quick_method%functional_id(ifunc),XC_UNPOLARIZED)
      endif
   enddo

!  Form the quadrature
   do Iatm=1,natom
      if(quick_method%ISG.eq.1)then
         Iradtemp=50
      else
         if(quick_molspec%iattype(iatm).le.10)then
            Iradtemp=23
         else
            Iradtemp=26
         endif
      endif

#ifdef MPI
!  Distribute grid points among master and slaves
   call setup_xc_mpi(itotgridspn, igridptul, igridptll, Iradtemp)
#endif

#ifdef MPI
      if(bMPI) then
         irad_init = igridptll(mpirank)
         irad_end = igridptul(mpirank)
      else
         irad_init = 1
         irad_end = Iradtemp
      endif
      do Irad=irad_init, irad_end
#else
      do Irad=1,Iradtemp
#endif
         if(quick_method%ISG.eq.1)then
            call gridformnew(iatm,RGRID(Irad),iiangt)
            rad = radii(quick_molspec%iattype(iatm))
         else
            call gridformSG0(iatm,Iradtemp+1-Irad,iiangt,RGRID,RWT)
            rad = radii2(quick_molspec%iattype(iatm))
         endif

         rad3 = rad*rad*rad
         do Iang=1,iiangt
            gridx=xyz(1,Iatm)+rad*RGRID(Irad)*XANG(Iang)
            gridy=xyz(2,Iatm)+rad*RGRID(Irad)*YANG(Iang)
            gridz=xyz(3,Iatm)+rad*RGRID(Irad)*ZANG(Iang)

!  Next, calculate the weight of the grid point in the SSW scheme.
!  if the grid point has a zero weight, we can skip it.

            weight=SSW(gridx,gridy,gridz,Iatm)*WTANG(Iang)*RWT(Irad)*rad3
            if (weight < quick_method%DMCutoff ) then
               continue
            else

               do Ibas=1,nbasis
                  call pteval(gridx,gridy,gridz,phi,dphidx,dphidy, &
                  dphidz,Ibas)
                  phixiao(Ibas)=phi
                  dphidxxiao(Ibas)=dphidx
                  dphidyxiao(Ibas)=dphidy
                  dphidzxiao(Ibas)=dphidz
               enddo

!  Next, evaluate the densities at the grid point and the gradient
!  at that grid point.

               call denspt(gridx,gridy,gridz,density,densityb,gax,gay,gaz, &
               gbx,gby,gbz)

               if (density < quick_method%DMCutoff ) then
                  continue
               else

!  This allows the calculation of the derivative of the functional with regard to the 
!  density (dfdr), with regard to the alpha-alpha density invariant (df/dgaa), and the
!  alpha-beta density invariant.

                  densitysum=2.0d0*density
                  sigma=4.0d0*(gax*gax+gay*gay+gaz*gaz)

                  libxc_rho(1)=densitysum
                  libxc_sigma(1)=sigma

                  tsttmp_exc=0.0d0
                  tsttmp_vrhoa=0.0d0
                  tsttmp_vsigmaa=0.0d0

                  do ifunc=1, quick_method%nof_functionals
                     select case(xc_f90_info_family(xc_info(ifunc)))
                        case(XC_FAMILY_LDA)
                           call xc_f90_lda_exc_vxc(xc_func(ifunc),1,libxc_rho(1), &
                           libxc_exc(1), libxc_vrhoa(1))
                        case(XC_FAMILY_GGA, XC_FAMILY_HYB_GGA)
                           call xc_f90_gga_exc_vxc(xc_func(ifunc),1,libxc_rho(1), libxc_sigma(1), &
                           libxc_exc(1), libxc_vrhoa(1), libxc_vsigmaa(1))
                     end select

                     tsttmp_exc=tsttmp_exc+libxc_exc(1)
                     tsttmp_vrhoa=tsttmp_vrhoa+libxc_vrhoa(1)
                     tsttmp_vsigmaa=tsttmp_vsigmaa+libxc_vsigmaa(1)
                  enddo

                  zkec=densitysum*tsttmp_exc
                  dfdr=tsttmp_vrhoa
                  xiaodot=tsttmp_vsigmaa*4

                  Eelxc = Eelxc + zkec*weight

                  quick_qm_struct%aelec = weight*density+quick_qm_struct%aelec
                  quick_qm_struct%belec = weight*densityb+quick_qm_struct%belec

!  Calculate the first term in the dot product shown above,
!  i.e.: (2 df/dgaa Grad(rho a) + df/dgab Grad(rho b)) doT Grad(Phimu Phinu))
                  xdot=xiaodot*gax
                  ydot=xiaodot*gay
                  zdot=xiaodot*gaz

!  Now loop over basis functions and compute the addition to the matrix element.
                  do Ibas=1,nbasis
                     phi=phixiao(Ibas)
                     dphidx=dphidxxiao(Ibas)
                     dphidy=dphidyxiao(Ibas)
                     dphidz=dphidzxiao(Ibas)
                     quicktest = DABS(dphidx+dphidy+dphidz+phi)

                     if (quicktest < quick_method%DMCutoff ) then
                        continue
                     else
                        do Jbas=Ibas,nbasis
                           phi2=phixiao(Jbas)
                           dphi2dx=dphidxxiao(Jbas)
                           dphi2dy=dphidyxiao(Jbas)
                           dphi2dz=dphidzxiao(Jbas)
                           temp = phi*phi2
                           tempgx = phi*dphi2dx + phi2*dphidx
                           tempgy = phi*dphi2dy + phi2*dphidy
                           tempgz = phi*dphi2dz + phi2*dphidz
                           quick_qm_struct%o(Jbas,Ibas)=quick_qm_struct%o(Jbas,Ibas)+(temp*dfdr+&
                           xdot*tempgx+ydot*tempgy+zdot*tempgz)*weight
                        enddo
                     endif
                  enddo
               endif
            endif
         enddo
      enddo
   enddo

!  Uninitilize libxc functionals
   do ifunc=1, quick_method%nof_functionals
      call xc_f90_func_end(xc_func(ifunc))
   enddo
#endif

#ifdef MPI
   if(.not. master) then
!  Send the Exc energy value
      Eelxcslave=Eelxc
      call MPI_SEND(Eelxcslave,1,mpi_double_precision,0,mpirank,MPI_COMM_WORLD,IERROR)
      call copyDMat(quick_qm_struct%o,temp2d,nbasis)
      call MPI_SEND(temp2d,nbasis*nbasis,mpi_double_precision,0,mpirank,MPI_COMM_WORLD,IERROR)
   else

!  Master node will receive infos from every nodes
      do i=1,mpisize-1
!  Receive exchange correlation energy from slaves
         call MPI_RECV(Eelxcslave,1,mpi_double_precision,i,i,MPI_COMM_WORLD,MPI_STATUS,IERROR)
         Eelxc=Eelxc+Eelxcslave
!  Receive opertors from slave nodes
         call  MPI_RECV(temp2d,nbasis*nbasis,mpi_double_precision,i,i,MPI_COMM_WORLD,MPI_STATUS,IERROR)
!  Sum them into operator
         do ii=1,nbasis
            do jj=1,nbasis
               quick_qm_struct%o(ii,jj)=quick_qm_struct%o(ii,jj)+temp2d(ii,jj)
            enddo
         enddo
      enddo
   endif
   call MPI_BARRIER(MPI_COMM_WORLD,mpierror)
#endif

#ifdef MPI
   if(master) then
#endif
!  Add the exchange correlation energy to total electronic energy
   quick_qm_struct%Eel=quick_qm_struct%Eel+Eelxc

!   if(quick_method%debug) then
      write(*,*) "Eelex=",Eelxc
      write(*,*) "E1+E2+Eelxc=",quick_qm_struct%Eel
!   endif
#ifdef MPI
   endif
#endif
   return

end subroutine get_xc

