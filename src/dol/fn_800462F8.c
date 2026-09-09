#include "types.h"

struct fn_800462F8_Arg0 {
    u8 pad_0[0x2];
    u16 unk_2;
    u8 pad_4[0x8];
    u8 unk_c;
    s8 unk_d;
    s8 unk_e;
    s8 unk_f;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u16 unk_1c;
    u8 pad_1e[0x2];
    u32 unk_20;
    u16 unk_24;
    u16 unk_26;
    u32 unk_28;
    u32 unk_2c;
    u32 unk_30;
    u32 unk_34;
    u8 pad_38[0x4];
    u32 unk_3c;
    u32 unk_40;
    u32 unk_44;
    u8 pad_48[0x8];
    s32 unk_50;
    s32 unk_54;
    u32 unk_58;
    u32 unk_5c;
    u32 unk_60;
    u32 unk_64;
    u8 pad_68[0x20];
    u32 unk_88;
    u32 unk_8c;
    u8 pad_90[0x8];
    u16 unk_98;
    u16 unk_9a;
};

extern s32 fn_800463E4(u32, u32, s16 *, u8 *, u8 *, u8 *, u8 *, u8 *, u8 *, u8 *, u32 *);

s32 fn_800462F8(struct fn_800462F8_Arg0 *arg0, u32 arg1, u32 arg2) {
    s16 local;
    s32 result;

    arg0->unk_2 = 1;
    result = fn_800463E4(arg1, arg2, &local,
                         (u8 *)&arg0->unk_c, (u8 *)&arg0->unk_d, (u8 *)&arg0->unk_f,
                         (u8 *)&arg0->unk_e, (u8 *)&arg0->unk_14, (u8 *)&arg0->unk_18,
                         (u8 *)&arg0->unk_10, (u32 *)&arg0->unk_9a);
    if (result < 0) {
        return 0;
    }
    arg0->unk_1c = 0;
    arg0->unk_26 = 0;
    arg0->unk_24 = 0;
    arg0->unk_34 = 0;
    arg0->unk_30 = 0;
    arg0->unk_2c = 0;
    arg0->unk_28 = 0;
    arg0->unk_20 = 0;
    arg0->unk_50 = arg0->unk_e;
    arg0->unk_54 = arg0->unk_f;
    arg0->unk_58 = arg0->unk_10;
    arg0->unk_5c = arg0->unk_3c;
    arg0->unk_60 = arg0->unk_40;
    arg0->unk_64 = arg0->unk_44;
    arg0->unk_8c = 0;
    arg0->unk_88 = 0;
    arg0->unk_98 = 2;
    return local;
}
