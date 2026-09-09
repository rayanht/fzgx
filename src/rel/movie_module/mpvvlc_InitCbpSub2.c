#include "types.h"

static inline void mpvvlc_EmitCbp(signed short **output, long count, signed short value) {
    int i;
    for (i = 0; i < count; i++) {
        *(*output)++ = value;
    }
}

signed short *mpvvlc_InitCbpSub2(signed short *output) {
    int i;
    for (i = 0; i < 4; i++)
        *output++ = 0xA207;
    for (i = 0; i < 4; i++)
        *output++ = 0x9207;
    for (i = 0; i < 4; i++)
        *output++ = 0x8A07;
    for (i = 0; i < 4; i++)
        *output++ = 0x8607;
    for (i = 0; i < 4; i++)
        *output++ = 0x6107;
    for (i = 0; i < 4; i++)
        *output++ = 0x5107;
    for (i = 0; i < 4; i++)
        *output++ = 0x4907;
    for (i = 0; i < 4; i++)
        *output++ = 0x4507;
    for (i = 0; i < 8; i++)
        *output++ = 0xFF06;
    for (i = 0; i < 8; i++)
        *output++ = 0xC306;
    for (i = 0; i < 8; i++)
        *output++ = 0x2406;
    for (i = 0; i < 8; i++)
        *output++ = 0x1806;
    mpvvlc_EmitCbp(&output, 16, 0xBE05);
    mpvvlc_EmitCbp(&output, 16, 0x8205);
    mpvvlc_EmitCbp(&output, 16, 0x7D05);
    mpvvlc_EmitCbp(&output, 16, 0x4105);
    mpvvlc_EmitCbp(&output, 16, 0x3805);
    mpvvlc_EmitCbp(&output, 16, 0x3405);
    mpvvlc_EmitCbp(&output, 16, 0x2C05);
    mpvvlc_EmitCbp(&output, 16, 0x1C05);
    mpvvlc_EmitCbp(&output, 16, 0x2805);
    mpvvlc_EmitCbp(&output, 16, 0x1405);
    mpvvlc_EmitCbp(&output, 16, 0x3005);
    mpvvlc_EmitCbp(&output, 16, 0x0C05);
    mpvvlc_EmitCbp(&output, 32, 0x2004);
    mpvvlc_EmitCbp(&output, 32, 0x1004);
    mpvvlc_EmitCbp(&output, 32, 0x0804);
    mpvvlc_EmitCbp(&output, 32, 0x0404);
    mpvvlc_EmitCbp(&output, 64, 0x3C03);
    return output;
}
