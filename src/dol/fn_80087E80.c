#include "types.h"

extern const f64 lbl_801A78A8;
extern f64 fn_80086C5C(f64, f64);
extern u32 fn_800868BC(f64 *, f64);
extern f64 fn_80087BA4(u32, f64, f64);

f64 fn_80087E80(f64 value) {
    f64 parts[2];
    s32 bits;
    u32 quadrant;

    bits = *(s32 *)&value;
    bits &= 0x7fffffff;
    if (bits <= 0x3fe921fb) {
        return fn_80086C5C(value, lbl_801A78A8);
    }
    if (bits >= 0x7ff00000) {
        return value - value;
    }

    quadrant = fn_800868BC(parts, value) & 3;
    switch (quadrant) {
    case 0:
        return fn_80086C5C(parts[0], parts[1]);
    case 1:
        return -fn_80087BA4(1, parts[0], parts[1]);
    case 2:
        return -fn_80086C5C(parts[0], parts[1]);
    default:
        return fn_80087BA4(1, parts[0], parts[1]);
    }
}
