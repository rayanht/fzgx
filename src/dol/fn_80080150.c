
#include "types.h"

int fn_80080150(const char *s, size_t n) {
    if (n == 0)
        return -1;
    if (s[0] == 0)
        return 0;
    if ((s[0] & 0x80) == 0)
        return 1;
    if ((s[0] & 0xe0) == 0xc0) {
        if (n >= 2) {
            if ((s[1] & 0x80) == 0x80)
                return 2;
            return -1;
        }
        return -2;
    } else if ((s[0] & 0xf0) == 0xe0) {
        if (n >= 3) {
            if ((s[1] & 0x80) == 0x80) {
                if ((s[2] & 0x80) == 0x80)
                    return 3;
            }
            return -1;
        } else if ((n == 2 && (s[1] & 0x80) == 0x80) || n == 1) {
            return -2;
        }
        return -1;
    }
    return -1;
}
