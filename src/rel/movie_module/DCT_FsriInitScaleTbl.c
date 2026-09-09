#include "types.h"

extern double lbl_12_bss_BB0[64];

static inline int dctFsriScanIndex(int index) {
    int row = index / 8;
    int offset = index % 8;
    int result;
    if ((row % 2) == 0) {
        offset *= 2;
    } else {
        row--;
        offset = offset * 2 + 1;
    }
    result = offset + row * 8;
    if ((result < 0) || (result >= 256)) {
        while (1) {
        }
    }
    return result;
}

void DCT_FsriInitScaleTbl(float scale_table[64]) {
    int index;
    for (index = 0; index < 64; index++) {
        scale_table[dctFsriScanIndex(index)] = (float)lbl_12_bss_BB0[index];
    }
}
