#include "types.h"
struct fn_8006EF10_Arg0 {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
};
extern f32 lbl_8006D0B4(f32);
extern s32 lbl_8006D24C(f32, f32);


void fn_8006EF10(void *arg0, s16 *arg1, s16 *arg2) {
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_sum;

    temp_f31 = -(*(f32 *)((u8 *)(arg0) + 0));
    temp_f30 = *(f32 *)((u8 *)(arg0) + 4);
    temp_f29 = -(*(f32 *)((u8 *)(arg0) + 8));
    temp_sum = temp_f31 * temp_f31;
    temp_sum += temp_f29 * temp_f29;
    (*(s16 *)((u8 *)(arg1) + 0)) = lbl_8006D24C((f32)(temp_f30), (f32)(lbl_8006D0B4(temp_sum)));
    (*(s16 *)((u8 *)(arg2) + 0)) = lbl_8006D24C((f32)(temp_f31), (f32)(temp_f29));
}
