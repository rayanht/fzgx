#include "types.h"

typedef u32 (*fn_12_2E374_Fn0)(u32, u32, u32, u32);

extern u32 lbl_12_rodata_E10;
extern u32 lbl_12_rodata_E34;
extern void fn_12_24A88(void *, int);

void fn_12_2E374(u32 arg0, u32 arg1, u32 arg2) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t1;
    v0 = *(u32 *)((u8 *)arg0 + 0);
    v1 = (v0 << 3);
    v2 = (v0 << 2);
    v3 = *(u32 *)((u8 *)&lbl_12_rodata_E10 + v2);
    if (*(u32 *)((u8 *)((u8 *)&lbl_12_rodata_E34 + v1) + (*(u32 *)((u8 *)arg0 + 4) << 2)) == 0) {
    v3 = 0;
    fn_12_24A88((void *)v3, (0xFF000000 + 545));
    v3 = 0;
    *(u32 *)((u8 *)arg1 + 0) = v3;
    *(u32 *)((u8 *)arg2 + 0) = 1;
    } else {
    t1 = ((fn_12_2E374_Fn0)*(u32 *)((u8 *)((u8 *)&lbl_12_rodata_E34 + v1) + (*(u32 *)((u8 *)arg0 + 4) << 2)))(v3, arg0, arg1, arg2);
    v3 = t1;
    }
}
