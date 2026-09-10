#include "types.h"

__declspec(section ".init") void *fn_800035C0(void *dest, const void *src, u32 n) {
    const u8 *s = (const u8 *)src;
    u8 *d = (u8 *)dest;

    s--;
    d--;
    n++;
    while (--n != 0) {
        *++d = *++s;
    }
}
