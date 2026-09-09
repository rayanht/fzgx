#include "types.h"

extern u32 fn_80079FA8(u32);
extern u32 fn_8007ADF0(u32, u32);

u32 fn_8007AB58(u32 arg0, u32 arg1) {
    u32 v0;
    u32 v2;
    u32 t0;
    u32 v1;
    u32 t1;
    v1 = (arg1 + 0x1f) & ~0x7;
    if (v1 < 0x10000) {
    v1 = 0x10000;
    }
    t0 = fn_80079FA8(v1);
    v2 = t0;
    if (t0 == 0) {
    v2 = 0;
    } else {
    t1 = fn_8007ADF0(v2, v1);
    v2 = t1;
    v2 = *(u32 *)((u8 *)arg0 + 0);
    if (v2 != 0) {
    *(u32 *)((u8 *)t0 + 0) = *(u32 *)((u8 *)v2 + 0);
    v2 = *(u32 *)((u8 *)t0 + 0);
    *(u32 *)((u8 *)v2 + 4) = t0;
    *(u32 *)((u8 *)t0 + 4) = *(u32 *)((u8 *)arg0 + 0);
    v2 = *(u32 *)((u8 *)arg0 + 0);
    *(u32 *)((u8 *)v2 + 0) = t0;
    *(u32 *)((u8 *)arg0 + 0) = t0;
    } else {
    *(u32 *)((u8 *)arg0 + 0) = t0;
    *(u32 *)((u8 *)t0 + 0) = t0;
    *(u32 *)((u8 *)t0 + 4) = t0;
    }
    v2 = t0;
    }
    return v2;
}
