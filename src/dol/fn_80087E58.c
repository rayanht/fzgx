#include "types.h"

typedef union {
    f64 value;
    struct {
        u32 hi;
        u32 lo;
    } words;
} DoubleBits;

f64 fn_80087E58(f64 a, f64 b) {
    DoubleBits other;
    DoubleBits result;

    result.value = a;
    other.value = b;
    result.words.hi = (result.words.hi & 0x7FFFFFFF) | (other.words.hi & 0x80000000);
    return result.value;
}
