#include "types.h"

extern const f64 lbl_801A78F0;
extern f64 fn_80087BA4(s32, f64, f64);
extern s32 fn_800868BC(f64 *);
extern f64 fn_80086C5C(f64, f64);

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

    quadrant = fn_800868BC(values);
    switch (quadrant & 3) {
    case 0:
        return fn_80087BA4(1, values[0], values[1]);
    case 1:
        return fn_80086C5C(values[0], values[1]);
    case 2:
        return -fn_80087BA4(1, values[0], values[1]);
    default:
        return -fn_80086C5C(values[0], values[1]);
    }
}
