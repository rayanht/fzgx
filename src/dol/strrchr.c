#include "types.h"

char *strrchr(const char *str, int c) {
    const unsigned char *p = (const unsigned char *)str - 1;
    u32 target = (u8)c;
    char *last = 0;
    u32 ch;

    while ((ch = *++p) != 0) {
        if (ch == target) {
            last = (char *)p;
        }
    }

    if (last != 0) {
        return last;
    }
    if (target != 0) {
        return 0;
    }
    return (char *)p;
}
