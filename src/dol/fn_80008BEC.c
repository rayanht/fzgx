#include "types.h"
extern void fn_800793D4(void *, int, u32);
extern void *memset(void *, int, u32);
void fn_80008BEC(void *dest, int value, u32 size) {
    if (((u32)dest & 0x1F) == 0) {
        fn_800793D4(dest, value, size);
    } else {
        memset(dest, (u8)value, size);
    }
}
