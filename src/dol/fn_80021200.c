#include "types.h"

extern u32 lbl_801A6AF8;
extern u8 lbl_8015FF00[1536];
extern u32 lbl_801A6AFC;

u8 *fn_80021200(void) {
    u32 index = lbl_801A6AF8;
    u8 *base = lbl_8015FF00;
    u8 *old = base;

    lbl_801A6AF8 = index + 1;
    old += index * 0x300;
    lbl_801A6AF8 &= 1;
    lbl_801A6AFC = (u32)(base + lbl_801A6AF8 * 0x300);
    return old;
}
