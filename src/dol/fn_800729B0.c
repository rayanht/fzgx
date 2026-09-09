#include "types.h"
#include "dol/globals.h"

extern void fn_80037480(s32, s32, s32, s32, s32);

void fn_800729B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;

    p = (u8 *)lbl_801A6D38 + arg0 * 16 + 0x2c;
    if (*(s32 *)(p + 0) == arg1 &&
        *(s32 *)(p + 4) == arg2 &&
        *(s32 *)(p + 8) == arg3 &&
        *(s32 *)(p + 0xc) == arg4) {
        return;
    }

    fn_80037480(arg0, arg1, arg2, arg3, arg4);
    *(s32 *)(p + 0) = arg1;
    *(s32 *)(p + 4) = arg2;
    *(s32 *)(p + 8) = arg3;
    *(s32 *)(p + 0xc) = arg4;
}
