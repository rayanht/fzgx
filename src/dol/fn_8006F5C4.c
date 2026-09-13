#include "types.h"

extern void lbl_8006DAEC(void *arg0, void *arg1, void *arg2);
extern f32 lbl_801A73F0;
extern f32 lbl_801A73F4;
extern void lbl_8006E1C0(void *arg0, void *arg1);
extern s16 lbl_8006D24C(f32 arg0, f32 arg1);
extern f32 lbl_8006D0B4(f32 arg0);
extern void lbl_8006D91C(s16 arg0);
extern void mathutil_mtxA_rotate_y(s16 arg0);
extern void fn_8006E2B0(void *arg0, void *arg1);
extern void lbl_8006DB30(void);

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

#pragma opt_dead_assignments off
void fn_8006F5C4(s16 *arg0, s16 *arg1, s16 *arg2) {
    Vec3 vec0;
    Vec3 vec1;

    lbl_8006DAEC(arg0, arg1, arg2);

    vec0.y = lbl_801A73F0;
    vec0.x = lbl_801A73F4;
    vec0.z = lbl_801A73F0;
    vec1.x = lbl_801A73F0;
    vec1.y = lbl_801A73F4;
    vec1.z = lbl_801A73F0;

    lbl_8006E1C0(&vec0, &vec0);
    lbl_8006E1C0(&vec1, &vec1);

    *arg0 = lbl_8006D24C(vec0.y, vec0.x);
    {
        f32 y;
        f32 x;
        f32 magnitude;

        y = vec0.y;
        x = vec0.x;
        magnitude = y * y;
        magnitude += x * x;
        *arg1 = -lbl_8006D24C(vec0.z, lbl_8006D0B4(magnitude));
    }

    lbl_8006D91C(*arg0);
    mathutil_mtxA_rotate_y(*arg1);

    fn_8006E2B0(&vec1, &vec1);
    *arg2 = lbl_8006D24C(vec1.z, vec1.y);

    lbl_8006DB30();
}
#pragma opt_dead_assignments reset

