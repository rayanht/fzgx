#include "types.h"

extern u8 lbl_800929F8[32];
extern u8 lbl_80092A18[160];
extern const f64 lbl_801A7248;
extern const f32 lbl_801A7250;
extern const f64 lbl_801A7238;
extern const f64 lbl_801A7218;
extern const f32 lbl_801A7254;
extern f32 fn_80088578(f32 x);

void fn_8005DB68(s16 arg0, f32 arg1, s16 arg2, s16 *arg3, s16 *arg4) {
    u32 idx = ((s32)arg0 / 4 - 1) & 0xFF;
    f32 a;
    f32 b;

    a = arg1 + (f32)(20.0 * fn_80088578((f32)lbl_800929F8[idx] / 255.0f));
    b = arg1 + (f32)(20.0 * fn_80088578((f32)lbl_80092A18[idx] / 255.0f));

    *arg3 = (s16)(s32)((f32)arg2 + 10.0f * a);
    *arg4 = (s16)(s32)((f32)arg2 + 10.0f * b);

    if (*arg3 < -960) {
        *arg3 = -960;
    }
    if (*arg4 < -960) {
        *arg4 = -960;
    }
}
