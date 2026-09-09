#include "types.h"

struct fn_800453A4_Arg0 {
    u8 pad_0[0xD];
    u8 unk_D;
    u8 unk_E;
    u8 unk_F;
    u8 pad_10[0x38];
    u32 unk_48;
    u32 unk_4C;
    u8 pad_50[0x24];
    u32 unk_74;
    u8 pad_78[0x18];
    u32 unk_90;
    u32 unk_94;
    s16 unk_98;
};

u32 fn_800453A4(struct fn_800453A4_Arg0 *arg0, u32 arg1, u32 arg2) {
    u32 v0;
    u32 unk_1;

    v0 = arg1;
    if (arg0->unk_98 == 0) {
        arg0->unk_48 = v0;
        v0 = arg0->unk_F;
        v0 = (s8)v0;
        v0 = ((s32)arg2 / (s32)v0);
        arg0->unk_4C = v0;
        arg0->unk_74 = 0;
        arg0->unk_90 = 0;
        arg0->unk_94 = 0;
        return (u32)arg0;
    }
    arg0->unk_48 = v0;
    unk_1 = (s8)arg0->unk_D / 8;
    arg0->unk_4C = ((s32)arg2 / (s32)(unk_1 * (s8)arg0->unk_E));
    arg0->unk_74 = 0;
    arg0->unk_90 = 0;
    arg0->unk_94 = 0;
}
