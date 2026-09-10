#include "types.h"

struct fn_80076134_Mtx {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
};

extern struct fn_80076134_Mtx *lbl_801A6D00;
extern u8 lbl_801A3220[];
extern u8 lbl_8015AD10[];
extern const f32 lbl_801A7480;
extern const f32 lbl_801A7488;
extern const f32 lbl_801A748C;
extern const f32 lbl_801A749C;

extern void lbl_8006DAEC(void);
extern void lbl_8006DB30(void);
extern void lbl_8006E14C(f32);
extern void GXLoadTexMtxImm(void *, u32, u32);
extern void fn_8006F120(void *, void *);

void fn_80076134(void) {
    lbl_8006DAEC();
    lbl_801A6D00->unk_C = lbl_801A7480;
    lbl_801A6D00->unk_1C = lbl_801A7480;
    lbl_801A6D00->unk_2C = lbl_801A7480;
    GXLoadTexMtxImm(lbl_801A6D00, 30, 0);
    lbl_8006DB30();
    *(u32 *)(lbl_801A3220 + 0x3C) = 1;
    lbl_8006DAEC();
    fn_8006F120(lbl_8015AD10, lbl_801A3220 + 0x50);
    lbl_801A6D00->unk_C = lbl_801A748C;
    lbl_801A6D00->unk_10 = lbl_801A6D00->unk_10 * lbl_801A749C;
    lbl_801A6D00->unk_14 = lbl_801A6D00->unk_14 * lbl_801A749C;
    lbl_801A6D00->unk_18 = lbl_801A6D00->unk_18 * lbl_801A749C;
    lbl_801A6D00->unk_1C = lbl_801A748C;
    lbl_801A6D00->unk_20 = lbl_801A7480;
    lbl_801A6D00->unk_24 = lbl_801A7480;
    lbl_801A6D00->unk_28 = lbl_801A7480;
    lbl_801A6D00->unk_2C = lbl_801A7488;
    lbl_8006E14C(lbl_801A748C);
    GXLoadTexMtxImm(lbl_801A6D00, 64, 0);
    lbl_8006DB30();
}
