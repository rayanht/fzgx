#include "types.h"

extern u32 MWSFSVM_Error(u32, ...);
extern u32 fn_12_3A36C(u32);
extern u32 lbl_12_rodata_1118;

u32 fn_12_33874(u32 arg0) {
    u32 v0;
    u32 t0, t1;
    t0 = fn_12_3A36C(arg0);
    v0 = t0;
    if ((s32)t0 == 0) {
    v0 = (u32)&lbl_12_rodata_1118;
    t1 = MWSFSVM_Error((u32)v0);
    v0 = t1;
    v0 = 0;
    } else {
    v0 = *(u32 *)((u8 *)arg0 + 132);
    }
    return v0;
}
