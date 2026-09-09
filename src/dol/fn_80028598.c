#include "types.h"

extern u8 lbl_801299D0[256];
extern f32 lbl_801A7020[2];

struct fn_80028598_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    f32 unk_10;
    u32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    u32 unk_28;
};

void fn_80028598(struct fn_80028598_Arg0 *arg0) {
    f32 value;
    arg0->unk_4 = 14;
    arg0->unk_28 = 0;
    arg0->unk_8 = (u32)lbl_801299D0;
    arg0->unk_C = 64;
    value = lbl_801A7020[0];
    arg0->unk_10 = value;
    arg0->unk_14 = 0;
    arg0->unk_24 = value;
    arg0->unk_20 = value;
    arg0->unk_1C = value;
    arg0->unk_18 = value;
}
