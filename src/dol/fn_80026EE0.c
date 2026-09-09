#include "types.h"

struct fn_80026EE0_Arg0 {
    u8 pad_0[0x18];
    u32 unk_18;
};

extern u32 lbl_80176160[];
extern void fn_80025D5C(void *);

void fn_80026EE0(struct fn_80026EE0_Arg0 *arg0, s32 arg1) {
    u32 v0;
    v0 = (u32)((u8 *)&lbl_80176160 + (arg0->unk_18 * 96));
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 > 127) {
        arg1 = 127;
    }
    *(u32 *)((u8 *)v0 + 20) = arg1;
    fn_80025D5C((void *)v0);
    *(u32 *)((u8 *)v0 + 4) = (*(u32 *)((u8 *)v0 + 4) | 0x40000000);
}
