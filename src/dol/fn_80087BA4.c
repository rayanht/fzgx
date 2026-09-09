#include "types.h"

extern f64 lbl_801A7838;
extern f64 lbl_801A7840;
extern f64 lbl_801A7848;
extern f64 lbl_801A7850;
extern f64 lbl_801A7858;
extern f64 lbl_801A7860;
extern f64 lbl_801A7868;

f64 fn_80087BA4(f64 x, f64 y, u32 mode) {
    union {
        f64 d;
        struct {
            u32 hi;
            u32 lo;
        } words;
    } value;
    f64 z;
    f64 x2;
    f64 x3;
    f64 t;
    f64 p;

    value.d = x;
    if ((s32)(value.words.hi & 0x7fffffff) < (s32)0x3e400000) {
        if ((s32)x == 0) {
            return x;
        }
    }

    z = value.d;
    x2 = z * z;
    x3 = x2 * z;
    p = x2 * ((x2 * ((lbl_801A7858 * x2) + lbl_801A7850)) + lbl_801A7848) + lbl_801A7840;
    p = x2 * p + lbl_801A7838;

    if ((s32)mode == 0) {
        p = x3 * (x2 * p + lbl_801A7860) + z;
        return p;
    } else {
        f64 t;
        t = x3 * p;
        return z - ((x2 * (lbl_801A7868 * y - t) - y) - lbl_801A7860 * x3);
    }
}
