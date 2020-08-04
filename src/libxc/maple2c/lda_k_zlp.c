/*    
  This file was generated automatically with ../scripts/maple2c.pl.   
  Do not edit this file directly as it can be overwritten!!   
   
  This Source Code Form is subject to the terms of the Mozilla Public   
  License, v. 2.0. If a copy of the MPL was not distributed with this   
  file, You can obtain one at http://mozilla.org/MPL/2.0/.   
   
  Maple version     : Maple 2016 (X86 64 LINUX)   
  Maple source      : ../maple/lda_k_zlp.mpl   
  Type of functional: work_lda   
*/   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_k_zlp_func0_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func0(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t3, t4, t6, t7, t8, t9;   
  double t10, t12, t14, t18, t19, t23, t27, t28;   
  double t35, t38, t42, t44, t56, t57, t60, t63;   
  double t90;   
   
   
  t1 = M_CBRT3;   
  t2 = M_CBRT4;   
  t3 = t2 * t2;   
  t4 = t1 * t3;   
  t6 = cbrt(0.1e1 / 0.31415926535897932385e1);   
  t7 = r->rs * r->rs;   
  t8 = 0.1e1 / t7;   
  t9 = t6 * t8;   
  t10 = 0.1e1 / r->rs;   
  t12 = t1 * t1;   
  t14 = 0.1e1 / t6;   
  t18 = 0.1e1 + 0.17006802721088435374e3 * r->rs * t12 * t2 * t14;   
  t19 = log(t18);   
  t23 = 0.1e1 - 0.49000000000000000000e-3 * t4 * t6 * t10 * t19;   
  r->f = 0.80930000000000000000e0 * t4 * t9 * t23;   
   
  if(r->order < 1) return;   
   
  t27 = 0.1e1 / t7 / r->rs;   
  t28 = t6 * t27;   
  t35 = 0.1e1 / t18;   
  t38 = 0.49000000000000000000e-3 * t4 * t9 * t19 - 0.10000000000000000000e1 * t10 * t35;   
  r->dfdrs = -0.16186000000000000000e1 * t4 * t28 * t23 + 0.80930000000000000000e0 * t4 * t9 * t38;   
   
  if(r->order < 2) return;   
   
  t42 = t7 * t7;   
  t44 = t6 / t42;   
  t56 = t18 * t18;   
  t57 = 0.1e1 / t56;   
  t60 = t12 * t2 * t14;   
  t63 = -0.98000000000000000000e-3 * t4 * t28 * t19 + 0.20000000000000000000e1 * t8 * t35 + 0.17006802721088435374e3 * t10 * t57 * t60;   
  r->d2fdrs2 = 0.48558000000000000000e1 * t4 * t44 * t23 - 0.32372000000000000000e1 * t4 * t28 * t38 + 0.80930000000000000000e0 * t4 * t9 * t63;   
   
  if(r->order < 3) return;   
   
  t90 = t6 * t6;   
  r->d3fdrs3 = -0.19423200000000000000e2 * t4 * t6 / t42 / r->rs * t23 + 0.14567400000000000000e2 * t4 * t44 * t38 - 0.48558000000000000000e1 * t4 * t28 * t63 + 0.80930000000000000000e0 * t4 * t9 * (0.29400000000000000000e-2 * t4 * t44 * t19 - 0.60000000000000000000e1 * t27 * t35 - 0.51020408163265306122e3 * t8 * t57 * t60 - 0.17353880327641260585e6 * t10 / t56 / t18 * t4 / t90);   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_k_zlp_func1_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func1(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t3, t4, t6, t7, t8, t9;   
  double t10, t12, t13, t14, t17, t18, t19, t20;   
  double t21, t23, t25, t29, t30, t34, t38, t39;   
  double t47, t50, t55, t56, t59, t60, t61, t74;   
  double t75, t78, t81, t85, t95, t96, t123;   
   
   
  t1 = M_CBRT3;   
  t2 = M_CBRT4;   
  t3 = t2 * t2;   
  t4 = t1 * t3;   
  t6 = cbrt(0.1e1 / 0.31415926535897932385e1);   
  t7 = t4 * t6;   
  t8 = 0.1e1 + r->z;   
  t9 = cbrt(t8);   
  t10 = t9 * t9;   
  t12 = 0.1e1 - r->z;   
  t13 = cbrt(t12);   
  t14 = t13 * t13;   
  t17 = t10 * t8 / 0.2e1 + t14 * t12 / 0.2e1;   
  t18 = r->rs * r->rs;   
  t19 = 0.1e1 / t18;   
  t20 = t17 * t19;   
  t21 = 0.1e1 / r->rs;   
  t23 = t1 * t1;   
  t25 = 0.1e1 / t6;   
  t29 = 0.1e1 + 0.17006802721088435374e3 * r->rs * t23 * t2 * t25;   
  t30 = log(t29);   
  t34 = 0.1e1 - 0.49000000000000000000e-3 * t4 * t6 * t21 * t30;   
  r->f = 0.80930000000000000000e0 * t7 * t20 * t34;   
   
  if(r->order < 1) return;   
   
  t38 = 0.1e1 / t18 / r->rs;   
  t39 = t17 * t38;   
  t47 = 0.1e1 / t29;   
  t50 = 0.49000000000000000000e-3 * t4 * t6 * t19 * t30 - 0.10000000000000000000e1 * t21 * t47;   
  r->dfdrs = -0.16186000000000000000e1 * t7 * t39 * t34 + 0.80930000000000000000e0 * t7 * t20 * t50;   
  t55 = 0.5e1 / 0.6e1 * t10 - 0.5e1 / 0.6e1 * t14;   
  t56 = t55 * t19;   
  r->dfdz = 0.80930000000000000000e0 * t7 * t56 * t34;   
   
  if(r->order < 2) return;   
   
  t59 = t18 * t18;   
  t60 = 0.1e1 / t59;   
  t61 = t17 * t60;   
  t74 = t29 * t29;   
  t75 = 0.1e1 / t74;   
  t78 = t23 * t2 * t25;   
  t81 = -0.98000000000000000000e-3 * t4 * t6 * t38 * t30 + 0.20000000000000000000e1 * t19 * t47 + 0.17006802721088435374e3 * t21 * t75 * t78;   
  r->d2fdrs2 = 0.48558000000000000000e1 * t7 * t61 * t34 - 0.32372000000000000000e1 * t7 * t39 * t50 + 0.80930000000000000000e0 * t7 * t20 * t81;   
  t85 = t55 * t38;   
  r->d2fdrsz = -0.16186000000000000000e1 * t7 * t85 * t34 + 0.80930000000000000000e0 * t7 * t56 * t50;   
  t95 = 0.5e1 / 0.9e1 / t9 + 0.5e1 / 0.9e1 / t13;   
  t96 = t95 * t19;   
  r->d2fdz2 = 0.80930000000000000000e0 * t7 * t96 * t34;   
   
  if(r->order < 3) return;   
   
  t123 = t6 * t6;   
  r->d3fdrs3 = -0.19423200000000000000e2 * t7 * t17 / t59 / r->rs * t34 + 0.14567400000000000000e2 * t7 * t61 * t50 - 0.48558000000000000000e1 * t7 * t39 * t81 + 0.80930000000000000000e0 * t7 * t20 * (0.29400000000000000000e-2 * t4 * t6 * t60 * t30 - 0.60000000000000000000e1 * t38 * t47 - 0.51020408163265306122e3 * t19 * t75 * t78 - 0.17353880327641260585e6 * t21 / t74 / t29 * t4 / t123);   
  r->d3fdrs2z = 0.48558000000000000000e1 * t7 * t55 * t60 * t34 - 0.32372000000000000000e1 * t7 * t85 * t50 + 0.80930000000000000000e0 * t7 * t56 * t81;   
  r->d3fdrsz2 = -0.16186000000000000000e1 * t7 * t95 * t38 * t34 + 0.80930000000000000000e0 * t7 * t96 * t50;   
  r->d3fdz3 = 0.80930000000000000000e0 * t7 * (-0.5e1 / 0.27e2 / t9 / t8 + 0.5e1 / 0.27e2 / t13 / t12) * t19 * t34;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ void   
xc_lda_k_zlp_func_kernel(const void *p, xc_lda_work_t *r)   
{   
  if(r->nspin == XC_UNPOLARIZED)   
xc_lda_k_zlp_func0_kernel(p, r);   
  else   
xc_lda_k_zlp_func1_kernel(p, r);   
}   
#else   
void    
xc_lda_k_zlp_func(const xc_func_type *p, xc_lda_work_t *r)   
{   
  if(p->nspin == XC_UNPOLARIZED)   
    func0(p, r);   
  else   
    func1(p, r);   
}   
#endif   
   
#ifndef DEVICE   
#define maple2c_order 3   
#define maple2c_func  xc_lda_k_zlp_func   
#define kernel_id 22 
#endif
