#include "types.h"

extern unsigned char lbl_12_bss_54F0[1024];

static inline void mpvvlc_EmitDc(signed char **output, long count, signed char value) {
    int i;
    for (i = 0; i < count; i++) {
        *(*output)++ = value;
    }
}

void mpvvlc2_InitDcSizC(void) {
    signed char *output = (signed char *)lbl_12_bss_54F0;
    mpvvlc_EmitDc(&output, 256, 0x02);
    mpvvlc_EmitDc(&output, 256, 0x12);
    mpvvlc_EmitDc(&output, 256, 0x22);
    mpvvlc_EmitDc(&output, 128, 0x33);
    mpvvlc_EmitDc(&output, 64, 0x44);
    mpvvlc_EmitDc(&output, 32, 0x55);
    mpvvlc_EmitDc(&output, 16, 0x66);
    output[0] = 0x77;
    output[1] = 0x77;
    output[2] = 0x77;
    output[3] = 0x77;
    output[4] = 0x77;
    output[5] = 0x77;
    output[6] = 0x77;
    output[7] = 0x77;
    output[8] = 0x88;
    output[9] = 0x88;
    output[10] = 0x88;
    output[11] = 0x88;
    output[12] = 0x99;
    output[13] = 0x99;
    output[14] = 0xAA;
    output[15] = 0xBA;
}
