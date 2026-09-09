#include "types.h"

struct fn_80065AD0_Arg0 {
    u8 pad_0[0x10];
    u32 unk_10;
};

extern u32 lbl_801A6410;
extern u32 lbl_801A6C7C;
extern void fn_80008E5C(u32, u32);

void fn_80065AD0(struct fn_80065AD0_Arg0 *arg0) {
    u32 v0;
    u32 v1;
    v0 = arg0->unk_10;
    v1 = (u32)arg0;
    if (v0 != 0) {
    v1 = lbl_801A6410;
    fn_80008E5C(v1, v0);
    }
    lbl_801A6C7C = 0;
}
