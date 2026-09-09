#include "types.h"

struct fn_80043050_Arg0 {
    u8 pad_0[2];
    u16 unk_2;
    u8 pad_4[8];
    u8 unk_C;
    u8 unk_D;
    s8 unk_E;
    s8 unk_F;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u16 unk_1C;
    u8 pad_1E[2];
    u32 unk_20;
    u16 unk_24;
    u16 unk_26;
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
    u8 pad_38[4];
    u32 unk_3C;
    u32 unk_40;
    u32 unk_44;
    u8 pad_48[8];
    s32 unk_50;
    s32 unk_54;
    u32 unk_58;
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u8 pad_68[0x20];
    u32 unk_88;
    u32 unk_8C;
    u8 pad_90[8];
    u16 unk_98;
    u16 unk_9A;
};

extern s32 fn_8004313C(void *, void *, s16 *, void *, void *, void *, void *, void *,
                              void *, void *, void *);

struct fn_80043050_Local {
    u8 pad_0[0x18];
    s16 value;
};

s16 fn_80043050(struct fn_80043050_Arg0 *arg0, void *arg1, void *arg2) {
    s16 local;
    s32 result;

    arg0->unk_2 = 1;
    result = fn_8004313C(arg1, arg2, &local, &arg0->unk_C, &arg0->unk_D,
                          &arg0->unk_F, &arg0->unk_E, (u8 *)&arg0->unk_14,
                          &arg0->unk_18, &arg0->unk_10, &arg0->unk_9A);
    if (result < 0) {
        return 0;
    }
    arg0->unk_1C = 0;
    arg0->unk_26 = 0;
    arg0->unk_24 = 0;
    arg0->unk_34 = 0;
    arg0->unk_30 = 0;
    arg0->unk_2C = 0;
    arg0->unk_28 = 0;
    arg0->unk_20 = 0;
    arg0->unk_50 = (s8)arg0->unk_E;
    arg0->unk_54 = (s8)arg0->unk_F;
    arg0->unk_58 = arg0->unk_10;
    arg0->unk_5C = arg0->unk_3C;
    arg0->unk_60 = arg0->unk_40;
    arg0->unk_64 = arg0->unk_44;
    arg0->unk_8C = 0;
    arg0->unk_88 = 0;
    arg0->unk_98 = 1;
    return local;
}
