#include "types.h"

struct fn_12_8B0C_Arg0 {
    u8 pad_0[0x120];
    u32 unk_120;
    s32 values[12];
    u8 pad_154[0x50];
    s32 unk_1a4;
    u8 pad_1a8[0xa8];
    s16 unk_250;
    s16 unk_252;
};

void fn_12_8B0C(struct fn_12_8B0C_Arg0 *arg0) {
    s32 value = 4;
    s32 *values = &arg0->values[0];
    s16 sample;

    if (arg0->unk_1a4 == 0) {
        value = -1;
    }
    arg0->unk_120 = value;
    sample = arg0->unk_250;
    values[1] = sample;
    values[3] = sample;
    sample = arg0->unk_252;
    values[5] = sample;
    values[7] = sample;
    values[9] = sample;
    values[11] = sample;
}
