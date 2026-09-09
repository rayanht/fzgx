#include "types.h"

struct fn_800289C0_Arg0 {
    u8 pad_0[0x8];
    s32 unk_8;
    s32 unk_C;
    s32 unk_10;
};

void fn_800289C0(struct fn_800289C0_Arg0 *arg0) {
    if (arg0->unk_10 == arg0->unk_C) {
        return;
    }
    arg0->unk_10 += arg0->unk_8;
    if (arg0->unk_8 > 0) {
        if (arg0->unk_10 > arg0->unk_C) {
            arg0->unk_10 = arg0->unk_C;
        }
    } else if (arg0->unk_8 < 0) {
        if (arg0->unk_10 < arg0->unk_C) {
            arg0->unk_10 = arg0->unk_C;
        }
    }
}
