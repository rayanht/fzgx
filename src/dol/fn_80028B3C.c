#include "types.h"

struct fn_80028B3C_Arg0 {
    u8 pad_0[0x8];
    f32 unk_8;
    f32 unk_C;
    f32 unk_10;
    f32 unk_14;
    u32 unk_18;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F;
    u16 unk_20;
    u16 unk_22;
    f32 unk_24;
    u32 unk_28;
};

extern u8 lbl_80129FD0[];
extern const f32 lbl_801A7048;
extern const f32 lbl_801A7050;
extern const f32 lbl_801A704C;
extern const f32 lbl_801A7054;
extern f32 lbl_801A6B98;
extern f32 lbl_801A6B9C;
extern u32 __cvt_fp2unsigned(f32);
extern u32 fn_80025EEC(void);

void fn_80028B3C(struct fn_80028B3C_Arg0 *arg0) {
    u8 *base;
    u32 idx8;
    u32 idxC;
    f32 a;

    base = lbl_80129FD0;
    if (arg0->unk_18 == 0) {
        return;
    }
    a = arg0->unk_8;
    if (a > lbl_801A7048) {
        idx8 = __cvt_fp2unsigned(lbl_801A704C * (a / lbl_801A7050));
    } else if (a < lbl_801A7048) {
        f32 t = lbl_801A704C * (a / lbl_801A7050);
        idx8 = __cvt_fp2unsigned(lbl_801A704C + t);
    } else {
        idx8 = 0;
    }
    a = arg0->unk_C;
    if (a > lbl_801A7048) {
        idxC = __cvt_fp2unsigned(lbl_801A704C * (a / lbl_801A7050));
    } else if (a < lbl_801A7048) {
        f32 t = lbl_801A704C * (a / lbl_801A7050);
        idxC = __cvt_fp2unsigned(lbl_801A704C + t);
    } else {
        idxC = 0;
    }
    arg0->unk_18 = 0;
    if (fn_80025EEC() == 3) {
        arg0->unk_1C = base[idx8 + 720];
    } else {
        arg0->unk_1C = base[idx8];
    }
    arg0->unk_1D = base[idx8 + 360];
    arg0->unk_20 = base[idx8 + 1080];
    arg0->unk_22 = base[idx8 + 1440];
    arg0->unk_1E = base[idxC + 1800];
    arg0->unk_24 = arg0->unk_14 / lbl_801A6B98;
    arg0->unk_28 = (s32)(lbl_801A7054 * (arg0->unk_10 / lbl_801A6B9C));
}
