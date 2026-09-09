#include "types.h"

unsigned int UTY_MulDiv(int multiplicand, int multiplier, int divisor) {
    if (divisor == 0) {
        unsigned int limit = 0x80000000u;
        unsigned int sign = (unsigned int)(multiplicand ^ multiplier) >> 31;
        return sign == 0 ? limit - 1 : limit;
    }
    return (unsigned int)(((long long)multiplicand * multiplier) / divisor);
}
