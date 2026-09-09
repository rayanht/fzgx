#include "types.h"

const char *fn_12_4E14(void);

extern const double lbl_12_rodata_610[8];

extern double lbl_12_bss_BB0[64];

extern const char *lbl_12_bss_BA8;

void DCT_FsriInitSparseTbl(void);

void DCT_FsriInit(void) {
    int row;
    int column;
    lbl_12_bss_BA8 = fn_12_4E14();
    for (row = 0; row < 8; row++) {
        for (column = 0; column < 8; column++) {
            lbl_12_bss_BB0[row * 8 + column] = lbl_12_rodata_610[row] * lbl_12_rodata_610[column];
        }
    }
    DCT_FsriInitSparseTbl();
}
