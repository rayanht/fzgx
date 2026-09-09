#include "types.h"

extern u32 fn_8004AC58(u32);
extern u32 fn_800565FC(u32, ...);
extern u32 lbl_80092188[];
extern u32 memset(u32, u32, u32);

u32 fn_80057114(u32 arg0) {
    u32 v0;
    u32 t0, t1, t2, t3;
    v0 = arg0;
    if (arg0 != 0) {
    if (arg0 == 0) {
    v0 = (u32)&lbl_80092188;
    t0 = fn_800565FC((u32)v0);
    v0 = t0;
    } else {
    if ((s8)*(u8 *)((u8 *)arg0 + 1) != 0) {
    *(u8 *)((u8 *)arg0 + 1) = 0;
    v0 = *(u32 *)((u8 *)arg0 + 40);
    if (v0 != 0 && (s32)*(u8 *)((u8 *)arg0 + 2) == 1) {
    t1 = fn_8004AC58(v0);
    v0 = t1;
    *(u8 *)((u8 *)arg0 + 2) = 0;
    }
    v0 = 0;
    *(u32 *)((u8 *)arg0 + 44) = v0;
    if (arg0 == 0) {
    v0 = (u32)&lbl_80092188;
    t2 = fn_800565FC((u32)v0);
    v0 = t2;
    } else {
    if ((s8)*(u8 *)((u8 *)arg0 + 1) == 0) {
    *(u32 *)((u8 *)arg0 + 28) = v0;
    *(u32 *)((u8 *)arg0 + 32) = v0;
    *(u32 *)((u8 *)arg0 + 36) = v0;
    }
    }
    *(u32 *)((u8 *)arg0 + 52) = 0;
    }
    }
    v0 = arg0;
    *(u8 *)((u8 *)arg0 + 0) = 0;
    t3 = memset(v0, 0, 568);
    v0 = t3;
    }
    return v0;
}
