#include "types.h"

extern u32 lbl_8015ABD8[];
extern u32 lbl_801A6D0C;
extern u32 lbl_801A6D10;
extern u32 lbl_801A6D14;
extern u32 lbl_801A6D18;
extern u32 lbl_801A6D1C;
extern u32 lbl_801A6D20;
extern u32 lbl_801A6D24;
extern void fn_8007174C(u32, u32);

void *fn_80071484(u32 arg0) {
    s32 temp_r31;
    void *temp_r30;
    void *temp_r29;
    s32 temp_r28;

    temp_r28 = ((s32 (*)())((*(u32 *)((u8 *)(&lbl_801A6D24) + 0))))();
    if (((s32 (*)(u32, s32))((*(u32 *)((u8 *)(&lbl_801A6D20) + 0))))(arg0, temp_r28) == 0) {
        return NULL;
    }
    temp_r31 = ((s32 (*)(s32))((*(u32 *)((u8 *)(&lbl_801A6D1C) + 0))))(temp_r28);
    temp_r30 = ((void *(*)(s32))((*(u32 *)((u8 *)(&lbl_801A6D0C) + 0))))(((temp_r31 + 0x1F) & 0xFFFFFFE0) + 0x20);
    if (temp_r30 == NULL) {
        fn_8007174C((u32)lbl_8015ABD8, arg0);
    }
    temp_r29 = (void *)(((u32)temp_r30 + 0x3F) & 0xFFFFFFE0);
    ((s32 (*)(s32, void *, s32, s32))((*(u32 *)((u8 *)(&lbl_801A6D18) + 0))))(temp_r28, temp_r29, temp_r31, 0);
    ((s32 (*)(s32))((*(u32 *)((u8 *)(&lbl_801A6D14) + 0))))(temp_r28);
    ((s32 (*)(s32))((*(u32 *)((u8 *)(&lbl_801A6D10) + 0))))(temp_r28);
    *(u32 *)temp_r30 = *(u32 *)temp_r29;
    *(u32 *)((u8 *)temp_r30 + 4) = (u32)temp_r29 + 4;
    *(u32 *)((u8 *)temp_r30 + 8) = (u32)temp_r29;
    *(u32 *)((u8 *)temp_r30 + 12) = 0;
    return temp_r30;
}
