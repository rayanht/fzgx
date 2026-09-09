#include "types.h"

u8 *fn_80083970(u8 *str, const u8 *needle) {
    u8 *p = str - 1;
    u8 ch;
    u32 c;

    if (needle == 0) {
        return str;
    }
    c = *needle;
    if (c == 0) {
        return str;
    }

    while ((ch = *++p) != 0) {
        if (ch == c) {
            u32 c1;
            u32 c2;
            u8 *s = p - 1;
            const u8 *n = needle - 1;

            do {
                c1 = *++s;
                c2 = *++n;
                if (c1 != c2) {
                    break;
                }
            } while (c1 != 0);

            if (c2 == 0) {
                return p;
            }
        }
    }

    return 0;
}
