#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __EXIRegs[16] : FZGX_ADDR___EXIRegs;

BOOL fn_8008FC3C(void *buf, s32 len, u32 type) {
    u32 data;
    int i;

    if (type != 0) {
        data = 0;
        for (i = 0; i < len; i++) {
            data |= ((u8 *)buf)[i] << ((3 - i) * 8);
        }
        __EXIRegs[2 * 5 + 4] = data;
    }
    __EXIRegs[2 * 5 + 3] = 1 | (type << 2) | ((len - 1) << 4);
    while (__EXIRegs[2 * 5 + 3] & 1) {
    }
    if (type == 0) {
        data = __EXIRegs[2 * 5 + 4];
        for (i = 0; i < len; i++) {
            *((u8 *)buf)++ = (u8)(data >> ((3 - i) * 8));
        }
    }
    return TRUE;
}
