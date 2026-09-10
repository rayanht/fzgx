#include "types.h"

typedef u32 (*fn_800715A0_Fn0)(u32, u32);

extern u32 ARGetDMAStatus(void);
extern u32 ARStartDMA(u32, u32, u32, u32);
extern u32 lbl_8015ABC0[];
extern u32 lbl_8015ABD8[];
extern u32 lbl_801A6D0C;
extern void DCInvalidateRange(void *, u32);
extern void fn_8007174C(u32, u32);

void *fn_800715A0(u32 arg0, u32 arg1) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 t0, t3, t5;
    v0 = (arg1 + 31);
    v1 = (v0 & ~0x1F);
    t0 = ((fn_800715A0_Fn0)lbl_801A6D0C)((v1 + 32), arg1);
    v2 = t0;
    if (t0 == 0) {
        v2 = (u32)&lbl_8015ABD8;
        v3 = (u32)&lbl_8015ABC0;
        fn_8007174C((u32)v2, (u32)v3);
    }
    v4 = ((t0 + 63) & ~0x1F);
    DCInvalidateRange((void *)v4, v1);
    do {
        t3 = ARGetDMAStatus();
    } while (t3 != 0);
    ARStartDMA(1, v4, arg0, arg1);
    do {
        t5 = ARGetDMAStatus();
    } while (t5 != 0);
    *(u32 *)((u8 *)t0 + 0) = *(u32 *)((u8 *)v4 + 0);
    *(u32 *)((u8 *)t0 + 4) = (v4 + 4);
    *(u32 *)((u8 *)t0 + 8) = v4;
    *(u32 *)((u8 *)t0 + 12) = 0;
    return (void *)t0;
}
