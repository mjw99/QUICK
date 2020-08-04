/*    
  This file was generated automatically with ../scripts/maple2c.pl.   
  Do not edit this file directly as it can be overwritten!!   
   
  This Source Code Form is subject to the terms of the Mozilla Public   
  License, v. 2.0. If a copy of the MPL was not distributed with this   
  file, You can obtain one at http://mozilla.org/MPL/2.0/.   
   
  Maple version     : Maple 2016 (X86 64 LINUX)   
  Maple source      : ../maple/lda_k_tf.mpl   
  Type of functional: work_lda   
*/   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_k_tf_func0_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func0(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t8;   
   
  lda_k_tf_params *params;   
   
#ifndef DEVICE   
  assert(p->params != NULL);   
  params = (lda_k_tf_params * )(p->params);   
#else   
  params = (lda_k_tf_params * )(p);   
#endif   
   
  t1 = r->rs * r->rs;   
  r->f = 0.10000000000000000000e1 * params->ax / t1;   
   
  if(r->order < 1) return;   
   
  r->dfdrs = -0.20000000000000000000e1 * params->ax / t1 / r->rs;   
   
  if(r->order < 2) return;   
   
  t8 = t1 * t1;   
  r->d2fdrs2 = 0.60000000000000000000e1 * params->ax / t8;   
   
  if(r->order < 3) return;   
   
  r->d3fdrs3 = -0.24000000000000000000e2 * params->ax / t8 / r->rs;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_k_tf_func1_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func1(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t3, t5, t6, t7, t11, t12;   
  double t13, t15, t20, t21, t22, t30;   
   
  lda_k_tf_params *params;   
   
#ifndef DEVICE   
  assert(p->params != NULL);   
  params = (lda_k_tf_params * )(p->params);   
#else   
  params = (lda_k_tf_params * )(p);   
#endif   
   
  t1 = 0.1e1 + r->z;   
  t2 = cbrt(t1);   
  t3 = t2 * t2;   
  t5 = 0.1e1 - r->z;   
  t6 = cbrt(t5);   
  t7 = t6 * t6;   
  t11 = params->ax * (t3 * t1 / 0.2e1 + t7 * t5 / 0.2e1);   
  t12 = r->rs * r->rs;   
  t13 = 0.1e1 / t12;   
  r->f = t11 * t13;   
   
  if(r->order < 1) return;   
   
  t15 = 0.1e1 / t12 / r->rs;   
  r->dfdrs = -0.2e1 * t11 * t15;   
  t20 = params->ax * (0.5e1 / 0.6e1 * t3 - 0.5e1 / 0.6e1 * t7);   
  r->dfdz = t20 * t13;   
   
  if(r->order < 2) return;   
   
  t21 = t12 * t12;   
  t22 = 0.1e1 / t21;   
  r->d2fdrs2 = 0.6e1 * t11 * t22;   
  r->d2fdrsz = -0.2e1 * t20 * t15;   
  t30 = params->ax * (0.5e1 / 0.9e1 / t2 + 0.5e1 / 0.9e1 / t6);   
  r->d2fdz2 = t30 * t13;   
   
  if(r->order < 3) return;   
   
  r->d3fdrs3 = -0.24e2 * t11 / t21 / r->rs;   
  r->d3fdrs2z = 0.6e1 * t20 * t22;   
  r->d3fdrsz2 = -0.2e1 * t30 * t15;   
  r->d3fdz3 = params->ax * (-0.5e1 / 0.27e2 / t2 / t1 + 0.5e1 / 0.27e2 / t6 / t5) * t13;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ void   
xc_lda_k_tf_func_kernel(const void *p, xc_lda_work_t *r)   
{   
  if(r->nspin == XC_UNPOLARIZED)   
xc_lda_k_tf_func0_kernel(p, r);   
  else   
xc_lda_k_tf_func1_kernel(p, r);   
}   
#else   
void    
xc_lda_k_tf_func(const xc_func_type *p, xc_lda_work_t *r)   
{   
  if(p->nspin == XC_UNPOLARIZED)   
    func0(p, r);   
  else   
    func1(p, r);   
}   
#endif   
   
#ifndef DEVICE   
#define maple2c_order 3   
#define maple2c_func  xc_lda_k_tf_func   
#define kernel_id 21 
#endif
