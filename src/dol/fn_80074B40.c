#include "types.h"

extern u8 lbl_801A6D80[4];
extern u32 lbl_801A6D88[2];

void fn_80074B40(u8 *arg0) {
    if (arg0[0] != 0xFF || arg0[1] != 0xFF ||
        arg0[2] != 0xFF || arg0[3] != 0xFF) {
        lbl_801A6D88[0] = 1;
        lbl_801A6D80[0] = arg0[0];
        lbl_801A6D80[1] = arg0[1];
        lbl_801A6D80[2] = arg0[2];
        lbl_801A6D80[3] = arg0[3];
    } else {
        lbl_801A6D88[0] = 0;
        lbl_801A6D80[0] = 0xFF;
        lbl_801A6D80[1] = 0xFF;
        lbl_801A6D80[2] = 0xFF;
        lbl_801A6D80[3] = 0xFF;
    }
}
