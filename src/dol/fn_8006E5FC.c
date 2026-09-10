#include "types.h"

extern f32 lbl_8006D0B4(f32);
extern const f32 lbl_801A73D4;
extern const f32 lbl_801A73D8;
extern const f32 lbl_801A73DC;
extern u32 lbl_80094E10[4];
extern f32 (*lbl_801A6D00)[4];

void fn_8006E5FC(f32 *arg0) {
    f32 q[4];
    u32 order[3];
    f32 t;
    f32 s;
    s32 i;
    s32 j;
    s32 k;
    f32 f;

    order[0] = lbl_80094E10[0];
    order[1] = lbl_80094E10[1];
    order[2] = lbl_80094E10[2];
    t = lbl_801A6D00[0][0] + lbl_801A6D00[1][1] + lbl_801A6D00[2][2];

    if (t > lbl_801A73D4) {
        s = lbl_8006D0B4(lbl_801A73D8 + t);
        f = lbl_801A73DC / s;
        arg0[3] = lbl_801A73DC * s;
        arg0[0] = f * (lbl_801A6D00[2][1] - lbl_801A6D00[1][2]);
        arg0[1] = f * (lbl_801A6D00[0][2] - lbl_801A6D00[2][0]);
        arg0[2] = f * (lbl_801A6D00[1][0] - lbl_801A6D00[0][1]);
    } else {
        i = 0;
        if (lbl_801A6D00[1][1] > lbl_801A6D00[0][0]) {
            i = 1;
        }
        if (lbl_801A6D00[2][2] > lbl_801A6D00[i][i]) {
            i = 2;
        }
        j = order[i];
        k = order[j];
        s = lbl_8006D0B4(lbl_801A73D8 + (lbl_801A6D00[i][i] - (lbl_801A6D00[j][j] + lbl_801A6D00[k][k])));
        q[i] = lbl_801A73DC * s;
        if (lbl_801A73D4 != s) {
            s = lbl_801A73DC / s;
        }
        q[3] = s * (lbl_801A6D00[k][j] - lbl_801A6D00[j][k]);
        q[j] = s * (lbl_801A6D00[j][i] + lbl_801A6D00[i][j]);
        q[k] = s * (lbl_801A6D00[k][i] + lbl_801A6D00[i][k]);
        arg0[0] = q[0];
        arg0[1] = q[1];
        arg0[2] = q[2];
        arg0[3] = q[3];
    }
}
