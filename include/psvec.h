#ifndef PSVEC_H
#define PSVEC_H

#include "types.h"

/* Paired-single vector kernels recovered from retail code (2026-09-15).
 *
 * Retail's x/y lanes are handled by psq_l/psq_st with a displacement and the
 * z lane by lfs/stfs. MWCC's __vec2x32float__ type only ever emits the indexed
 * psq_lx/psq_stx forms, so the displacement form can come only from inline
 * assembly inlined into the caller; the compiler then allocates the registers
 * and schedules these instructions together with the surrounding code, which
 * is what the retail streams show. Pointers are untyped so every per-block Vec
 * typedef can be passed without a cast. */

/* ab = a - b */
static inline void psvec_sub(const register void *a, const register void *b, register void *ab) {
    register f32 axy, bxy, az, bz;
    asm {
        psq_l axy, 0(a), 0, 0
        psq_l bxy, 0(b), 0, 0
        lfs az, 8(a)
        lfs bz, 8(b)
        ps_sub axy, axy, bxy
        fsubs az, az, bz
        psq_st axy, 0(ab), 0, 0
        stfs az, 8(ab)
    }
}

/* ab = a + b */
static inline void psvec_add(const register void *a, const register void *b, register void *ab) {
    register f32 axy, bxy, az, bz;
    asm {
        psq_l axy, 0(a), 0, 0
        psq_l bxy, 0(b), 0, 0
        lfs az, 8(a)
        lfs bz, 8(b)
        ps_add axy, axy, bxy
        fadds az, az, bz
        psq_st axy, 0(ab), 0, 0
        stfs az, 8(ab)
    }
}

/* dst = a * s */
static inline void psvec_scale(const register void *a, register f32 s, register void *dst) {
    register f32 axy, az;
    asm {
        psq_l axy, 0(a), 0, 0
        lfs az, 8(a)
        ps_muls0 axy, axy, s
        fmuls az, az, s
        psq_st axy, 0(dst), 0, 0
        stfs az, 8(dst)
    }
}

/* dst = acc + v * s (retail loads the accumulator first: fn_1_236CC) */
static inline void psvec_scale_add(const register void *acc, const register void *v, register f32 s, register void *dst) {
    register f32 axy, vxy, az, vz;
    asm {
        psq_l axy, 0(acc), 0, 0
        psq_l vxy, 0(v), 0, 0
        lfs az, 8(acc)
        lfs vz, 8(v)
        ps_madds0 axy, vxy, s, axy
        fmadds az, vz, s, az
        psq_st axy, 0(dst), 0, 0
        stfs az, 8(dst)
    }
}

/* d = a - b; out = b + d * s (the interpolation kernel: fn_1_115BE8, fn_1_108A90) */
static inline void psvec_sub_scale_add(const register void *a, const register void *b, register f32 s, register void *d, register void *out) {
    register f32 axy, bxy, az, bz;
    asm {
        psq_l axy, 0(a), 0, 0
        psq_l bxy, 0(b), 0, 0
        lfs az, 8(a)
        lfs bz, 8(b)
        ps_sub axy, axy, bxy
        fsubs az, az, bz
        psq_st axy, 0(d), 0, 0
        stfs az, 8(d)
        ps_madds0 bxy, axy, s, bxy
        fmadds bz, az, s, bz
        psq_st bxy, 0(out), 0, 0
        stfs bz, 8(out)
    }
}

/* dst = (x, y, z). The parameters are declared z, y, x: an inlined asm block's
 * register parameters take f0, f1, f2 in declaration order, and retail merges
 * x from f2 with y from f1 while z sits in f0 (fn_1_2A694). */
static inline void psvec_set(register void *dst, register f32 z, register f32 y, register f32 x) {
    asm {
        ps_merge00 x, x, y
        psq_st x, 0(dst), 0, 0
        stfs z, 8(dst)
    }
}

#endif
