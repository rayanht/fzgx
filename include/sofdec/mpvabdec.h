#ifndef SOFDEC_MPVABDEC_H
#define SOFDEC_MPVABDEC_H

#include "types.h"

typedef union MPVABDECCoefficients {
    f32 values[64];
    f64 pairs[32];
} MPVABDECCoefficients;

typedef struct MPVABDECContext {
    u32 bit_buffer;
    u32 next_buffer;
    s32 bit_count;
    const u32* stream;
    const u32* run_level_8;
    const s16* run_level_4;
    const s16* run_level_2;
    const s16* run_level_1;
    const s16* run_level_0a;
    const s16* run_level_0b;
    const s16* run_level_0c;
    const s8* scan;
    const s16* dc_sign_masks;
    const f32* coefficient_scale;
    u8 field_0x38[0x1B0];
    s32 decode_mode;
} MPVABDECContext;

typedef struct MPVABDECBlock {
    s32 run;
    s32 level;
    s32 sign;
    u32 code_length;
    s32 first_scan;
    s32 current_scan;
    u8 field_0x18[4];
    MPVABDECCoefficients* coefficients;
    const u8* quant_matrix;
    s32 quantizer_scale;
    s32* dc_predictor;
    const u8* dc_size_lut;
} MPVABDECBlock;

s32 MPVABDEC_NintraBlock(MPVABDECContext* ctx, MPVABDECBlock* block);
s32 MPVABDEC_IntraBlock(MPVABDECContext* ctx, MPVABDECBlock* block);
s32 MPVABDEC_IntraBlockDc11(MPVABDECContext* ctx, MPVABDECBlock* block);

#endif
