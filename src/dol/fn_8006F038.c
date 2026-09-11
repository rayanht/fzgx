#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern f32 lbl_8006D0B4(f32 value);
extern s32 lbl_8006D24C(f32 value1, f32 value2);
extern void lbl_8006D91C(s16 angle);
extern void mathutil_mtxA_rotate_x(s16 angle);
extern void mathutil_mtxA_rotate_y(s16 angle);
extern void lbl_8006E0C8(Vec3 *value);

void fn_8006F038(Vec3 *arg0, Vec3 *arg1, s16 arg2) {
    f32 dz;
    f32 dy;
    f32 dx;
    f32 distance;
    s32 angle_x;
    s32 angle_y;

    dx = arg0->x - arg1->x;
    dy = arg1->y - arg0->y;
    dz = arg0->z - arg1->z;
    distance = dx * dx;
    distance += dz * dz;
    distance = lbl_8006D0B4(distance);
    angle_x = lbl_8006D24C(dy, distance);
    angle_y = lbl_8006D24C(dx, dz);
    lbl_8006D91C(-arg2);
    mathutil_mtxA_rotate_x(-angle_x);
    mathutil_mtxA_rotate_y(-angle_y);
    lbl_8006E0C8(arg0);
}
