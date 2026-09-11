#include "types.h"

extern f64 lbl_12_rodata_60[12];

struct fn_12_F70_Arg0 {
    u8 pad_0[0x4];
    s32 unk_4;
    s32 unk_8;
    s32 unk_C;
    u8 pad_10[0x28];
    u32 unk_38;
};

struct fn_12_F70_Arg1 {
    u8 pad_0[0x4];
    s32 unk_4;
    s32 unk_8;
    s32 unk_C;
    u8 pad_10[0x4];
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x18];
    s32 unk_44;
    s32 unk_48;
};

typedef struct {
    u32 a[6];
} fn_12_F70_Loc24;

typedef struct {
    u32 a[7];
} fn_12_F70_Loc8;

extern void fn_12_309C(void *, void *, void *);
extern void fn_12_3C4A8(void *, void *, u32);
extern void fn_12_3C8CC(void *, void *);
extern int fn_12_740(struct fn_12_F70_Arg0 *);
extern int fn_12_49D8(struct fn_12_F70_Arg0 *);
extern int fn_12_49AC(struct fn_12_F70_Arg0 *);
extern int fn_12_738(struct fn_12_F70_Arg0 *);

void fn_12_F70(struct fn_12_F70_Arg0 *arg0, struct fn_12_F70_Arg1 *arg1, u32 arg2, s32 arg3, s32 arg4) {
    fn_12_F70_Loc24 loc24;
    fn_12_F70_Loc8 loc8;
    s32 t;
    s32 flag;
    s32 var;

    flag = 0;
    var = 0;
    loc24.a[0] = arg1->unk_4;
    loc24.a[1] = arg1->unk_14;
    loc24.a[2] = arg1->unk_24;
    loc24.a[3] = arg1->unk_8;
    loc24.a[4] = arg1->unk_18;
    loc24.a[5] = arg1->unk_28;
    loc8.a[0] = arg2;
    loc8.a[1] = arg1->unk_44;

    switch (arg0->unk_4) {
    case 0x11:
    case 0x31:
    case 0x41:
    case 0xf1:
    case 0x1001:
        t = 0;
        break;
    case 0x21:
    case 0x101:
        t = 1;
        break;
    default:
        fn_12_309C(0, 0, lbl_12_rodata_60);
        t = 0;
        break;
    }

    if (t == 1) {
        loc8.a[2] = arg1->unk_48 / 2;
    } else {
        loc8.a[2] = arg1->unk_48;
    }

    if (arg0->unk_8 == 0) {
        loc8.a[3] = arg1->unk_8;
    } else {
        loc8.a[3] = arg0->unk_8;
    }

    if (arg0->unk_C == 0) {
        loc8.a[6] = arg1->unk_C;
    } else {
        loc8.a[6] = arg0->unk_C;
    }

    switch (fn_12_740(arg0)) {
    case -1:
        var = 0;
        if (fn_12_49D8(arg0) == 1) {
            if (fn_12_49AC(arg0) == 1) {
                if (fn_12_738(arg0) == 0) {
                    var = 1;
                }
            }
        }
        break;
    case 0:
        var = 0;
        break;
    case 1:
        var = 1;
        break;
    default:
        var = 0;
        break;
    }

    if (var == 1) {
        loc8.a[4] = 2;
    } else {
        loc8.a[4] = 1;
    }

    if (arg3 == 1) {
        u32 x = arg0->unk_38;
        if (flag != 1) {
            fn_12_3C4A8(&loc24, &loc8, x);
        }
    } else {
        if (flag != 1) {
            fn_12_3C8CC(&loc24, &loc8);
        }
    }
}
