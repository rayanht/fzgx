#include "types.h"

struct fn_80028A78_Arg0 {
    f32 *unk_0;
    u32 unk_4;
    f32 unk_8;
    u32 unk_C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
};

extern f32 lbl_801A7040;
extern u32 __cvt_fp2unsigned(f32);

void fn_80028A78(struct fn_80028A78_Arg0 *arg0) {
    f32 difference;
    f32 value;
    u32 index;

    arg0->unk_10 = arg0->unk_10 + arg0->unk_8;
    value = arg0->unk_10;
    if (value >= lbl_801A7040) {
        arg0->unk_10 = value - value;
        index = __cvt_fp2unsigned(value);
        arg0->unk_C = arg0->unk_C + index;
        arg0->unk_C = arg0->unk_C % arg0->unk_4;
        arg0->unk_14 = arg0->unk_18;
        arg0->unk_18 = arg0->unk_0[arg0->unk_C];
    }
    difference = arg0->unk_10 * (arg0->unk_14 - arg0->unk_18);
    arg0->unk_1C = arg0->unk_14 - difference;
}
