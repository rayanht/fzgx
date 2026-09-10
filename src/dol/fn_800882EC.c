
#include "types.h"

extern double j0(double);

static const double one = 1.0;

double fn_800882EC(double x, double *iptr) {
    int i0;
    int i1;
    int j0;
    unsigned int i;
    i0 = *(int *)&x;
    i1 = *(1 + (int *)&x);
    j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
    if (j0 < 20) {
        if (j0 < 0) {
            *(int *)iptr = i0 & 0x80000000;
            *(1 + (int *)iptr) = 0;
            return x;
        } else {
            i = 0x000fffff >> j0;
            if (((i0 & i) | i1) == 0) {
                *iptr = x;
                *(int *)&x &= 0x80000000;
                *(1 + (int *)&x) = 0;
                return x;
            } else {
                *(int *)iptr = i0 & ~i;
                *(1 + (int *)iptr) = 0;
                return x - *iptr;
            }
        }
    } else if (j0 > 51) {
        *iptr = x * one;
        *(int *)&x &= 0x80000000;
        *(1 + (int *)&x) = 0;
        return x;
    } else {
        i = (unsigned int)0xffffffff >> (j0 - 20);
        if ((i1 & i) == 0) {
            *iptr = x;
            *(int *)&x &= 0x80000000;
            *(1 + (int *)&x) = 0;
            return x;
        } else {
            *(int *)iptr = i0;
            *(1 + (int *)iptr) = i1 & ~i;
            return x - *iptr;
        }
    }
}
