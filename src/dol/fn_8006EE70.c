#include "types.h"

extern f32 lbl_8006D0B4(f32 value);
extern s16 lbl_8006D24C(f32 a, f32 b);

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

void fn_8006EE70(const Vec3 *input, s16 *output) {
    s16 *dst;
    f32 x;
    f32 y;
    f32 z;
    f32 sum;

    dst = output;
    x = -input->x;
    y = input->y;
    z = -input->z;
    sum = x * x;
    sum += z * z;
    dst[0] = lbl_8006D24C(y, lbl_8006D0B4(sum));
    dst[1] = lbl_8006D24C(x, z);
    dst[2] = 0;
}
