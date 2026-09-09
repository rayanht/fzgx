#include "types.h"

extern u8 lbl_80090A80[284];
extern void fn_800474E4(u32);

struct fn_8004BD5C_Arg0 {
    u8 pad_0[0x71];
    s8 unk_71;
};

s32 fn_8004BD5C(struct fn_8004BD5C_Arg0 *arg0) {
    if (arg0 == 0) {
        fn_800474E4((u32)&lbl_80090A80);
        return -1;
    }
    return arg0->unk_71;
}
