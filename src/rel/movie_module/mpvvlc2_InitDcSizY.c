#include "types.h"

extern unsigned char lbl_12_bss_58F0[1024];

static inline void mpvvlc_EmitDc(signed char **output, long count, signed char value) {
    int i;
    for (i = 0; i < count; i++) {
        *(*output)++ = value;
    }
}

void mpvvlc2_InitDcSizY(void) {
    signed char *output = (signed char *)lbl_12_bss_58F0;
    mpvvlc_EmitDc(&output, 256, 0x12);
    mpvvlc_EmitDc(&output, 256, 0x22);
    mpvvlc_EmitDc(&output, 128, 0x03);
    mpvvlc_EmitDc(&output, 128, 0x33);
    mpvvlc_EmitDc(&output, 128, 0x43);
    mpvvlc_EmitDc(&output, 64, 0x54);
    mpvvlc_EmitDc(&output, 32, 0x65);
    mpvvlc_EmitDc(&output, 16, 0x76);
    output[0] = 0x87;
    output[1] = 0x87;
    output[2] = 0x87;
    output[3] = 0x87;
    output[4] = 0x87;
    output[5] = 0x87;
    output[6] = 0x87;
    output[7] = 0x87;
    output[8] = 0x98;
    output[9] = 0x98;
    output[10] = 0x98;
    output[11] = 0x98;
    output[12] = 0xA9;
    output[13] = 0xA9;
    output[14] = 0xB9;
    output[15] = 0xB9;
}
