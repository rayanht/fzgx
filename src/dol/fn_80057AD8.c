#include "types.h"

typedef void (*fn_80057AD8_Fn0)(u32, s32);

struct fn_80057AD8_Arg0 {
    u8 pad_0[0xC];
    u32 unk_C;
    u8 pad_10[0xC];
    fn_80057AD8_Fn0 unk_1C;
    u32 unk_20;
};

s32 fn_80057AD8(struct fn_80057AD8_Arg0 *arg0, s32 arg1) {
    if (arg1 == 1) {
        return arg0->unk_C;
    } else if (arg1 == 0) {
        return 0;
    } else {
        if (arg0->unk_1C != 0) {
            arg0->unk_1C(arg0->unk_20, -3);
        }
        return 0;
    }
}
