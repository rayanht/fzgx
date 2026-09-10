#include "types.h"

extern const f32 lbl_801A73D4;
extern const f32 lbl_801A73D8;
extern f32 lbl_8006D0E8(f32);

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

void fn_8006E8DC(Vec4 *arg0) {
    f32 scale = lbl_801A73D4;
    f32 length_squared = (arg0->x * arg0->x) + (arg0->y * arg0->y) + (arg0->z * arg0->z) + (arg0->w * arg0->w);

    if (length_squared > scale) {
        scale = lbl_8006D0E8(length_squared);
    } else {
        scale = lbl_801A73D8;
    }

    arg0->x = arg0->x * scale;
    arg0->y = arg0->y * scale;
    arg0->z = arg0->z * scale;
    arg0->w = arg0->w * scale;
}
