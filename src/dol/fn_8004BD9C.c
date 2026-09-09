#include "types.h"

extern u32 fn_800474E4(u32);
extern u8 lbl_80090B9C[196];

struct fn_8004BD9C_Arg0 {
    u8 pad_0[0x60];
    s16 unk_60;
};

s32 fn_8004BD9C(struct fn_8004BD9C_Arg0 *arg0) {
    if (arg0 == 0) {
        fn_800474E4((u32)&lbl_80090B9C);
        return -1;
    }
    return arg0->unk_60;
}
