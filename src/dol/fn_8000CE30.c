#include "types.h"

extern s32 __OSReadROM(void *dst, s32 length, u32 offset);

void fn_8000CE30(void *dst, s32 length, u32 offset) {
    s32 chunk;

    while (length > 0) {
        if (length <= 0x100) {
            chunk = length;
        } else {
            chunk = 0x100;
        }
        length -= chunk;
        while (!__OSReadROM(dst, chunk, offset)) {
        }
        offset += chunk;
        dst = (u8 *)dst + chunk;
    }
}
