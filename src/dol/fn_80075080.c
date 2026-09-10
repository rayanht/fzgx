#include "types.h"
struct fn_80075080_Arg0 {
    u32 unk_0;
};
struct fn_80075080_lbl_8019F130 {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
};
extern f32 lbl_801A7484;
extern f64 lbl_801A7490;
extern struct fn_80075080_lbl_8019F130 lbl_8019F130[];
extern u32 fn_80072614(void *);
extern u32 fn_800725DC(void *);

struct FzgxCopy_4 { u32 words[1]; };
void fn_80075080(void *arg0) {
    struct FzgxCopy_4 loc_14;
    struct FzgxCopy_4 loc_10;
    u32 spC;
    u32 sp8;
    f32 temp_f31;
    f32 var_f4;
    f32 var_f5;
    f32 var_f6;
    s32 temp_r3;
    s32 var_r31;
    s32 var_r4;

    temp_r3 = *(s32 *)((u8 *)(arg0) + 0);
    var_r31 = 0;
    var_r4 = 0;
    if (temp_r3 & 8) {
        var_r4 = 1;
        var_r31 = 1;
    } else if (temp_r3 & 0x80) {
        var_r31 = 1;
    }
    temp_f31 = lbl_8019F130->unk_C;
    if (var_r4 != 0) {
        var_f4 = (f32) (*(u8 *)((u8 *)(arg0) + 8));
        var_f5 = (f32) (*(u8 *)((u8 *)(arg0) + 9));
        var_f6 = (f32) (*(u8 *)((u8 *)(arg0) + 10));
    } else {
        var_f4 = *(f32 *)((u8 *)(&lbl_801A7484) + 0);
        var_f5 = var_f4;
        var_f6 = var_f4;
    }
    (*(s8 *)((u8 *)(&loc_10) + 3)) = (s8) ((*(f32 *)((u8 *)(&lbl_801A7484) + 0)) * temp_f31);
    (*(s8 *)((u8 *)(&loc_10) + 0)) = (s8) (var_f4 * lbl_8019F130->unk_0);
    (*(s8 *)((u8 *)(&loc_10) + 1)) = (s8) (var_f5 * lbl_8019F130->unk_4);
    (*(s8 *)((u8 *)(&loc_10) + 2)) = (s8) (var_f6 * lbl_8019F130->unk_8);
    spC = loc_10.words[0];
    fn_80072614((void *)(&spC));
    if (var_r31 != 0) {
        (*(u8 *)((u8 *)(&loc_14) + 0)) = *(u8 *)((u8 *)(arg0) + 4);
        (*(u8 *)((u8 *)(&loc_14) + 1)) = *(u8 *)((u8 *)(arg0) + 5);
        (*(u8 *)((u8 *)(&loc_14) + 2)) = *(u8 *)((u8 *)(arg0) + 6);
    } else {
        (*(u8 *)((u8 *)(&loc_14) + 0)) = 0xFF;
        (*(u8 *)((u8 *)(&loc_14) + 1)) = 0xFF;
        (*(u8 *)((u8 *)(&loc_14) + 2)) = 0xFF;
    }
    (*(s8 *)((u8 *)(&loc_14) + 3)) = (s8) (temp_f31 * (f32) (*(u8 *)((u8 *)(arg0) + 17)));
    sp8 = loc_14.words[0];
    fn_800725DC((void *)(&sp8));
}
