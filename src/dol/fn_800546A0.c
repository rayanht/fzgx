#include "types.h"

typedef u32 (*fn_800546A0_Fn0)(u32, u32, u32);
typedef u32 (*fn_800546A0_Fn1)(u32);

struct fn_800546A0_Object {
    u32 vtable;
    u32 value;
};

extern u32 lbl_80187430[];
extern u32 lbl_80187434[80];
extern char lbl_80091C48[28];
extern char lbl_80091C64[26];

s32 fn_800546A0(struct fn_800546A0_Object *arg0) {
    s32 result = 3;

    if (arg0 == 0) {
        if (lbl_80187430[0] != 0) {
            ((fn_800546A0_Fn0)lbl_80187430[0])(lbl_80187434[0], (u32)&lbl_80091C48, 0);
        }
        return 3;
    } else if (*(u32 *)((u8 *)arg0->vtable + 44) != 0) {
        result = ((fn_800546A0_Fn1)*(u32 *)((u8 *)arg0->vtable + 44))(arg0->value);
    } else if (lbl_80187430[0] != 0) {
        ((fn_800546A0_Fn0)lbl_80187430[0])(lbl_80187434[0], (u32)&lbl_80091C64, 0);
    }

    return result;
}
