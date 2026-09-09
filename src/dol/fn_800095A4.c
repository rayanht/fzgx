#include "types.h"

extern u32 lbl_801A6730;
extern u32 lbl_8015BE40[40];
extern u32 lbl_8015BEE0[8];
extern u32 lbl_801A6410;
extern u32 lbl_801A6744;
extern u32 lbl_801A6740;
extern u32 lbl_801A673C;
extern u32 lbl_801A6738;

void fn_800095A4(void) {
    if ((s32)lbl_801A6730 != -1) {
        lbl_8015BE40[lbl_801A6730 * 5] = lbl_801A6410;
        lbl_8015BE40[lbl_801A6730 * 5 + 1] = lbl_801A6744;
        lbl_8015BE40[lbl_801A6730 * 5 + 2] = lbl_801A6740;
        lbl_8015BE40[lbl_801A6730 * 5 + 3] = lbl_801A673C;
        lbl_8015BE40[lbl_801A6730 * 5 + 4] = lbl_801A6738;
        lbl_801A6410 = lbl_8015BEE0[0];
        lbl_801A6744 = lbl_8015BEE0[1];
        lbl_801A6740 = lbl_8015BEE0[2];
        lbl_801A673C = lbl_8015BEE0[3];
        lbl_801A6738 = lbl_8015BEE0[4];
    }
}
