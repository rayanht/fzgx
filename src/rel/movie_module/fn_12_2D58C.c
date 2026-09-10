#include "types.h"

struct fn_12_2D58C_Copy64 { u32 a[16]; };

extern s32 fn_12_24990(u32);
extern s32 fn_12_24A88(void *, s32);

s32 fn_12_2D58C(u32 arg0, u32 arg1) {
    s32 t0;
    t0 = fn_12_24990(arg0);
    if (t0 != 0) {
    return fn_12_24A88(0, 0xFF000000 + 281);
    }
    *(struct fn_12_2D58C_Copy64 *)((u8 *)arg1 + 0) = *(struct fn_12_2D58C_Copy64 *)((u8 *)arg0 + 2380);
    return 0;
}
