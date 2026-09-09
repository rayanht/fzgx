#include "types.h"

struct fn_8006AA20_lbl_80199670_0_E4680 {
    u8 pad_0[0x4D];
    s8 unk_4D;
    u8 pad_4E[0x11FA];
};
struct fn_8006AA20_lbl_80199670 {
    struct fn_8006AA20_lbl_80199670_0_E4680 unk_0[1];
};

extern struct fn_8006AA20_lbl_80199670 lbl_80199670[];

void fn_8006AA20(u32 arg0, u32 arg1) {
    if ((s32)arg1 == 0) { return; }
    lbl_80199670[0].unk_0[arg0].unk_4D = -1;
}
