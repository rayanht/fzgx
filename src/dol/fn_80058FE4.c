#include "types.h"

typedef void (*fn_80058FE4_Fn0)(u32);

extern u32 lbl_8018FF78[];

void fn_80058FE4(u32 arg0) {
    u32 *v0;
    u32 v1;
    v0 = lbl_8018FF78;
    v1 = (arg0 << 3);
    if (v0[v1 / 4] != 0) {
    ((fn_80058FE4_Fn0)v0[v1 / 4])(v0[v1 / 4 + 1]);
    }
}
