#include "types.h"

typedef struct DivResult {
    s32 quot;
    s32 rem;
} DivResult;

DivResult fn_8007E914(s32 numer, s32 denom) {
    s32 quotient;
    s32 numer_sign = 1;
    s32 denom_sign = 1;
    DivResult result;

    if (numer < 0) {
        numer = -numer;
        numer_sign = -1;
    }
    if (denom < 0) {
        denom = -denom;
        denom_sign = -1;
    }

    quotient = numer_sign * denom_sign * (numer / denom);
    result.quot = quotient;
    result.rem = numer * numer_sign - denom_sign * (quotient * denom);
    return result;
}
