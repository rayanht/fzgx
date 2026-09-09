#include "types.h"

extern const f32 lbl_801A73B0;
extern u32 lbl_801A6CA8;

void fn_8006CE1C(f32 arg0) {
    f32 value = lbl_801A73B0;
    ((u8 *)&lbl_801A6CA8)[3] = (u8)(s32)(value * arg0);
}
