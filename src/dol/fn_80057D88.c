#include "types.h"

u32 fn_80057D88(u32 arg0, u32 arg1, u32 arg2) {
    u8 *ptr = (u8 *)arg0 + (arg1 << 3);
    ptr += arg2 << 2;
    return *(u32 *)(ptr + 0x28);
}
