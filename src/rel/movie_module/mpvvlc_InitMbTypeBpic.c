#include "types.h"

extern signed short lbl_12_bss_6330[64];

void mpvvlc_InitMbTypeBpic(void) {
    signed short *output = lbl_12_bss_6330;
    int i;
    long entry_count = 16;
    *output++ = 0x1F00;
    *output++ = 0x1106;
    *output++ = 0x1606;
    *output++ = 0x1A06;
    for (i = 0; i < 2; i++)
        *output++ = 0x1E05;
    for (i = 0; i < 2; i++)
        *output++ = 0x0105;
    for (i = 0; i < 4; i++)
        *output++ = 0x0804;
    for (i = 0; i < 4; i++)
        *output++ = 0x0A04;
    for (i = 0; i < 8; i++)
        *output++ = 0x0403;
    for (i = 0; i < 8; i++)
        *output++ = 0x0603;
    for (i = 0; i < entry_count; i++)
        *output++ = 0x0C02;
    for (i = 0; i < entry_count; i++)
        *output++ = 0x0E02;
}
