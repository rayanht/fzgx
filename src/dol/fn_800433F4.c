#include "types.h"

typedef u32 (*fn_800433F4_Fn0)(u32, u32);

extern u32 lbl_8017A284[];

struct fn_800433F4_Arg0 {
    u8 pad_0[0xB0];
    u32 unk_B0;
};

void fn_800433F4(struct fn_800433F4_Arg0 *arg0, u32 arg1) {
    u32 unk_1;

    unk_1 = arg0->unk_B0;
    if (unk_1 != 0) {
        ((fn_800433F4_Fn0)lbl_8017A284[0])(unk_1, arg1);
    }
}
