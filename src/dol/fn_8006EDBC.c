#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern f32 lbl_8006D0B4(f32);
extern s32 lbl_8006D24C(f32, f32);

void fn_8006EDBC(Vec3 *arg0, Vec3 *arg1, s16 *arg2, s16 *arg3) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    dx = arg0->x - arg1->x;
    dy = arg1->y - arg0->y;
    dz = arg0->z - arg1->z;
    dist = dx * dx;
    dist += dz * dz;
    *arg2 = lbl_8006D24C(dy, lbl_8006D0B4(dist));
    *arg3 = lbl_8006D24C(dx, dz);
}
