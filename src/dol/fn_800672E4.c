#include "types.h"

extern u32 lbl_801A6C80;

s32 fn_800672E4(u32 arg0, s32 arg1) {
    u8 *base;
    u32 offset;
    if (arg0 >= 0x10) {
        return -0x80;
    }
    switch (arg1) {
    case (s32)0xA0040000:
        base = (u8 *)lbl_801A6C80;
        offset = arg0 << 4;
        return base[offset + 0x492];
    case (s32)0xA0100000:
        base = (u8 *)lbl_801A6C80;
        offset = arg0 << 4;
        return base[offset + 0x493];
    default:
        return -0x80;
    }
}
