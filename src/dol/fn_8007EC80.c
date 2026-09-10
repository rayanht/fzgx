#include "types.h"

typedef s32 (*fn_8007EC80_Fn0)(u32, u32, u32 *, u32);

struct fn_8007EC80_Arg0 {
    u32 unk_0;
    u8 pad_4[0x14];
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u8 pad_38[0x04];
    fn_8007EC80_Fn0 unk_3C;
    u8 pad_40[0x08];
    u32 unk_48;
};

s32 fn_8007EC80(struct fn_8007EC80_Arg0 *arg0, u32 *arg1, s32 arg2) {
    s32 result;

    arg0->unk_24 = arg0->unk_1C;
    arg0->unk_28 = arg0->unk_20;
    arg0->unk_28 -= arg0->unk_18 & arg0->unk_2C;
    arg0->unk_34 = arg0->unk_18;
    if (arg2 == 1) {
        arg0->unk_28 = arg0->unk_20;
    }
    result = arg0->unk_3C(arg0->unk_0, arg0->unk_1C, &arg0->unk_28, arg0->unk_48);
    if (result == 2) {
        arg0->unk_28 = 0;
    }
    if (arg1 != 0) {
        *arg1 = arg0->unk_28;
    }
    if (result != 0) {
        return result;
    }
    arg0->unk_18 += arg0->unk_28;
    return 0;
}
