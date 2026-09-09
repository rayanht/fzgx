#include "types.h"

struct fn_800433D0_Arg0 {
    u8 pad_0[0xB4];
    s32 unk_B4;
    s32 unk_B8;
};

void fn_800433D0(struct fn_800433D0_Arg0 *arg0, s32 value) {
    arg0->unk_B4 = value;
    arg0->unk_B8 = value / 96;
}
