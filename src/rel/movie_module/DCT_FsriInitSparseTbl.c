#pragma opt_loop_invariants off
#include "types.h"

void *memset(void *destination, int value, unsigned long size);

void fn_12_4D14(void);

void fn_12_4CEC(const double input[8][8], double output[8][8]);

extern float lbl_12_bss_DB0[64][64];

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

static inline void dctFsriStoreSparseCoefficient(int coefficient, int index, const double *value) {
    lbl_12_bss_DB0[dctFsriScanIndex(coefficient)][index] = (float)*value;
}

void DCT_FsriInitSparseTbl(void) {
    union DctCoefficientMatrix {
        double matrix[8][8];
        double coefficients[64];
    } source, destination;
    int coefficient;
    memset(lbl_12_bss_DB0, 0, sizeof(lbl_12_bss_DB0));
    fn_12_4D14();
    for (coefficient = 0; coefficient < 64; coefficient++) {
        int index;
        for (index = 0; index < 64; index++) {
            if (index == coefficient) {
                source.coefficients[index] = 1.0 / lbl_12_bss_BB0[index];
            } else {
                source.coefficients[index] = 0.0;
            }
        }
        fn_12_4CEC(source.matrix, destination.matrix);
        for (index = 0; index < 64; index++) {
            dctFsriStoreSparseCoefficient(coefficient, index, &destination.coefficients[index]);
        }
    }
}
