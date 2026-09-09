#include "types.h"
#include "dol/globals.h"

extern void fn_800370A0(s32, s32, s32, s32, s32);

void fn_80072C24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 *entry;

    entry = (u32 *)(lbl_801A6D38 + (arg0 << 4) + 0xf0);
    if ((s32)entry[0] == arg1 &&
        (s32)entry[1] == arg2 &&
        (s32)entry[2] == arg3 &&
        (s32)entry[3] == arg4) {
        return;
    }

    fn_800370A0(arg0, arg1, arg2, arg3, arg4);
    entry[0] = arg1;
    entry[1] = arg2;
    entry[2] = arg3;
    entry[3] = arg4;
}
