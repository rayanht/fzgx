#include "types.h"

__declspec(section ".init") void *memcpy(void *dest, const void *src, u32 n) {
    const u8 *s;
    u8 *d;

    d = (u8 *)dest;
    s = (const u8 *)src;
    if (s >= d) {
        s--;
        d--;
        n++;
        while (--n != 0) {
            *++d = *++s;
        }
    } else {
        s += n;
        d += n;
        n++;
        while (--n != 0) {
            *--d = *--s;
        }
    }
    return dest;
}
