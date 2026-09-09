#include "types.h"

typedef u32 (*fn_8005676C_Fn0)(u32, u32);
struct fn_8005676C_lbl_80188A78 {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};

extern struct fn_8005676C_lbl_80188A78 lbl_80188A78[];

void fn_8005676C(void) {
    u32 v0;
    u32 t0;
    if (lbl_80188A78[0].unk_0 != 0) {
    v0 = lbl_80188A78[0].unk_4;
    t0 = ((fn_8005676C_Fn0)lbl_80188A78[0].unk_0)(v0, lbl_80188A78[0].unk_8);
    v0 = t0;
    }
}
