#include "types.h"

extern f32 lbl_801A7020[2];

struct fn_800284A0_Arg0 {
    u32 unk_0;
    u32 unk_4;
    f32 unk_8;
    u32 unk_c;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1c;
};

void fn_800284A0(struct fn_800284A0_Arg0 *arg0, u32 arg1, u32 arg2, f32 arg3) {
    f32 value;

    arg0->unk_0 = arg1;
    arg0->unk_4 = arg2;
    arg0->unk_8 = arg3;
    arg0->unk_c = 0;
    value = lbl_801A7020[0];
    arg0->unk_1c = value;
    arg0->unk_18 = value;
    arg0->unk_14 = value;
    arg0->unk_10 = value;
}
