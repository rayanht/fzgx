#include "types.h"

struct fn_8007423C_lbl_801A6D38_T {
    u8 pad_0[0xAFC];
    u16 unk_AFC;
    u16 unk_AFE;
    u16 unk_B00;
    u16 unk_B02;
};

extern struct fn_8007423C_lbl_801A6D38_T *lbl_801A6D38;
extern u32 GXSetDispCopySrc(u32, u32, u32, u32);

void fn_8007423C(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 v0;
    u32 v1;
    u32 t0;
    v0 = (arg0 & 0xFFFF);
    v1 = lbl_801A6D38->unk_B02;
    if (lbl_801A6D38->unk_AFC != v0 || lbl_801A6D38->unk_AFE != (arg1 & 0xFFFF) || lbl_801A6D38->unk_B00 != (arg2 & 0xFFFF) || lbl_801A6D38->unk_B02 != (arg3 & 0xFFFF)) {
    v1 = arg0;
    t0 = GXSetDispCopySrc(v1, arg1, arg2, arg3);
    v1 = t0;
    v1 = (u32)lbl_801A6D38;
    *(u16 *)((u8 *)v1 + 2812) = arg0;
    *(u16 *)((u8 *)((u32)lbl_801A6D38) + 2814) = arg1;
    *(u16 *)((u8 *)((u32)lbl_801A6D38) + 2816) = arg2;
    *(u16 *)((u8 *)((u32)lbl_801A6D38) + 2818) = arg3;
    }
}
