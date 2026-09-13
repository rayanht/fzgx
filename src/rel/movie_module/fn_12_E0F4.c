
#include "types.h"

void fn_12_E0F4(void);

extern unsigned int lbl_12_bss_52F0[128];

static inline void mpvvlc_fill_u32(unsigned int **output, long count, unsigned int value) {
    int i;
    for (i = 0; i < count; i++) {
        *(*output)++ = value;
    }
}

#pragma opt_propagation off
void fn_12_E0F4(void) {
    unsigned int *output = lbl_12_bss_52F0;
    int i = 0;
    mpvvlc_fill_u32(&output, 4, 0x00000000);
    mpvvlc_fill_u32(&output, 4, 0x00064040);
    mpvvlc_fill_u32(&output, 2, 0x00080202);
    mpvvlc_fill_u32(&output, 2, 0x00080109);
    mpvvlc_fill_u32(&output, 2, 0x00080400);
    mpvvlc_fill_u32(&output, 2, 0x00080108);
    mpvvlc_fill_u32(&output, 4, 0x00070107);
    mpvvlc_fill_u32(&output, 4, 0x00070106);
    mpvvlc_fill_u32(&output, 4, 0x00070201);
    mpvvlc_fill_u32(&output, 4, 0x00070105);
    mpvvlc_fill_u32(&output, 1, 0x0009010D);
    mpvvlc_fill_u32(&output, 1, 0x00090600);
    mpvvlc_fill_u32(&output, 1, 0x0009010C);
    mpvvlc_fill_u32(&output, 1, 0x0009010B);
    mpvvlc_fill_u32(&output, 1, 0x00090203);
    mpvvlc_fill_u32(&output, 1, 0x00090301);
    mpvvlc_fill_u32(&output, 1, 0x00090500);
    mpvvlc_fill_u32(&output, 1, 0x0009010A);
    mpvvlc_fill_u32(&output, 8, 0x00060300);
    mpvvlc_fill_u32(&output, 8, 0x00060104);
    mpvvlc_fill_u32(&output, 8, 0x00060103);
    for (i = 0; i < 16; i++)
        *output++ = 0x00050200;
    mpvvlc_fill_u32(&output, 16, 0x00050102);
    mpvvlc_fill_u32(&output, 32, 0x00040101);
}
#pragma opt_propagation reset

