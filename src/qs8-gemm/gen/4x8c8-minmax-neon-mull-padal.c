// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/c8-neon-mull-padal.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/common.h>
#include <xnnpack/gemm.h>

static const int32x4_t combine4(const int32x4_t a, const int32x4_t b, const int32x4_t c, const int32x4_t d) {
  const int32x4_t ab = vpaddq_s32(a, b);
  const int32x4_t cd = vpaddq_s32(c, d);
  const int32x4_t abcd= vpaddq_s32(ab, cd);
  return abcd;
}

void xnn_qs8_gemm_minmax_ukernel_4x8c8__neon_mull_padal(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    int8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_qs8_gemm_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN
{
  assert(mr != 0);
  assert(mr <= 4);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  const int8_t* a0 = a;
  int8_t* c0 = c;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  int8_t* c1 = (int8_t*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 2) {
    a1 = a0;
    c1 = c0;
  }
  const int8_t* a2 = (const int8_t*) ((uintptr_t) a1 + a_stride);
  int8_t* c2 = (int8_t*) ((uintptr_t) c1 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 2) {
    a2 = a1;
    c2 = c1;
  }
  const int8_t* a3 = (const int8_t*) ((uintptr_t) a2 + a_stride);
  int8_t* c3 = (int8_t*) ((uintptr_t) c2 + cm_stride);
  if XNN_UNPREDICTABLE(mr != 4) {
    a3 = a2;
    c3 = c2;
  }

  do {
    int32x4_t vacc0x0 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x1 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x2 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x3 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x4 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x5 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x6 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc0x7 = vld1q_s32(w); w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));
    int32x4_t vacc1x0 = vacc0x0;
    int32x4_t vacc1x1 = vacc0x1;
    int32x4_t vacc1x2 = vacc0x2;
    int32x4_t vacc1x3 = vacc0x3;
    int32x4_t vacc1x4 = vacc0x4;
    int32x4_t vacc1x5 = vacc0x5;
    int32x4_t vacc1x6 = vacc0x6;
    int32x4_t vacc1x7 = vacc0x7;
    int32x4_t vacc2x0 = vacc0x0;
    int32x4_t vacc2x1 = vacc0x1;
    int32x4_t vacc2x2 = vacc0x2;
    int32x4_t vacc2x3 = vacc0x3;
    int32x4_t vacc2x4 = vacc0x4;
    int32x4_t vacc2x5 = vacc0x5;
    int32x4_t vacc2x6 = vacc0x6;
    int32x4_t vacc2x7 = vacc0x7;
    int32x4_t vacc3x0 = vacc0x0;
    int32x4_t vacc3x1 = vacc0x1;
    int32x4_t vacc3x2 = vacc0x2;
    int32x4_t vacc3x3 = vacc0x3;
    int32x4_t vacc3x4 = vacc0x4;
    int32x4_t vacc3x5 = vacc0x5;
    int32x4_t vacc3x6 = vacc0x6;
    int32x4_t vacc3x7 = vacc0x7;

    size_t k = kc;
    while (k >= 8 * sizeof(int8_t)) {
      const int8x8_t va0 = vld1_s8(a0); a0 += 8;
      const int8x8_t va1 = vld1_s8(a1); a1 += 8;
      const int8x8_t va2 = vld1_s8(a2); a2 += 8;
      const int8x8_t va3 = vld1_s8(a3); a3 += 8;

      const int8x8_t vbx0 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x0 = vmull_s8(vbx0, va0);
      vacc0x0 = vpadalq_s16(vacc0x0, vprod0x0);
      const int16x8_t vprod1x0 = vmull_s8(vbx0, va1);
      vacc1x0 = vpadalq_s16(vacc1x0, vprod1x0);
      const int16x8_t vprod2x0 = vmull_s8(vbx0, va2);
      vacc2x0 = vpadalq_s16(vacc2x0, vprod2x0);
      const int16x8_t vprod3x0 = vmull_s8(vbx0, va3);
      vacc3x0 = vpadalq_s16(vacc3x0, vprod3x0);
      const int8x8_t vbx1 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x1 = vmull_s8(vbx1, va0);
      vacc0x1 = vpadalq_s16(vacc0x1, vprod0x1);
      const int16x8_t vprod1x1 = vmull_s8(vbx1, va1);
      vacc1x1 = vpadalq_s16(vacc1x1, vprod1x1);
      const int16x8_t vprod2x1 = vmull_s8(vbx1, va2);
      vacc2x1 = vpadalq_s16(vacc2x1, vprod2x1);
      const int16x8_t vprod3x1 = vmull_s8(vbx1, va3);
      vacc3x1 = vpadalq_s16(vacc3x1, vprod3x1);
      const int8x8_t vbx2 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x2 = vmull_s8(vbx2, va0);
      vacc0x2 = vpadalq_s16(vacc0x2, vprod0x2);
      const int16x8_t vprod1x2 = vmull_s8(vbx2, va1);
      vacc1x2 = vpadalq_s16(vacc1x2, vprod1x2);
      const int16x8_t vprod2x2 = vmull_s8(vbx2, va2);
      vacc2x2 = vpadalq_s16(vacc2x2, vprod2x2);
      const int16x8_t vprod3x2 = vmull_s8(vbx2, va3);
      vacc3x2 = vpadalq_s16(vacc3x2, vprod3x2);
      const int8x8_t vbx3 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x3 = vmull_s8(vbx3, va0);
      vacc0x3 = vpadalq_s16(vacc0x3, vprod0x3);
      const int16x8_t vprod1x3 = vmull_s8(vbx3, va1);
      vacc1x3 = vpadalq_s16(vacc1x3, vprod1x3);
      const int16x8_t vprod2x3 = vmull_s8(vbx3, va2);
      vacc2x3 = vpadalq_s16(vacc2x3, vprod2x3);
      const int16x8_t vprod3x3 = vmull_s8(vbx3, va3);
      vacc3x3 = vpadalq_s16(vacc3x3, vprod3x3);
      const int8x8_t vbx4 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x4 = vmull_s8(vbx4, va0);
      vacc0x4 = vpadalq_s16(vacc0x4, vprod0x4);
      const int16x8_t vprod1x4 = vmull_s8(vbx4, va1);
      vacc1x4 = vpadalq_s16(vacc1x4, vprod1x4);
      const int16x8_t vprod2x4 = vmull_s8(vbx4, va2);
      vacc2x4 = vpadalq_s16(vacc2x4, vprod2x4);
      const int16x8_t vprod3x4 = vmull_s8(vbx4, va3);
      vacc3x4 = vpadalq_s16(vacc3x4, vprod3x4);
      const int8x8_t vbx5 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x5 = vmull_s8(vbx5, va0);
      vacc0x5 = vpadalq_s16(vacc0x5, vprod0x5);
      const int16x8_t vprod1x5 = vmull_s8(vbx5, va1);
      vacc1x5 = vpadalq_s16(vacc1x5, vprod1x5);
      const int16x8_t vprod2x5 = vmull_s8(vbx5, va2);
      vacc2x5 = vpadalq_s16(vacc2x5, vprod2x5);
      const int16x8_t vprod3x5 = vmull_s8(vbx5, va3);
      vacc3x5 = vpadalq_s16(vacc3x5, vprod3x5);
      const int8x8_t vbx6 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x6 = vmull_s8(vbx6, va0);
      vacc0x6 = vpadalq_s16(vacc0x6, vprod0x6);
      const int16x8_t vprod1x6 = vmull_s8(vbx6, va1);
      vacc1x6 = vpadalq_s16(vacc1x6, vprod1x6);
      const int16x8_t vprod2x6 = vmull_s8(vbx6, va2);
      vacc2x6 = vpadalq_s16(vacc2x6, vprod2x6);
      const int16x8_t vprod3x6 = vmull_s8(vbx6, va3);
      vacc3x6 = vpadalq_s16(vacc3x6, vprod3x6);
      const int8x8_t vbx7 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x7 = vmull_s8(vbx7, va0);
      vacc0x7 = vpadalq_s16(vacc0x7, vprod0x7);
      const int16x8_t vprod1x7 = vmull_s8(vbx7, va1);
      vacc1x7 = vpadalq_s16(vacc1x7, vprod1x7);
      const int16x8_t vprod2x7 = vmull_s8(vbx7, va2);
      vacc2x7 = vpadalq_s16(vacc2x7, vprod2x7);
      const int16x8_t vprod3x7 = vmull_s8(vbx7, va3);
      vacc3x7 = vpadalq_s16(vacc3x7, vprod3x7);

      k -= 8 * sizeof(int8_t);
    }
    if XNN_UNLIKELY(k != 0) {
      const int8x8_t va0 = vld1_s8(a0); a0 += k;
      const int8x8_t va1 = vld1_s8(a1); a1 += k;
      const int8x8_t va2 = vld1_s8(a2); a2 += k;
      const int8x8_t va3 = vld1_s8(a3); a3 += k;

      const int8x8_t vbx0 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x0 = vmull_s8(vbx0, va0);
      vacc0x0 = vpadalq_s16(vacc0x0, vprod0x0);
      const int16x8_t vprod1x0 = vmull_s8(vbx0, va1);
      vacc1x0 = vpadalq_s16(vacc1x0, vprod1x0);
      const int16x8_t vprod2x0 = vmull_s8(vbx0, va2);
      vacc2x0 = vpadalq_s16(vacc2x0, vprod2x0);
      const int16x8_t vprod3x0 = vmull_s8(vbx0, va3);
      vacc3x0 = vpadalq_s16(vacc3x0, vprod3x0);
      const int8x8_t vbx1 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x1 = vmull_s8(vbx1, va0);
      vacc0x1 = vpadalq_s16(vacc0x1, vprod0x1);
      const int16x8_t vprod1x1 = vmull_s8(vbx1, va1);
      vacc1x1 = vpadalq_s16(vacc1x1, vprod1x1);
      const int16x8_t vprod2x1 = vmull_s8(vbx1, va2);
      vacc2x1 = vpadalq_s16(vacc2x1, vprod2x1);
      const int16x8_t vprod3x1 = vmull_s8(vbx1, va3);
      vacc3x1 = vpadalq_s16(vacc3x1, vprod3x1);
      const int8x8_t vbx2 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x2 = vmull_s8(vbx2, va0);
      vacc0x2 = vpadalq_s16(vacc0x2, vprod0x2);
      const int16x8_t vprod1x2 = vmull_s8(vbx2, va1);
      vacc1x2 = vpadalq_s16(vacc1x2, vprod1x2);
      const int16x8_t vprod2x2 = vmull_s8(vbx2, va2);
      vacc2x2 = vpadalq_s16(vacc2x2, vprod2x2);
      const int16x8_t vprod3x2 = vmull_s8(vbx2, va3);
      vacc3x2 = vpadalq_s16(vacc3x2, vprod3x2);
      const int8x8_t vbx3 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x3 = vmull_s8(vbx3, va0);
      vacc0x3 = vpadalq_s16(vacc0x3, vprod0x3);
      const int16x8_t vprod1x3 = vmull_s8(vbx3, va1);
      vacc1x3 = vpadalq_s16(vacc1x3, vprod1x3);
      const int16x8_t vprod2x3 = vmull_s8(vbx3, va2);
      vacc2x3 = vpadalq_s16(vacc2x3, vprod2x3);
      const int16x8_t vprod3x3 = vmull_s8(vbx3, va3);
      vacc3x3 = vpadalq_s16(vacc3x3, vprod3x3);
      const int8x8_t vbx4 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x4 = vmull_s8(vbx4, va0);
      vacc0x4 = vpadalq_s16(vacc0x4, vprod0x4);
      const int16x8_t vprod1x4 = vmull_s8(vbx4, va1);
      vacc1x4 = vpadalq_s16(vacc1x4, vprod1x4);
      const int16x8_t vprod2x4 = vmull_s8(vbx4, va2);
      vacc2x4 = vpadalq_s16(vacc2x4, vprod2x4);
      const int16x8_t vprod3x4 = vmull_s8(vbx4, va3);
      vacc3x4 = vpadalq_s16(vacc3x4, vprod3x4);
      const int8x8_t vbx5 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x5 = vmull_s8(vbx5, va0);
      vacc0x5 = vpadalq_s16(vacc0x5, vprod0x5);
      const int16x8_t vprod1x5 = vmull_s8(vbx5, va1);
      vacc1x5 = vpadalq_s16(vacc1x5, vprod1x5);
      const int16x8_t vprod2x5 = vmull_s8(vbx5, va2);
      vacc2x5 = vpadalq_s16(vacc2x5, vprod2x5);
      const int16x8_t vprod3x5 = vmull_s8(vbx5, va3);
      vacc3x5 = vpadalq_s16(vacc3x5, vprod3x5);
      const int8x8_t vbx6 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x6 = vmull_s8(vbx6, va0);
      vacc0x6 = vpadalq_s16(vacc0x6, vprod0x6);
      const int16x8_t vprod1x6 = vmull_s8(vbx6, va1);
      vacc1x6 = vpadalq_s16(vacc1x6, vprod1x6);
      const int16x8_t vprod2x6 = vmull_s8(vbx6, va2);
      vacc2x6 = vpadalq_s16(vacc2x6, vprod2x6);
      const int16x8_t vprod3x6 = vmull_s8(vbx6, va3);
      vacc3x6 = vpadalq_s16(vacc3x6, vprod3x6);
      const int8x8_t vbx7 = vld1_s8(w); w = (const void*) ((uintptr_t) w + 8 * sizeof(int8_t));

      const int16x8_t vprod0x7 = vmull_s8(vbx7, va0);
      vacc0x7 = vpadalq_s16(vacc0x7, vprod0x7);
      const int16x8_t vprod1x7 = vmull_s8(vbx7, va1);
      vacc1x7 = vpadalq_s16(vacc1x7, vprod1x7);
      const int16x8_t vprod2x7 = vmull_s8(vbx7, va2);
      vacc2x7 = vpadalq_s16(vacc2x7, vprod2x7);
      const int16x8_t vprod3x7 = vmull_s8(vbx7, va3);
      vacc3x7 = vpadalq_s16(vacc3x7, vprod3x7);
    }

    int32x4_t vacc0x0123 = combine4(vacc0x0, vacc0x1, vacc0x2, vacc0x3);
    int32x4_t vacc0x4567 = combine4(vacc0x4, vacc0x5, vacc0x6, vacc0x7);
    int32x4_t vacc1x0123 = combine4(vacc1x0, vacc1x1, vacc1x2, vacc1x3);
    int32x4_t vacc1x4567 = combine4(vacc1x4, vacc1x5, vacc1x6, vacc1x7);
    int32x4_t vacc2x0123 = combine4(vacc2x0, vacc2x1, vacc2x2, vacc2x3);
    int32x4_t vacc2x4567 = combine4(vacc2x4, vacc2x5, vacc2x6, vacc2x7);
    int32x4_t vacc3x0123 = combine4(vacc3x0, vacc3x1, vacc3x2, vacc3x3);
    int32x4_t vacc3x4567 = combine4(vacc3x4, vacc3x5, vacc3x6, vacc3x7);

    const int32x4_t vmultiplier = vld1q_dup_s32(&params->neon.multiplier);
    vacc0x0123 = vqrdmulhq_s32(vacc0x0123, vmultiplier);
    vacc0x4567 = vqrdmulhq_s32(vacc0x4567, vmultiplier);
    vacc1x0123 = vqrdmulhq_s32(vacc1x0123, vmultiplier);
    vacc1x4567 = vqrdmulhq_s32(vacc1x4567, vmultiplier);
    vacc2x0123 = vqrdmulhq_s32(vacc2x0123, vmultiplier);
    vacc2x4567 = vqrdmulhq_s32(vacc2x4567, vmultiplier);
    vacc3x0123 = vqrdmulhq_s32(vacc3x0123, vmultiplier);
    vacc3x4567 = vqrdmulhq_s32(vacc3x4567, vmultiplier);

    const int32x4_t vright_shift = vld1q_dup_s32(&params->neon.right_shift);
    const int32x4_t vzero_shift_mask = vreinterpretq_s32_u32(vceqq_s32(vright_shift, vmovq_n_s32(0)));
    vacc0x0123 = vsraq_n_s32(vacc0x0123, vbicq_s32(vacc0x0123, vzero_shift_mask), 31);
    vacc0x4567 = vsraq_n_s32(vacc0x4567, vbicq_s32(vacc0x4567, vzero_shift_mask), 31);
    vacc1x0123 = vsraq_n_s32(vacc1x0123, vbicq_s32(vacc1x0123, vzero_shift_mask), 31);
    vacc1x4567 = vsraq_n_s32(vacc1x4567, vbicq_s32(vacc1x4567, vzero_shift_mask), 31);
    vacc2x0123 = vsraq_n_s32(vacc2x0123, vbicq_s32(vacc2x0123, vzero_shift_mask), 31);
    vacc2x4567 = vsraq_n_s32(vacc2x4567, vbicq_s32(vacc2x4567, vzero_shift_mask), 31);
    vacc3x0123 = vsraq_n_s32(vacc3x0123, vbicq_s32(vacc3x0123, vzero_shift_mask), 31);
    vacc3x4567 = vsraq_n_s32(vacc3x4567, vbicq_s32(vacc3x4567, vzero_shift_mask), 31);

    vacc0x0123 = vrshlq_s32(vacc0x0123, vright_shift);
    vacc0x4567 = vrshlq_s32(vacc0x4567, vright_shift);
    vacc1x0123 = vrshlq_s32(vacc1x0123, vright_shift);
    vacc1x4567 = vrshlq_s32(vacc1x4567, vright_shift);
    vacc2x0123 = vrshlq_s32(vacc2x0123, vright_shift);
    vacc2x4567 = vrshlq_s32(vacc2x4567, vright_shift);
    vacc3x0123 = vrshlq_s32(vacc3x0123, vright_shift);
    vacc3x4567 = vrshlq_s32(vacc3x4567, vright_shift);

    const int16x8_t voutput_zero_point = vld1q_dup_s16(&params->neon.output_zero_point);
#if XNN_ARCH_ARM64
    const int16x8_t vacc0x01234567 = vqaddq_s16(vqmovn_high_s32(vqmovn_s32(vacc0x0123), vacc0x1), voutput_zero_point);
    const int16x8_t vacc1x01234567 = vqaddq_s16(vqmovn_high_s32(vqmovn_s32(vacc1x0123), vacc1x1), voutput_zero_point);
    const int16x8_t vacc2x01234567 = vqaddq_s16(vqmovn_high_s32(vqmovn_s32(vacc2x0123), vacc2x1), voutput_zero_point);
    const int16x8_t vacc3x01234567 = vqaddq_s16(vqmovn_high_s32(vqmovn_s32(vacc3x0123), vacc3x1), voutput_zero_point);

    int8x16_t vout0x01234567_1x01234567 = vqmovn_high_s16(vqmovn_s16(vacc0x01234567), vacc1x01234567);
    int8x16_t vout2x01234567_3x01234567 = vqmovn_high_s16(vqmovn_s16(vacc2x01234567), vacc3x01234567);
#else
    const int16x8_t vacc0x01234567 = vqaddq_s16(vcombine_s16(vqmovn_s32(vacc0x0123), vqmovn_s32(vacc0x4567)), voutput_zero_point);
    const int16x8_t vacc1x01234567 = vqaddq_s16(vcombine_s16(vqmovn_s32(vacc1x0123), vqmovn_s32(vacc1x4567)), voutput_zero_point);
    const int16x8_t vacc2x01234567 = vqaddq_s16(vcombine_s16(vqmovn_s32(vacc2x0123), vqmovn_s32(vacc2x4567)), voutput_zero_point);
    const int16x8_t vacc3x01234567 = vqaddq_s16(vcombine_s16(vqmovn_s32(vacc3x0123), vqmovn_s32(vacc3x4567)), voutput_zero_point);

    int8x16_t vout0x01234567_1x01234567 = vcombine_s8(vqmovn_s16(vacc0x01234567), vqmovn_s16(vacc1x01234567));
    int8x16_t vout2x01234567_3x01234567 = vcombine_s8(vqmovn_s16(vacc2x01234567), vqmovn_s16(vacc3x01234567));
#endif
    const int8x16_t voutput_min = vld1q_dup_s8(&params->neon.output_min);
    const int8x16_t voutput_max = vld1q_dup_s8(&params->neon.output_max);

    vout0x01234567_1x01234567 = vmaxq_s8(vout0x01234567_1x01234567, voutput_min);
    vout2x01234567_3x01234567 = vmaxq_s8(vout2x01234567_3x01234567, voutput_min);

    vout0x01234567_1x01234567 = vminq_s8(vout0x01234567_1x01234567, voutput_max);
    vout2x01234567_3x01234567 = vminq_s8(vout2x01234567_3x01234567, voutput_max);

    if (nc >= 8) {
      vst1_s8(c0 + 0, vget_low_s8(vout0x01234567_1x01234567));
      vst1_s8(c1 + 0, vget_high_s8(vout0x01234567_1x01234567));
      vst1_s8(c2 + 0, vget_low_s8(vout2x01234567_3x01234567));
      vst1_s8(c3 + 0, vget_high_s8(vout2x01234567_3x01234567));

      c0 = (int8_t*) ((uintptr_t) c0 + cn_stride);
      c1 = (int8_t*) ((uintptr_t) c1 + cn_stride);
      c2 = (int8_t*) ((uintptr_t) c2 + cn_stride);
      c3 = (int8_t*) ((uintptr_t) c3 + cn_stride);

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);
      a2 = (const int8_t*) ((uintptr_t) a2 - kc);
      a3 = (const int8_t*) ((uintptr_t) a3 - kc);

      nc -= 8;
    } else {
      if (nc & 4) {
        vst1q_lane_u32(__builtin_assume_aligned(c0, 1), vreinterpretq_u32_s8(vout0x01234567_1x01234567), 0); c0 += 4;
        vst1q_lane_u32(__builtin_assume_aligned(c1, 1), vreinterpretq_u32_s8(vout0x01234567_1x01234567), 2); c1 += 4;
        vst1q_lane_u32(__builtin_assume_aligned(c2, 1), vreinterpretq_u32_s8(vout2x01234567_3x01234567), 0); c2 += 4;
        vst1q_lane_u32(__builtin_assume_aligned(c3, 1), vreinterpretq_u32_s8(vout2x01234567_3x01234567), 2); c3 += 4;
        vout0x01234567_1x01234567 = vextq_s8(vout0x01234567_1x01234567, vout0x01234567_1x01234567, 4);
        vout2x01234567_3x01234567 = vextq_s8(vout2x01234567_3x01234567, vout2x01234567_3x01234567, 4);
      }
      if (nc & 2) {
        vst1q_lane_u16(__builtin_assume_aligned(c0, 1), vreinterpretq_u16_s8(vout0x01234567_1x01234567), 0); c0 += 2;
        vst1q_lane_u16(__builtin_assume_aligned(c1, 1), vreinterpretq_u16_s8(vout0x01234567_1x01234567), 4); c1 += 2;
        vst1q_lane_u16(__builtin_assume_aligned(c2, 1), vreinterpretq_u16_s8(vout2x01234567_3x01234567), 0); c2 += 2;
        vst1q_lane_u16(__builtin_assume_aligned(c3, 1), vreinterpretq_u16_s8(vout2x01234567_3x01234567), 4); c3 += 2;
        vout0x01234567_1x01234567 = vextq_s8(vout0x01234567_1x01234567, vout0x01234567_1x01234567, 2);
        vout2x01234567_3x01234567 = vextq_s8(vout2x01234567_3x01234567, vout2x01234567_3x01234567, 2);
      }
      if (nc & 1) {
        vst1q_lane_s8(c0, vout0x01234567_1x01234567, 0);
        vst1q_lane_s8(c1, vout0x01234567_1x01234567, 8);
        vst1q_lane_s8(c2, vout2x01234567_3x01234567, 0);
        vst1q_lane_s8(c3, vout2x01234567_3x01234567, 8);
      }

      nc = 0;
    }
  } while (nc != 0);
}
