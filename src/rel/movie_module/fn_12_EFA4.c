
#include "types.h"

void fn_12_EFA4(void);

extern unsigned char lbl_12_bss_5D70[128];

static inline void mpvvlc_fill_u8(signed char **output, long count, signed char value) {
    int i;
    for (i = 0; i < count; i++) {
        *(*output)++ = value;
    }
}

void fn_12_EFA4(void) {
    signed char *output = (signed char *)lbl_12_bss_5D70;
    mpvvlc_fill_u8(&output, 32, 0x12);
    mpvvlc_fill_u8(&output, 32, 0x22);
    mpvvlc_fill_u8(&output, 16, 0x03);
    mpvvlc_fill_u8(&output, 16, 0x33);
    mpvvlc_fill_u8(&output, 16, 0x43);
    mpvvlc_fill_u8(&output, 8, 0x54);
    mpvvlc_fill_u8(&output, 4, 0x65);
    mpvvlc_fill_u8(&output, 2, 0x76);
    *output++ = 0x87;
    *output = 0x87;
}
