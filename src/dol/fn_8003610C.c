#include "types.h"

typedef struct Fn8003610CData {
    u32 flags;
    u32 packed;
} Fn8003610CData;

extern u8 lbl_801A6578[8];
extern const f64 lbl_801A70C0;
extern const f32 lbl_801A70E0;
extern const f64 lbl_801A70E8;
extern const f32 lbl_801A70E4;

void fn_8003610C(const Fn8003610CData *data, u32 *out_table, u32 *out_bit,
                 f32 *out_low, f32 *out_high, f32 *out_signed,
                 u8 *out_flag, u8 *out_inverse, u32 *out_bits) {
    int sign;
    *out_table = lbl_801A6578[(data->flags >> 5) & 7u];
    *out_bit = (data->flags >> 4) & 1u;
    *out_low = (f32)(data->packed & 0xffu) * lbl_801A70E0;
    *out_high = (f32)((data->packed >> 8) & 0xffu) * lbl_801A70E0;
    sign = (data->flags >> 9) & 0xff;
    *out_signed = (f32)(s8)(s16)sign * lbl_801A70E4;
    *out_flag = (u8)((data->flags >> 21) & 1u);
    *out_inverse = (u8)!((data->flags >> 8) & 1u);
    *out_bits = (data->flags >> 19) & 3u;
}
