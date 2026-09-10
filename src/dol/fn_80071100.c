#include "types.h"

typedef u32 (*fn_80071100_Fn0)(u32, u32, u32);

extern u32 fn_80078DA8(u32, u32, u32);
extern u32 lbl_8015AB70[];
extern u32 lbl_8015ABCC[];
extern u32 lbl_801A6D0C;
extern void fn_8007174C(u32, u32);

u32 fn_80071100(u32 arg0, u32 arg1, u32 arg2) {
    s32 flag;
    u32 arg2_local;
    u32 arg0_local;

    flag = 0;
    arg2_local = arg2;
    arg0_local = arg0;
    if (arg1 == 0) {
        arg1 = ((fn_80071100_Fn0)lbl_801A6D0C)(32, arg1, arg2_local);
        if (arg1 == 0) {
            fn_8007174C((u32)&lbl_8015AB70, (u32)&lbl_8015ABCC);
        }
        flag = 1;
    }
    fn_80078DA8(arg1, arg0_local, arg2_local);
    if (flag == 0) {
        *(u32 *)((u8 *)arg1 + 16) = (*(u32 *)((u8 *)arg1 + 16) | 1);
    }
    return arg1;
}
