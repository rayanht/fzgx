#include "types.h"

extern int fn_12_A2C4(const unsigned char *);

char *fn_12_A1C4(char *text, s32 length, u32 mask) {
    char *limit = text - length;
    char c;
    s32 state = 0;

    while (limit < text) {
        c = *--text;

        switch (state) {
        case 0:
            state = 1;
            break;
        case 1:
            if (c == 1) {
                state = 2;
            }
            break;
        case 2:
            if (c == 0) {
                state = 3;
            } else if (c != 1) {
                state = 1;
            }
            break;
        case 3:
            if (c == 0) {
                if (mask & fn_12_A2C4((const unsigned char *)text)) {
                    return text;
                }
                state = 0;
            } else if (c != 1) {
                state = 1;
            } else {
                state = 2;
            }
            break;
        }
    }

    return 0;
}
