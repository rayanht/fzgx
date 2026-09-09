#include "types.h"
struct fn_80077384_Arg0 {
    u32 unk_0;
};
struct fn_80077384_lbl_801A3220 {
    u8 pad_0[0x2];
    u8 unk_2;    u8 pad_3[0x5D];
};
extern f32 lbl_801A7488;
extern struct fn_80077384_lbl_801A3220 lbl_801A3220[];
extern u32 lbl_8019F130[];
extern u32 lbl_801A6D64;
extern u32 lbl_801A6D74;
extern void fn_800747D0(u32, u32, u32, u32, u32, u32, u32);

void fn_80077384(s32 *arg0) {
    u32 var_r6;

    if ((*(s32 *)((u8 *)(arg0) + 0)) & 0x100) {
        if ((u8) lbl_801A3220->unk_2 != 4) {
            lbl_801A3220->unk_2 = 4;
            if ((*(f32 *)((u8 *)(&lbl_801A7488) + 0)) == (*(f32 *)((u8 *)(lbl_8019F130) + 12))) {
                var_r6 = 1;
            } else {
                var_r6 = 0;
            }
            fn_800747D0(2U, 0U, 0U, var_r6, 0U, 0U, 2U);
            fn_800747D0(0U, 1U, 0U, 1U, *(u32 *)((u8 *)(&lbl_801A6D74) + 0), 2U, *(u32 *)((u8 *)(&lbl_801A6D64) + 0));
        }
    } else if ((u8) lbl_801A3220->unk_2 != 3) {
        lbl_801A3220->unk_2 = 3;
        fn_800747D0(2U, 0U, 0U, 0U, 0U, 0U, 2U);
        fn_800747D0(0U, 1U, 0U, 0U, *(u32 *)((u8 *)(&lbl_801A6D74) + 0), 2U, *(u32 *)((u8 *)(&lbl_801A6D64) + 0));
    }
}
