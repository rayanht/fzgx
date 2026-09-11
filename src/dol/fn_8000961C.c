#include "types.h"

extern u32 lbl_801A6730;
extern u32 lbl_8015BE40[40];
extern u32 lbl_8015BEE0[8];
extern u32 lbl_801A6410;
extern u32 lbl_801A6744;
extern u32 lbl_801A6740;
extern u32 lbl_801A673C;
extern u32 lbl_801A6738;

s32 *fn_8000961C(s32 arg0) {
    s32 idx;
    s32 v0, v1, v2, v3, v4;
    s32 *p;

    idx = (s32)lbl_801A6730;
    if (idx != -1) {
        v0 = lbl_801A6410;
        v1 = lbl_801A6744;
        v2 = lbl_801A6740;
        v3 = lbl_801A673C;
        v4 = lbl_801A6738;
        lbl_8015BEE0[0] = v0;
        lbl_8015BEE0[1] = v1;
        lbl_8015BEE0[2] = v2;
        lbl_8015BEE0[3] = v3;
        lbl_8015BEE0[4] = v4;
        lbl_801A6410 = lbl_8015BE40[idx * 5];
        lbl_801A6744 = lbl_8015BE40[idx * 5 + 1];
        lbl_801A6740 = lbl_8015BE40[idx * 5 + 2];
        lbl_801A673C = lbl_8015BE40[idx * 5 + 3];
        lbl_801A6738 = lbl_8015BE40[idx * 5 + 4];
    }
    if (arg0 < 0 || arg0 >= (s32)lbl_801A6740) {
        if (idx != -1) {
            lbl_8015BE40[idx * 5] = lbl_801A6410;
            lbl_8015BE40[idx * 5 + 1] = lbl_801A6744;
            lbl_8015BE40[idx * 5 + 2] = lbl_801A6740;
            lbl_8015BE40[idx * 5 + 3] = lbl_801A673C;
            lbl_8015BE40[idx * 5 + 4] = lbl_801A6738;
            lbl_801A6410 = lbl_8015BEE0[0];
            lbl_801A6744 = lbl_8015BEE0[1];
            lbl_801A6740 = lbl_8015BEE0[2];
            lbl_801A673C = lbl_8015BEE0[3];
            lbl_801A6738 = lbl_8015BEE0[4];
        }
        return 0;
    }
    p = (s32 *)((u8 *)lbl_801A6744 + arg0 * 12);
    if (*p < 0) {
        if (idx != -1) {
            lbl_8015BE40[idx * 5] = lbl_801A6410;
            lbl_8015BE40[idx * 5 + 1] = lbl_801A6744;
            lbl_8015BE40[idx * 5 + 2] = lbl_801A6740;
            lbl_8015BE40[idx * 5 + 3] = lbl_801A673C;
            lbl_8015BE40[idx * 5 + 4] = lbl_801A6738;
            lbl_801A6410 = lbl_8015BEE0[0];
            lbl_801A6744 = lbl_8015BEE0[1];
            lbl_801A6740 = lbl_8015BEE0[2];
            lbl_801A673C = lbl_8015BEE0[3];
            lbl_801A6738 = lbl_8015BEE0[4];
        }
        return 0;
    }
    if (idx != -1) {
        lbl_8015BE40[idx * 5] = lbl_801A6410;
        lbl_8015BE40[idx * 5 + 1] = lbl_801A6744;
        lbl_8015BE40[idx * 5 + 2] = lbl_801A6740;
        lbl_8015BE40[idx * 5 + 3] = lbl_801A673C;
        lbl_8015BE40[idx * 5 + 4] = lbl_801A6738;
        lbl_801A6410 = lbl_8015BEE0[0];
        lbl_801A6744 = lbl_8015BEE0[1];
        lbl_801A6740 = lbl_8015BEE0[2];
        lbl_801A673C = lbl_8015BEE0[3];
        lbl_801A6738 = lbl_8015BEE0[4];
    }
    return p;
}
