
#include "types.h"

void __copy_longs_rev_unaligned(void *dst, const void *src, size_t n) {
    unsigned long i, v1, v2;
    unsigned int src_offset, left_shift, right_shift;
    ((unsigned char *)src) = ((unsigned char *)src) + n;
    ((unsigned char *)dst) = ((unsigned char *)dst) + n;
    i = ((unsigned long)((unsigned char *)dst)) & 3;
    if (i) {
        n -= i;
        do
            *--((unsigned char *)dst) = *--((unsigned char *)src);
        while (--i);
    }
    src_offset = ((unsigned int)((unsigned char *)src)) & 3;
    left_shift = src_offset << 3;
    right_shift = 32 - left_shift;
    ((unsigned char *)src) += 4 - src_offset;
    i = n >> 3;
    v1 = *--((unsigned long *)src);
    do {
        v2 = *--((unsigned long *)src);
        *--((unsigned long *)dst) = (v2 << left_shift) | (v1 >> right_shift);
        v1 = *--((unsigned long *)src);
        *--((unsigned long *)dst) = (v1 << left_shift) | (v2 >> right_shift);
    } while (--i);
    if (n & 4) {
        v2 = *--((unsigned long *)src);
        *--((unsigned long *)dst) = (v2 << left_shift) | (v1 >> right_shift);
    }
    n &= 3;
    if (n) {
        ((unsigned char *)src) += src_offset;
        do
            *--((unsigned char *)dst) = *--((unsigned char *)src);
        while (--n);
    }
    return;
}
