#include "types.h"

struct fn_80074438_lbl_801A6D38_T {
    u8 pad_0[0xB10];
    u16 unk_B10;
    u16 unk_B12;
    u32 unk_B14;
    u8 unk_B18;
};

extern struct fn_80074438_lbl_801A6D38_T *lbl_801A6D38;
extern u32 fn_80034BB8(u32, u32, u32, u32);

void fn_80074438(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 v0;
    u32 v1;
    u32 t0;
    v0 = (arg0 & 0xFFFF);
    v1 = lbl_801A6D38->unk_B18;
    if (lbl_801A6D38->unk_B10 != v0 || lbl_801A6D38->unk_B12 != (arg1 & 0xFFFF) || (s32)lbl_801A6D38->unk_B14 != (s32)arg2 || lbl_801A6D38->unk_B18 != (arg3 & 0xFF)) {
    v1 = arg0;
    t0 = fn_80034BB8(v1, arg1, arg2, arg3);
    v1 = t0;
    v1 = (u32)lbl_801A6D38;
    *(u16 *)((u8 *)v1 + 2832) = arg0;
    *(u16 *)((u8 *)((u32)lbl_801A6D38) + 2834) = arg1;
    *(u32 *)((u8 *)((u32)lbl_801A6D38) + 2836) = arg2;
    *(u8 *)((u8 *)((u32)lbl_801A6D38) + 2840) = arg3;
    }
}
