#include "types.h"

struct fn_800631EC_Entry {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
    u8 unk_3;
    u8 unk_4;
    u8 unk_5;
    u8 unk_6;
    u8 unk_7;
    u8 unk_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    u8 unk_C;
    u8 unk_D;
    u8 unk_E;
    u8 unk_F;
    u32 unk_10;
    u8 unk_14[16][4];
};

extern struct fn_800631EC_Entry lbl_80192D68[16];

void fn_800631EC(void) {
    u8 i;
    u8 j;

    for (i = 0; i < 16; i++) {
        lbl_80192D68[i].unk_0 = 0xff;
        lbl_80192D68[i].unk_1 = 0;
        lbl_80192D68[i].unk_3 = 0x7f;
        lbl_80192D68[i].unk_4 = 0x40;
        lbl_80192D68[i].unk_5 = 0x40;
        lbl_80192D68[i].unk_6 = 0x40;
        lbl_80192D68[i].unk_7 = 0x40;
        lbl_80192D68[i].unk_9 = 0x40;
        lbl_80192D68[i].unk_A = 0x40;
        lbl_80192D68[i].unk_B = 0;
        lbl_80192D68[i].unk_C = 0;
        lbl_80192D68[i].unk_D = 0;
        lbl_80192D68[i].unk_E = 0;
        lbl_80192D68[i].unk_F = 0;
        lbl_80192D68[i].unk_10 = 0;
        for (j = 0; j < 16; j++) {
            lbl_80192D68[i].unk_14[j][0] = 0;
            lbl_80192D68[i].unk_14[j][1] = 0;
            lbl_80192D68[i].unk_14[j][2] = 0xff;
            lbl_80192D68[i].unk_14[j][3] = 0xff;
        }
    }
}
