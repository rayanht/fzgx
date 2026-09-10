#include "types.h"

typedef struct Fn80055DF4_Obj {
    u8 pad18[0x18];
    s32 max_value;
    s32 value;
} Fn80055DF4_Obj;

typedef u32 (*fn_80055DF4_Fn0)(u32, u32, u32);

extern u32 lbl_80091F7C[];
extern u32 lbl_801878C4[];
extern u32 lbl_801878C8[];

u32 fn_80055DF4(Fn80055DF4_Obj *arg0, s32 arg1, s32 arg2) {
    s32 value;
    s32 max_value;

    if (arg0 == 0) {
        if (lbl_801878C8[0] != 0) {
            ((fn_80055DF4_Fn0)lbl_801878C8[0])(lbl_801878C4[0], (u32)&lbl_80091F7C, 0);
        }
        return 0;
    }

    if (arg2 == 0) {
        arg0->value = arg1;
    } else if (arg2 == 2) {
        arg0->value = arg0->max_value + arg1;
    } else if (arg2 == 1) {
        arg0->value = arg0->value + arg1;
    }

    max_value = arg0->max_value;
    value = arg0->value;
    if (value < max_value) {
        max_value = value;
    }
    arg0->value = max_value;

    arg0->value = (arg0->value > 0) ? arg0->value : 0;
    return arg0->value;
}
