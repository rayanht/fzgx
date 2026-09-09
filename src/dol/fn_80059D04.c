#include "types.h"

typedef u32 (*fn_80059D04_Fn0)(u32, u32, u32);
struct fn_80059D04_lbl_8019017C {
    u32 unk_0;
    u8 pad_4[0x9F0];
};

extern struct fn_80059D04_lbl_8019017C lbl_8019017C[];
extern u32 lbl_80092634[];
extern u32 lbl_80190178[];

s32 fn_80059D04(s8 *arg0) {
    u32 v0;
    u32 t0;
    if (arg0 == 0) {
        if (lbl_80190178[0] != 0) {
            v0 = lbl_8019017C[0].unk_0;
            t0 = ((fn_80059D04_Fn0)lbl_80190178[0])(v0, (u32)&lbl_80092634, 0);
            v0 = t0;
        }
        return 0;
    }
    return arg0[1];
}
