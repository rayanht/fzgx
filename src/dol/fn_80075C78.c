#include "types.h"

struct fn_80075C78_Arg0 {
    u32 unk_0;
    u8 pad_4[0x3C];
    u32 unk_40;
};

struct fn_80075C78_lbl_801A3220 {
    u8 pad_0[0x1C];
    u32 unk_1C;
    u32 unk_20;
};

extern struct fn_80075C78_lbl_801A3220 lbl_801A3220;
extern u32 lbl_801A6D5C;
extern u32 lbl_801A6D60;
extern void fn_800728A8(s32, s32, s32, s32);

void fn_80075C78(struct fn_80075C78_Arg0 *arg0) {
    struct fn_80075C78_lbl_801A3220 *p_lbl_801A3220;
    s32 v0;
    u32 v1;
    s32 v2;
    u32 unk_1;
    u32 unk_2;
    u32 v5;

    v0 = 4;
    v2 = 5;
    if ((s32)lbl_801A6D60 == -1) {
        v1 = arg0->unk_0;
        if ((v1 & 0x20) != 0) {
            v1 = arg0->unk_40;
            v0 = (v1 & 0xF);
        }
    } else {
        v0 = lbl_801A6D60;
    }
    if ((s32)lbl_801A6D5C == -1) {
        unk_1 = arg0->unk_0;
        if ((unk_1 & 0x40) != 0) {
            unk_2 = arg0->unk_40;
            v2 = ((unk_2 >> 4) & 0xF);
        }
    } else {
        v2 = lbl_801A6D5C;
    }
    p_lbl_801A3220 = (struct fn_80075C78_lbl_801A3220 *)&lbl_801A3220;
    if ((s32)p_lbl_801A3220->unk_1C != (s32)v0 ||
        (s32)p_lbl_801A3220->unk_20 != (s32)v2) {
        v5 = 1;
        fn_800728A8(v5, v0, v2, 0);
        p_lbl_801A3220->unk_1C = v0;
        v5 = (u32)&lbl_801A3220;
        *(u32 *)((u8 *)v5 + 32) = v2;
    }
}
