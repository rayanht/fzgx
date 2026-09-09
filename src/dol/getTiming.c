#include "types.h"

extern u8 lbl_801241C8[500];

const char *getTiming(u32 timing) {
    const char *base = (const char *)lbl_801241C8;

    switch (timing) {
    case 0:
        return base + 0x44;
    case 1:
        return base + 0x6a;
    case 2:
        return base + 0x90;
    case 3:
        return base + 0xb6;
    case 4:
        return base + 0x44;
    case 5:
        return base + 0x6a;
    case 6:
        return base + 0xdc;
    case 7:
        return base + 0x102;
    case 8:
        return base + 0x128;
    case 9:
        return base + 0x14e;
    case 10:
        return base + 0x90;
    case 11:
        return base + 0xb6;
    case 12:
        return base + 0x174;
    case 13:
        return base + 0x19a;
    case 26:
    default:
        return 0;
    }
}
