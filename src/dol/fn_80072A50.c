#include "types.h"
#include "dol/globals.h"

extern void fn_80037480(s32 index);

void fn_80072A50(u32 index, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    u32 *entry = (u32 *)(lbl_801A6D38 + (index << 4) + 0x2c);

    fn_80037480(index);
    entry[0] = arg1;
    entry[1] = arg2;
    entry[2] = arg3;
    entry[3] = arg4;
}
