#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern f32 lbl_8006D0B4(f32);
extern s32 lbl_8006D24C(f32, f32);

void fn_8006ED0C(Vec3 *arg0, Vec3 *arg1, s16 *arg2) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sum;

    dx = arg0->x - arg1->x;
    dz = arg0->z - arg1->z;
    dy = arg1->y - arg0->y;
    sum = dx * dx;
    sum += dz * dz;
    arg2[0] = lbl_8006D24C(dy, lbl_8006D0B4(sum));
    arg2[1] = lbl_8006D24C(dx, dz);
    arg2[2] = 0;
}
