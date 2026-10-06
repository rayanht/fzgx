#include "types.h"

struct fn_12_1F84_Arg0 {
    u8 pad_0[0x4];
    u32 unk_4;
    s32 unk_8;
    u8 pad_C[0x2c];
    u32 unk_38;
};

struct fn_12_1F84_Arg1 {
    u8 pad_0[0x4];
    u32 unk_4;
    s32 unk_8;
    s32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x8];
    u32 unk_24;
    u32 unk_28;
    u8 pad_2C[0x18];
    u32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x28];
    s32 unk_74;
};

extern s32 fn_12_308C(void);
extern u32 fn_12_309C(u32, u32, u32);
extern u32 fn_12_3D144(u32 *, u32 *);
extern u32 fn_12_3DCF0(u32 *, u32 *, u32);
extern u32 fn_12_3DF08(u32 *, u32 *);
extern f64 lbl_12_rodata_60[12];

u32 fn_12_1F84(struct fn_12_1F84_Arg0 *arg0, struct fn_12_1F84_Arg1 *arg1, u32 arg2) {
    u32 loc54[6];
    u32 loc3C[6];
    u32 loc24[6];
    u32 loc8[7];
    s32 v0;
    s32 skip;
    u32 v2;
    s32 v4;
    s32 v5;

    loc8[0] = arg1->unk_4;
    loc8[1] = arg1->unk_14;
    loc8[2] = arg1->unk_24;
    loc8[3] = arg1->unk_8;
    loc8[4] = arg1->unk_18;
    loc8[5] = arg1->unk_28;
    loc24[0] = arg2;
    loc24[1] = arg1->unk_44;

    switch ((s32)arg0->unk_4) {
    case 0x11:
    case 0x31:
    case 0x41:
    case 0xf1:
    case 0x1001:
        v0 = 0;
        break;
    case 0x21:
    case 0x101:
        v0 = 1;
        break;
    default:
        fn_12_309C(0, 0, (u32)&lbl_12_rodata_60);
        v0 = 0;
        break;
    }

    if (v0 == 1) {
        loc24[2] = arg1->unk_48 / 2;
    } else {
        loc24[2] = arg1->unk_48;
    }

    if (arg0->unk_8 == 0) {
        loc24[3] = arg1->unk_8 << 2;
    } else {
        loc24[3] = arg0->unk_8;
    }

    skip = 0;
    if (arg1->unk_74 == 1) {
        if (skip != 1) {
            fn_12_3D144(loc8, loc24);
        }
    } else {
        if (skip != 1) {
            fn_12_3D144(loc8, loc24);
        }
    }

    v2 = arg1->unk_8;
    v4 = v2 * arg1->unk_C;
    v5 = v4 / 2;
    loc54[0] = arg1->unk_4 + v5;
    loc54[1] = arg1->unk_14 + v5 / 2;
    loc54[2] = arg1->unk_24 + v5 / 2;
    loc54[3] = v2;
    loc54[4] = arg1->unk_18;
    loc54[5] = arg1->unk_28;
    loc3C[0] = arg2;
    loc3C[1] = arg1->unk_44;
    loc3C[2] = arg1->unk_48 / 2;
    if (arg0->unk_8 == 0) {
        loc3C[3] = v2 << 2;
    } else {
        loc3C[3] = arg0->unk_8;
    }

    if (fn_12_308C() == 1) {
        return fn_12_3DCF0(loc54, loc3C, arg0->unk_38);
    }
    return fn_12_3DF08(loc54, loc3C);
}

