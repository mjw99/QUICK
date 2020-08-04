/*    
  This file was generated automatically with ../scripts/maple2c.pl.   
  Do not edit this file directly as it can be overwritten!!   
   
  This Source Code Form is subject to the terms of the Mozilla Public   
  License, v. 2.0. If a copy of the MPL was not distributed with this   
  file, You can obtain one at http://mozilla.org/MPL/2.0/.   
   
  Maple version     : Maple 2016 (X86 64 LINUX)   
  Maple source      : ../maple/lda_c_pz.mpl   
  Type of functional: work_lda   
*/   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_c_pz_func0_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func0(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t3, t5, t7, t9, t10, t11;   
  double t13, t14, t15, t19, t20, t22, t23, t25;   
  double t27, t29, t33, t36, t38, t43, t44, t52;   
  double t53, t60, t62, t66, t68, t76, t77, t78;   
  double t92, t109, t111, t116, t142;   
   
  lda_c_pz_params *params;   
   
#ifndef DEVICE   
  assert(p->params != NULL);   
  params = (lda_c_pz_params * )(p->params);   
#else   
  params = (lda_c_pz_params * )(p);   
#endif   
   
  t1 = params->gamma[0];   
  t2 = params->beta1[0];   
  t3 = sqrt(r->rs);   
  t5 = params->beta2[0];   
  t7 = t5 * r->rs + t2 * t3 + 0.1e1;   
  t9 = t1 / t7;   
  t10 = r->rs - 0.1e1;   
  t11 = Heaviside(t10);   
  t13 = params->c[0];   
  t14 = t13 * r->rs;   
  t15 = log(r->rs);   
  t19 = params->a[0];   
  t20 = t19 * t15;   
  t22 = params->d[0];   
  t23 = t22 * r->rs;   
  t25 = params->b[0];   
  r->f = -t14 * t15 * t11 - t20 * t11 - t23 * t11 - t25 * t11 + t9 * t11 + t14 * t15 + t20 + t23 + t25;   
   
  if(r->order < 1) return;   
   
  t27 = t7 * t7;   
  t29 = t1 / t27;   
  t33 = t2 / t3 / 0.2e1 + t5;   
  t36 = 0.0;   
  t38 = t13 * t15;   
  t43 = 0.1e1 / r->rs;   
  t44 = t19 * t43;   
  r->dfdrs = -t29 * t11 * t33 - t14 * t15 * t36 - t13 * t11 - t22 * t11 - t38 * t11 - t44 * t11 - t20 * t36 - t23 * t36 - t25 * t36 + t9 * t36 + t13 + t22 + t38 + t44;   
   
  if(r->order < 2) return;   
   
  t52 = t1 / t27 / t7;   
  t53 = t33 * t33;   
  t60 = t11 * t2;   
  t62 = 0.1e1 / t3 / r->rs;   
  t66 = 0.0;   
  t68 = t13 * t43;   
  t76 = r->rs * r->rs;   
  t77 = 0.1e1 / t76;   
  t78 = t19 * t77;   
  r->d2fdrs2 = 0.2e1 * t52 * t11 * t53 - 0.2e1 * t29 * t36 * t33 + t29 * t60 * t62 / 0.4e1 + t9 * t66 - t68 * t11 - 0.2e1 * t38 * t36 - 0.2e1 * t13 * t36 - t14 * t15 * t66 + t68 + t78 * t11 - 0.2e1 * t44 * t36 - t20 * t66 - t78 - 0.2e1 * t22 * t36 - t23 * t66 - t25 * t66;   
   
  if(r->order < 3) return;   
   
  t92 = t27 * t27;   
  t109 = t13 * t77;   
  t111 = 0.0;   
  t116 = t19 / t76 / r->rs;   
  t142 = -0.3e1 * t38 * t66 + 0.3e1 * t78 * t36 - 0.3e1 * t44 * t66 - t20 * t111 - t23 * t111 - 0.3e1 * t13 * t66 - t109 + 0.2e1 * t116 - 0.3e1 * t22 * t66 - t25 * t111 - 0.3e1 / 0.8e1 * t29 * t60 / t3 / t76;   
  r->d3fdrs3 = t142 - 0.3e1 / 0.2e1 * t52 * t11 * t33 * t2 * t62 - 0.6e1 * t1 / t92 * t11 * t53 * t33 + 0.3e1 / 0.4e1 * t29 * t36 * t2 * t62 + 0.6e1 * t52 * t36 * t53 - 0.3e1 * t29 * t66 * t33 + t109 * t11 - t14 * t15 * t111 - 0.2e1 * t116 * t11 + t9 * t111 - 0.3e1 * t68 * t36;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ static void   
xc_lda_c_pz_func1_kernel(const void *p, xc_lda_work_t *r)   
#else   
static void   
func1(const xc_func_type *p, xc_lda_work_t *r)   
#endif   
{   
  double t1, t2, t3, t5, t7, t9, t10, t11;   
  double t12, t13, t14, t15, t16, t17, t18, t19;   
  double t20, t21, t22, t23, t24, t25, t26, t27;   
  double t28, t30, t32, t34, t36, t37, t40, t41;   
  double t43, t44, t46, t48, t49, t50, t52, t53;   
  double t55, t57, t60, t62, t64, t65, t68, t70;   
  double t71, t72, t73, t74, t75, t76, t77, t78;   
  double t79, t80, t81, t82, t83, t84, t85, t88;   
  double t92, t93, t95, t98, t105, t106, t110, t114;   
  double t115, t118, t121, t122, t124, t127, t128, t129;   
  double t130, t131, t133, t135, t136, t137, t138, t139;   
  double t140, t141, t143, t144, t146, t147, t148, t149;   
  double t153, t155, t164, t167, t168, t181, t182, t186;   
  double t188, t191, t193, t199, t203, t206, t209, t210;   
  double t211, t212, t213, t214, t216, t217, t219, t220;   
  double t222, t224, t226, t227, t229, t230, t231, t237;   
  double t240, t247, t250, t260, t263, t281, t293, t295;   
  double t296, t297, t300, t305;   
   
  lda_c_pz_params *params;   
   
#ifndef DEVICE   
  assert(p->params != NULL);   
  params = (lda_c_pz_params * )(p->params);   
#else   
  params = (lda_c_pz_params * )(p);   
#endif   
   
  t1 = params->gamma[0];   
  t2 = params->beta1[0];   
  t3 = sqrt(r->rs);   
  t5 = params->beta2[0];   
  t7 = t5 * r->rs + t2 * t3 + 0.1e1;   
  t9 = t1 / t7;   
  t10 = r->rs - 0.1e1;   
  t11 = Heaviside(t10);   
  t12 = t9 * t11;   
  t13 = params->c[0];   
  t14 = t13 * r->rs;   
  t15 = log(r->rs);   
  t16 = t15 * t11;   
  t17 = t14 * t16;   
  t18 = t14 * t15;   
  t19 = params->a[0];   
  t20 = t19 * t15;   
  t21 = t20 * t11;   
  t22 = params->d[0];   
  t23 = t22 * r->rs;   
  t24 = t23 * t11;   
  t25 = params->b[0];   
  t26 = t25 * t11;   
  t27 = params->gamma[1];   
  t28 = params->beta1[1];   
  t30 = params->beta2[1];   
  t32 = t30 * r->rs + t28 * t3 + 0.1e1;   
  t34 = t27 / t32;   
  t36 = params->c[1];   
  t37 = t36 * r->rs;   
  t40 = params->a[1];   
  t41 = t40 * t15;   
  t43 = params->d[1];   
  t44 = t43 * r->rs;   
  t46 = params->b[1];   
  t48 = t34 * t11 - t41 * t11 - t44 * t11 - t46 * t11 + t37 * t15 - t37 * t16 - t12 + t17 - t18 - t20 + t21 - t23 + t24 - t25 + t26 + t41 + t44 + t46;   
  t49 = 0.1e1 + r->z;   
  t50 = cbrt(t49);   
  t52 = 0.1e1 - r->z;   
  t53 = cbrt(t52);   
  t55 = t50 * t49 + t53 * t52 - 0.2e1;   
  t57 = M_CBRT2;   
  t60 = 0.1e1 / (0.2e1 * t57 - 0.2e1);   
  r->f = t48 * t55 * t60 + t12 - t17 + t18 + t20 - t21 + t23 - t24 + t25 - t26;   
   
  if(r->order < 1) return;   
   
  t62 = t7 * t7;   
  t64 = t1 / t62;   
  t65 = 0.1e1 / t3;   
  t68 = t2 * t65 / 0.2e1 + t5;   
  t70 = t64 * t11 * t68;   
  t71 = 0.0;   
  t72 = t9 * t71;   
  t73 = t13 * t15;   
  t74 = t73 * t11;   
  t75 = t13 * t11;   
  t76 = t15 * t71;   
  t77 = t14 * t76;   
  t78 = 0.1e1 / r->rs;   
  t79 = t19 * t78;   
  t80 = t79 * t11;   
  t81 = t20 * t71;   
  t82 = t22 * t11;   
  t83 = t23 * t71;   
  t84 = t25 * t71;   
  t85 = t36 * t15;   
  t88 = t40 * t78;   
  t92 = -t85 * t11 - t88 * t11 + t34 * t71 - t41 * t71 - t44 * t71 - t13 - t22 + t36 + t43 - t72 + t74 + t80 + t81 + t83;   
  t93 = t32 * t32;   
  t95 = t27 / t93;   
  t98 = t28 * t65 / 0.2e1 + t30;   
  t105 = -t95 * t11 * t98 - t36 * t11 - t43 * t11 - t37 * t76 - t46 * t71 + t70 - t73 + t75 + t77 - t79 + t82 + t84 + t85 + t88;   
  t106 = t105 + t92;   
  r->dfdrs = t106 * t55 * t60 + t13 + t22 - t70 + t72 + t73 - t74 - t75 - t77 + t79 - t80 - t81 - t82 - t83 - t84;   
  t110 = 0.4e1 / 0.3e1 * t50 - 0.4e1 / 0.3e1 * t53;   
  r->dfdz = t48 * t110 * t60;   
   
  if(r->order < 2) return;   
   
  t114 = t1 / t62 / t7;   
  t115 = t68 * t68;   
  t118 = 0.2e1 * t114 * t11 * t115;   
  t121 = 0.2e1 * t64 * t71 * t68;   
  t122 = t11 * t2;   
  t124 = 0.1e1 / t3 / r->rs;   
  t127 = t64 * t122 * t124 / 0.4e1;   
  t128 = 0.0;   
  t129 = t9 * t128;   
  t130 = t13 * t78;   
  t131 = t130 * t11;   
  t133 = 0.2e1 * t73 * t71;   
  t135 = 0.2e1 * t13 * t71;   
  t136 = t15 * t128;   
  t137 = t14 * t136;   
  t138 = r->rs * r->rs;   
  t139 = 0.1e1 / t138;   
  t140 = t19 * t139;   
  t141 = t140 * t11;   
  t143 = 0.2e1 * t79 * t71;   
  t144 = t20 * t128;   
  t146 = 0.2e1 * t22 * t71;   
  t147 = t23 * t128;   
  t148 = t25 * t128;   
  t149 = t11 * t28;   
  t153 = t40 * t139;   
  t155 = t36 * t78;   
  t164 = -t127 + t95 * t149 * t124 / 0.4e1 + t153 * t11 - t155 * t11 - 0.2e1 * t85 * t71 + t34 * t128 - 0.2e1 * t88 * t71 - t41 * t128 - t44 * t128 - t129 + t131 + t133 - t141 + t143 + t144 + t147;   
  t167 = t27 / t93 / t32;   
  t168 = t98 * t98;   
  t181 = 0.2e1 * t167 * t11 * t168 - 0.2e1 * t95 * t71 * t98 - t46 * t128 - t37 * t136 - 0.2e1 * t36 * t71 - 0.2e1 * t43 * t71 - t118 + t121 - t130 + t135 + t137 + t140 + t146 + t148 - t153 + t155;   
  t182 = t181 + t164;   
  r->d2fdrs2 = t182 * t55 * t60 + t118 - t121 + t127 + t129 + t130 - t131 - t133 - t135 - t137 - t140 + t141 - t143 - t144 - t146 - t147 - t148;   
  r->d2fdrsz = t106 * t110 * t60;   
  t186 = t50 * t50;   
  t188 = t53 * t53;   
  t191 = 0.4e1 / 0.9e1 / t186 + 0.4e1 / 0.9e1 / t188;   
  r->d2fdz2 = t48 * t191 * t60;   
   
  if(r->order < 3) return;   
   
  t193 = t62 * t62;   
  t199 = 0.6e1 * t1 / t193 * t11 * t115 * t68;   
  t203 = 0.3e1 / 0.4e1 * t64 * t71 * t2 * t124;   
  t206 = 0.6e1 * t114 * t71 * t115;   
  t209 = 0.3e1 * t64 * t128 * t68;   
  t210 = t13 * t139;   
  t211 = t210 * t11;   
  t212 = 0.0;   
  t213 = t15 * t212;   
  t214 = t14 * t213;   
  t216 = 0.1e1 / t138 / r->rs;   
  t217 = t19 * t216;   
  t219 = 0.2e1 * t217 * t11;   
  t220 = t9 * t212;   
  t222 = 0.3e1 * t130 * t71;   
  t224 = 0.3e1 * t73 * t128;   
  t226 = 0.3e1 * t140 * t71;   
  t227 = -t199 + t203 + t206 - t209 + t211 - t214 - t219 + t220 - t222 - t224 + t226;   
  t229 = 0.3e1 * t79 * t128;   
  t230 = t20 * t212;   
  t231 = t23 * t212;   
  t237 = 0.1e1 / t3 / t138;   
  t240 = 0.3e1 / 0.8e1 * t64 * t122 * t237;   
  t247 = t40 * t216;   
  t250 = t36 * t139;   
  t260 = -0.2e1 * t247 * t11 + t250 * t11 - 0.3e1 * t85 * t128 - 0.3e1 * t88 * t128 + 0.3e1 * t153 * t71 - 0.3e1 * t155 * t71 + t34 * t212 - t41 * t212 + t229 + t230 + t231;   
  t263 = t93 * t93;   
  t281 = 0.3e1 / 0.2e1 * t114 * t11 * t68 * t2 * t124;   
  t293 = 0.3e1 * t13 * t128;   
  t295 = 0.3e1 * t22 * t128;   
  t296 = t25 * t212;   
  t297 = 0.2e1 * t217;   
  t300 = -0.3e1 / 0.2e1 * t167 * t11 * t98 * t28 * t124 - 0.3e1 * t36 * t128 - 0.3e1 * t43 * t128 + t293 + t295 + t296 + t210 - t297 + 0.2e1 * t247 - t46 * t212 - t250;   
  t305 = -t229 - t230 - t231 + (t300 - t44 * t212 + t199 - t206 + t209 + t214 - 0.6e1 * t27 / t263 * t11 * t168 * t98 + 0.6e1 * t167 * t71 * t168 - 0.3e1 * t95 * t128 * t98 - t37 * t213 + t281 + t260 - t203 + 0.3e1 / 0.4e1 * t95 * t71 * t28 * t124 + t240 - 0.3e1 / 0.8e1 * t95 * t149 * t237 - t211 + t219 - t220 + t222 + t224 - t226) * t55 * t60 - t293 - t295 - t296 - t210 + t297 - t281 - t240;   
  r->d3fdrs3 = t305 + t227;   
  r->d3fdrs2z = t182 * t110 * t60;   
  r->d3fdrsz2 = t106 * t191 * t60;   
  r->d3fdz3 = t48 * (-0.8e1 / 0.27e2 / t186 / t49 + 0.8e1 / 0.27e2 / t188 / t52) * t60;   
   
  if(r->order < 4) return;   
   
   
}   
   
#ifdef DEVICE   
__device__ void   
xc_lda_c_pz_func_kernel(const void *p, xc_lda_work_t *r)   
{   
  if(r->nspin == XC_UNPOLARIZED)   
xc_lda_c_pz_func0_kernel(p, r);   
  else   
xc_lda_c_pz_func1_kernel(p, r);   
}   
#else   
void    
xc_lda_c_pz_func(const xc_func_type *p, xc_lda_work_t *r)   
{   
  if(p->nspin == XC_UNPOLARIZED)   
    func0(p, r);   
  else   
    func1(p, r);   
}   
#endif   
   
#ifndef DEVICE   
#define maple2c_order 3   
#define maple2c_func  xc_lda_c_pz_func   
#define kernel_id 11 
#endif
