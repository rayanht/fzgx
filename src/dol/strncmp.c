#include "types.h"

s32 strncmp(const char *s1, const char *s2, size_t n) {
    const u8 *p1 = (const u8 *)s1 - 1;
    const u8 *p2 = (const u8 *)s2 - 1;
    u8 c1;
    u8 c2;

    n++;
    while (--n != 0) {
        c1 = *++p1;
        c2 = *++p2;
        if (c1 != c2) {
            return c1 - c2;
        }
        if (c1 == 0) {
            break;
        }
    }
    return 0;
}
