#include "types.h"

struct fn_800745A4_lbl_801A6D38_T {
    s32 unk_00;
    s32 unk_04;
    u32 unk_08;
    u8 unk_0C;
    u8 pad_0D[3];
    u32 unk_10;
};

extern struct fn_800745A4_lbl_801A6D38_T *lbl_801A6D38;
extern void fn_80033A7C(u32, u32, u32, u32, u32, u32);

void fn_800745A4(u32 arg0, s32 arg1, s32 arg2, u32 arg3, u32 arg4, u32 arg5) {
    struct fn_800745A4_lbl_801A6D38_T *p;
    p = (struct fn_800745A4_lbl_801A6D38_T *)((u8 *)lbl_801A6D38 + (arg0 << 5) + 0xB28);
    if (p->unk_00 != arg1 || p->unk_04 != arg2 || p->unk_08 != arg3 ||
        p->unk_0C != (arg4 & 0xFF) || p->unk_10 != arg5) {
        fn_80033A7C(arg0, arg1, arg2, arg3, arg4, arg5);
        p->unk_00 = arg1;
        p->unk_04 = arg2;
        p->unk_08 = arg3;
        p->unk_0C = arg4;
        p->unk_10 = arg5;
    }
}
