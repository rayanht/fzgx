#include "types.h"

char *fn_800839D8(char *string, const char *delimiters);

extern char *lbl_801A6640;

extern char *lbl_801A6644;

char *fn_800839D8(char *string, const char *delimiters) {
    unsigned char delimiter_map[32] = {0};
    unsigned char *scan;
    unsigned char *token;
    unsigned long value;

    if (string != 0)
        lbl_801A6644 = string;

    scan = (unsigned char *)delimiters - 1;
    while ((s32)(value = *++scan) != 0) {
        delimiter_map[(value >> 3) & 0x1FU] |= 1U << (value & 7);
    }

    scan = (unsigned char *)lbl_801A6644 - 1;
    while ((s32)(value = *++scan) != 0) {
        if ((delimiter_map[(value >> 3) & 0x1FU] & (1U << (value & 7))) == 0)
            break;
    }

    if ((s32)value == 0) {
        lbl_801A6644 = lbl_801A6640;
        return 0;
    }

    token = scan;
    while ((s32)(value = *++scan) != 0) {
        if ((delimiter_map[(value >> 3) & 0x1FU] & (1U << (value & 7))) != 0)
            break;
    }

    if ((s32)value == 0) {
        lbl_801A6644 = lbl_801A6640;
        return (char *)token;
    }
    lbl_801A6644 = (char *)scan + 1;
    *scan = 0;
    return (char *)token;
}
