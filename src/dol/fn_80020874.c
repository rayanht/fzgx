#include "types.h"

struct fn_80020874_block {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u32 unk_3C;
};

extern struct fn_80020874_block lbl_8015D180[2];
extern struct fn_80020874_block lbl_8015D100[2];
extern u32 lbl_801A6AB8;

void fn_80020874(void) {
    u32 i;

    lbl_801A6AB8 = 0;
    for (i = 0; i < 2; i++) {
        lbl_8015D180[i].unk_0 = 0;
        lbl_8015D100[i].unk_0 = 0;
        lbl_8015D180[i].unk_4 = 0;
        lbl_8015D100[i].unk_4 = 0;
        lbl_8015D180[i].unk_8 = 0;
        lbl_8015D100[i].unk_8 = 0;
        lbl_8015D180[i].unk_C = 0;
        lbl_8015D100[i].unk_C = 0;
        lbl_8015D180[i].unk_10 = 0;
        lbl_8015D100[i].unk_10 = 0;
        lbl_8015D180[i].unk_14 = 0;
        lbl_8015D100[i].unk_14 = 0;
        lbl_8015D180[i].unk_18 = 0;
        lbl_8015D100[i].unk_18 = 0;
        lbl_8015D180[i].unk_1C = 0;
        lbl_8015D100[i].unk_1C = 0;
        lbl_8015D180[i].unk_20 = 0;
        lbl_8015D100[i].unk_20 = 0;
        lbl_8015D180[i].unk_24 = 0;
        lbl_8015D100[i].unk_24 = 0;
        lbl_8015D180[i].unk_28 = 0;
        lbl_8015D100[i].unk_28 = 0;
        lbl_8015D180[i].unk_2C = 0;
        lbl_8015D100[i].unk_2C = 0;
        lbl_8015D180[i].unk_30 = 0;
        lbl_8015D100[i].unk_30 = 0;
        lbl_8015D180[i].unk_34 = 0;
        lbl_8015D100[i].unk_34 = 0;
        lbl_8015D180[i].unk_38 = 0;
        lbl_8015D100[i].unk_38 = 0;
        lbl_8015D180[i].unk_3C = 0;
        lbl_8015D100[i].unk_3C = 0;
    }
}
