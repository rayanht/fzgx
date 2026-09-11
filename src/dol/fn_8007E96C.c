#include "types.h"

#pragma use_lmw_stmw on

typedef s32 (*fn_8007E96C_Compare)(u32, u32);

#pragma opt_propagation off
s32 fn_8007E96C(u32 key, u32 base, u32 count, u32 size, fn_8007E96C_Compare compare) {
    u32 element;
    u32 low;
    u32 high;
    u32 middle;
    s32 result;
    u32 first;

    if (key == 0 || base == 0 || count == 0 || size == 0 || compare == 0) {
        return 0;
    }

    first = base;
    result = compare(key, base);
    if (result == 0) {
        return first;
    }
    if (result < 0) {
        return 0;
    }

    high = count - 1;
    low = 1;

    while (low <= high) {
        middle = (low + high) / 2;
        element = base + size * middle;
        result = compare(key, element);
        if (result == 0) {
            return element;
        }
        if (result < 0) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return 0;
}
#pragma opt_propagation reset

