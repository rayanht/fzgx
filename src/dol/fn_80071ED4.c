#include "types.h"

struct fn_80071ED4_lbl_8019E250 {
    u8 pad_0[0x4];
    f32 unk_4;
    f32 unk_8;
    u32 unk_C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u8 pad_28[0x4];
    u32 unk_2C;
};

extern const f32 lbl_801A745C;
extern struct fn_80071ED4_lbl_8019E250 lbl_8019E250[];
extern u32 fn_800377F8(u32, void *, f32, f32);
extern u32 fn_800720B0(u32);

void fn_80071ED4(f32 arg0, f32 arg1, s32 arg2) {
    f32 v0;
    f32 v1;
    u32 c;
    u32 b;
    f32 t;
    u32 x;
    u32 w;
    struct { u32 a[2]; } loc_8;

    v0 = lbl_8019E250[0].unk_4;
    v1 = lbl_8019E250[0].unk_8;
    if (arg1 == lbl_8019E250[0].unk_14 && arg0 == lbl_8019E250[0].unk_10 && v1 == lbl_8019E250[0].unk_18 && v0 == lbl_8019E250[0].unk_1C && arg2 == (s32)lbl_8019E250[0].unk_C) {
        return;
    }
    if (arg2 == 0) {
        fn_800720B0(0);
        return;
    }
    c = lbl_8019E250[0].unk_2C | 1;
    lbl_8019E250[0].unk_C = arg2;
    lbl_8019E250[0].unk_10 = arg0;
    lbl_8019E250[0].unk_14 = arg1;
    lbl_8019E250[0].unk_18 = v1;
    lbl_8019E250[0].unk_1C = v0;
    lbl_8019E250[0].unk_2C = lbl_8019E250[0].unk_2C | 1;
    b = lbl_8019E250[0].unk_20;
    loc_8.a[0] = b;
    fn_800377F8(arg2, &loc_8, arg0, arg1);
    if (arg0 == arg1) {
        t = lbl_801A745C;
    } else {
        t = arg0 / (arg1 - arg0);
    }
    *(f32 *)&loc_8.a[1] = t;
    x = loc_8.a[1];
    w = (lbl_8019E250[0].unk_24 & 0xFFFFF800) | ((x >> 12) & 0x7FF);
    lbl_8019E250[0].unk_24 = w;
    w = (w & 0xFFF807FF) | (((x >> 23) & 0xFF) << 11);
    lbl_8019E250[0].unk_24 = w;
    w = (w & 0xFFF7FFFF) | ((x >> 31) << 19);
    lbl_8019E250[0].unk_24 = w;
    w = w & 0xFFEFFFFF;
    lbl_8019E250[0].unk_24 = w;
    lbl_8019E250[0].unk_24 = (lbl_8019E250[0].unk_24 & 0xFFFFFF) | 0xF1000000;
}
