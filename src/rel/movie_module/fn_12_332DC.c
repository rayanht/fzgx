#include "types.h"

extern const f64 lbl_12_rodata_1100;

int fn_12_332DC(int a, int b, int c, int d) {
    int result;

    if ((f64)a * (f64)d <= (f64)c * (f64)b) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
