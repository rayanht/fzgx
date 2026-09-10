
#include "types.h"

void fn_12_ED30(void);

extern unsigned char lbl_12_bss_5CF0[128];

static inline void mpvvlc_fill_u8(signed char **output, long count, signed char value) {
    int i;
    for (i = 0; i < count; i++) {
        *(*output)++ = value;
    }
}

void fn_12_ED30(void) {
    signed char *output = (signed char *)lbl_12_bss_5CF0;
    mpvvlc_fill_u8(&output, 32, 0x02);
    mpvvlc_fill_u8(&output, 32, 0x12);
    mpvvlc_fill_u8(&output, 32, 0x22);
    mpvvlc_fill_u8(&output, 16, 0x33);
    mpvvlc_fill_u8(&output, 8, 0x44);
    mpvvlc_fill_u8(&output, 4, 0x55);
    mpvvlc_fill_u8(&output, 2, 0x66);
    *output++ = 0x77;
    *output = 0x88;
}
