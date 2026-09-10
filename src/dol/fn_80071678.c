#include "types.h"
typedef u32 (*fn_80071678_Fn0)(u32, u32);
extern u32 lbl_8015ABCC[];
extern u32 lbl_8015ABD8[];
extern u32 lbl_801A6D0C;
extern void fn_8007174C(u32, u32);


void *fn_80071678(s32 *arg0, void *arg1) {
    s32 var_r4;
    void *var_r31;

    var_r31 = (void *)(arg1);
    var_r4 = 0;
    if (var_r31 == NULL) {
        var_r31 = (void *)(((void *(*)(s32))((*(u32 *)((u8 *)(&lbl_801A6D0C) + 0))))(0x20));
        if (var_r31 == NULL) {
            fn_8007174C((u32)(lbl_8015ABD8), (u32)(lbl_8015ABCC));
        }
        var_r4 = 1;
    }
    (*(s32 *)((u8 *)(var_r31) + 0)) = (s32) (*(s32 *)((u8 *)(arg0) + 0));
    (*(void **)((u8 *)(var_r31) + 4)) = (void *)((void *) ((u8 *)(arg0) + 4));
    (*(s32 **)((u8 *)(var_r31) + 8)) = (s32 *)(arg0);
    if (var_r4 == 0) {
        (*(s32 *)((u8 *)(var_r31) + 12)) = 1;
    } else {
        (*(s32 *)((u8 *)(var_r31) + 12)) = 0;
    }
    return var_r31;
}
