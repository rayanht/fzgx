#include "types.h"

extern u32 fn_8003D42C();

u32 fn_8003B798(u32 arg0, u32 arg1) {
    u32 v;
    u32 n;
    s32 i;

    v = fn_8003D42C(arg0, arg1);
    n = arg1 & 0xFF;
    if (n == 1) {
        return v;
    }
    if (n == 2) {
        return (v << 1) + fn_8003D42C(arg0);
    }
    if (n == 3) {
        v = (v << 1) + fn_8003D42C(arg0);
        return (v << 1) + fn_8003D42C(arg0);
    }
    v = (v << 1) + fn_8003D42C(arg0);
    v = (v << 1) + fn_8003D42C(arg0);
    v = (v << 1) + fn_8003D42C(arg0);
    if (n == 4) {
        return v;
    }
    for (i = 4; i < (s32)n; i++) {
        v = (v << 1) + fn_8003D42C(arg0);
    }
    return v;
}
