/*    
  This file was generated automatically with ../scripts/maple2c.pl.   
  Do not edit this file directly as it can be overwritten!!   
   
  This Source Code Form is subject to the terms of the Mozilla Public   
  License, v. 2.0. If a copy of the MPL was not distributed with this   
  file, You can obtain one at http://mozilla.org/MPL/2.0/.   
   
  Maple version     : Maple 2016 (X86 64 LINUX)   
  Maple source      : ../maple/lda_x.mpl   
  Type of functional: work_lda   
*/   
#ifdef DEVICE   
__device__ static void   
xc_lda_x_func0_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func0(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t4, t5, t7, t8, t9, t10;   
  double t11, t16, t25;   
   
  lda_x_params *params;   
#ifndef DEVICE   
  assert(p->params != NULL);   
  params = (lda_x_params * )(p->params);   
#else   
  params = (lda_x_params * )(p);   
#endif   
  t1 = M_CBRT3;   
  t2 = t1 * t1;   
  t4 = M_CBRT4;   
  t5 = params->alpha * t2 * t4;   
  t7 = cbrt(0.1e1 / 0.31415926535897932385e1);   
  t8 = t7 * t7;   
  t9 = M_CBRT2;   
  t10 = t9 * t9;   
  t11 = t8 * t10;   
  r->f = -0.18750000000000000000e0 * t5 * t11 / r->rs;   
   
  if(r->order < 1) return;   
   
  t16 = r->rs * r->rs;   
  r->dfdrs = 0.18750000000000000000e0 * t5 * t11 / t16;   
   
  if(r->order < 2) return;   
   
  r->d2fdrs2 = -0.37500000000000000000e0 * t5 * t11 / t16 / r->rs;   
   
  if(r->order < 3) return;   
   
  t25 = t16 * t16;   
  r->d3fdrs3 = 0.11250000000000000000e1 * t5 * t11 / t25;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_x_func1_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func1(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t4, t5, t7, t8, t9, t10;   
  double t11, t12, t13, t15, t16, t18, t19, t24;   
  double t25, t30, t36, t44, t46, t49, t54;   
   
  lda_x_params *params;   
#ifndef DEVICE   
  assert(p->params != NULL);   
  params = (lda_x_params * )(p->params);   
#else   
  params = (lda_x_params * )(p);   
#endif   
  t1 = M_CBRT3;   
  t2 = t1 * t1;   
  t4 = M_CBRT4;   
  t5 = params->alpha * t2 * t4;   
  t7 = cbrt(0.1e1 / 0.31415926535897932385e1);   
  t8 = t7 * t7;   
  t9 = M_CBRT2;   
  t10 = t9 * t9;   
  t11 = t8 * t10;   
  t12 = 0.1e1 + r->z;   
  t13 = cbrt(t12);   
  t15 = 0.1e1 - r->z;   
  t16 = cbrt(t15);   
  t18 = t13 * t12 + t16 * t15;   
  t19 = 0.1e1 / r->rs;   
  r->f = -0.3e1 / 0.32e2 * t5 * t11 * t18 * t19;   
   
  if(r->order < 1) return;   
   
  t24 = r->rs * r->rs;   
  t25 = 0.1e1 / t24;   
  r->dfdrs = 0.3e1 / 0.32e2 * t5 * t11 * t18 * t25;   
  t30 = 0.4e1 / 0.3e1 * t13 - 0.4e1 / 0.3e1 * t16;   
  r->dfdz = -0.3e1 / 0.32e2 * t5 * t11 * t30 * t19;   
   
  if(r->order < 2) return;   
   
  t36 = 0.1e1 / t24 / r->rs;   
  r->d2fdrs2 = -0.3e1 / 0.16e2 * t5 * t11 * t18 * t36;   
  r->d2fdrsz = 0.3e1 / 0.32e2 * t5 * t11 * t30 * t25;   
  t44 = t13 * t13;   
  t46 = t16 * t16;   
  t49 = 0.4e1 / 0.9e1 / t44 + 0.4e1 / 0.9e1 / t46;   
  r->d2fdz2 = -0.3e1 / 0.32e2 * t5 * t11 * t49 * t19;   
   
  if(r->order < 3) return;   
   
  t54 = t24 * t24;   
  r->d3fdrs3 = 0.9e1 / 0.16e2 * t5 * t11 * t18 / t54;   
  r->d3fdrs2z = -0.3e1 / 0.16e2 * t5 * t11 * t30 * t36;   
  r->d3fdrsz2 = 0.3e1 / 0.32e2 * t5 * t11 * t49 * t25;   
  r->d3fdz3 = -0.3e1 / 0.32e2 * t5 * t11 * (-0.8e1 / 0.27e2 / t44 / t12 + 0.8e1 / 0.27e2 / t46 / t15) * t19;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ void   
xc_lda_x_func_kernel(const void *p, xc_lda_work_t *r)   
{   
  if(r->nspin == XC_UNPOLARIZED)  
xc_lda_x_func0_kernel(p, r);  
  else  
xc_lda_x_func1_kernel(p, r);   
}  
#else   
void    
xc_lda_x_func(const xc_func_type *p, xc_lda_work_t *r)   
{   
  if(p->nspin == XC_UNPOLARIZED)    
    func0(p, r);   
  else   
    func1(p, r);   
}   
#endif  
   
#ifndef DEVICE   
#define maple2c_order 3   
#define maple2c_func  xc_lda_x_func   
#define kernel_id 23 
#endif
