#include "types.h"
extern void __fill_mem(void *, int, u32);
__declspec(section ".init") void *memset(void *dest, int value, u32 size) {
    __fill_mem(dest, value, size);
    return dest;
}
