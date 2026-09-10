#include "types.h"

extern u8 lbl_12_rodata_C0[212];
extern u32 fn_12_3074(void *arg0, void *arg1);
extern void fn_12_11A8(void *arg0, void *arg1, void *arg2);
extern u8 lbl_12_rodata_2BC[396];
extern void fn_12_309C(void *arg0, void *arg1, void *arg2);

void fn_12_132C(void *arg0, void *arg1, void *arg2) {
    s32 value;
    value = *(s32 *)arg1;
    if (*(s32 *)((u8 *)arg0 + 4) == 0) {
        *(u32 *)((u8 *)arg0 + 4) = fn_12_3074(arg1, lbl_12_rodata_C0);
    }
    switch (value) {
    case 3:
        fn_12_11A8(arg0, arg1, arg2);
        break;
    case 2:
    default:
        fn_12_309C(arg0, arg1, lbl_12_rodata_2BC);
        break;
    }
}
