#include "types.h"

extern const f32 lbl_801A7480;
extern const f32 lbl_801A7484;
extern u32 lbl_801A6D7C;
extern u32 lbl_801A6D84;

void fn_80074BC4(f32 a, f32 b, f32 c, f32 d) {
    u8 v3;
    if (!(lbl_801A7480 == a &&
          lbl_801A7480 == b &&
          lbl_801A7480 == c &&
          lbl_801A7480 == d)) {
        f32 scale = lbl_801A7484;
        u8 v0 = (u8)(scale * a);
        u8 v1 = (u8)(scale * b);
        u8 v2 = (u8)(scale * c);

        lbl_801A6D84 = 1;
        *((u8 *)&lbl_801A6D7C) = v0;
        *((u8 *)&lbl_801A6D7C + 1) = v1;
        *((u8 *)&lbl_801A6D7C + 2) = v2;
        *((u8 *)&lbl_801A6D7C + 3) = ((u8)(scale * d));
    } else {
        lbl_801A6D84 = 0;
        *((u8 *)&lbl_801A6D7C) = 0;
        *((u8 *)&lbl_801A6D7C + 1) = 0;
        *((u8 *)&lbl_801A6D7C + 2) = 0;
        *((u8 *)&lbl_801A6D7C + 3) = 0;
    }
}
