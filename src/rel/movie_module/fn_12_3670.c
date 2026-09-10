#include "types.h"
extern f32 lbl_12_rodata_4EC;
extern u32 lbl_12_rodata_4F0;
extern void fn_12_309C(u32, u32, u32);


void fn_12_3670(void *arg0, f32 farg0, f32 farg1) {
    s32 var_r0;

    var_r0 = 1;
    if (farg1 <= farg0) {
        var_r0 = 0;
    }
    if ((farg1 - farg0) < (*(f32 *)((u8 *)(&lbl_12_rodata_4EC) + 0))) {
        var_r0 = 0;
    }
    if (var_r0 != 1) {
        fn_12_309C(0U, 0U, (u32)(&lbl_12_rodata_4F0));
    }
    (*(f32 *)((u8 *)(arg0) + 60)) = farg0;
    (*(f32 *)((u8 *)(arg0) + 64)) = farg1;
}
