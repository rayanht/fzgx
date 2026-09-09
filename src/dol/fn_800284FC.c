#include "types.h"

extern u8 lbl_801299D0[256];
extern f32 lbl_801A7020[2];

struct fn_800284FC_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 *unk_8;
    u32 unk_c;
    f32 unk_10;
    u32 unk_14;
    f32 unk_18;
    f32 unk_1c;
    f32 unk_20;
    f32 unk_24;
    u32 unk_28;
};

void fn_800284FC(struct fn_800284FC_Arg0 *arg0) {
    f32 zero;
    arg0->unk_4 = 7;
    arg0->unk_28 = 0;
    arg0->unk_8 = lbl_801299D0;
    arg0->unk_c = 64;
    zero = lbl_801A7020[0];
    arg0->unk_10 = zero;
    arg0->unk_14 = 0;
    arg0->unk_24 = zero;
    arg0->unk_20 = zero;
    arg0->unk_1c = zero;
    arg0->unk_18 = zero;
}
