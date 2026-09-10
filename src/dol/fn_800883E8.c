#include "types.h"

extern const f64 lbl_801A78F0;
extern f64 fn_80087BA4(s32, f64, f64);
extern s32 __ieee754_rem_pio2(f64 *);
extern f64 __kernel_cos(f64, f64);

f64 fn_800883E8(f64 angle) {
    union {
        f64 value;
        struct {
            s32 hi;
            u32 lo;
        } words;
    } bits;
    f64 values[2];
    s32 quadrant;

    bits.value = angle;
    if ((bits.words.hi & 0x7fffffff) <= 0x3fe921fb) {
        return fn_80087BA4(0, angle, lbl_801A78F0);
    }
    if ((bits.words.hi & 0x7fffffff) >= 0x7ff00000) {
        return angle - angle;
    }

    quadrant = __ieee754_rem_pio2(values);
    switch (quadrant & 3) {
    case 0:
        return fn_80087BA4(1, values[0], values[1]);
    case 1:
        return __kernel_cos(values[0], values[1]);
    case 2:
        return -fn_80087BA4(1, values[0], values[1]);
    default:
        return -__kernel_cos(values[0], values[1]);
    }
}
