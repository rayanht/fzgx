#include "types.h"

char *strchr(const char *str, int c) {
    const unsigned char *p = (const unsigned char *)str - 1;
    u32 target = (u8)c;
    u32 ch;

    while ((ch = *++p) != 0) {
        if (ch == target) {
            return (char *)p;
        }
    }
    if (target == 0) {
        return (char *)p;
    }
    return 0;
}

