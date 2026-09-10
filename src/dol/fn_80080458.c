
#include "types.h"

void fn_80080458(void *dst, const void *src, size_t n) {
    unsigned long i, v1, v2;
    unsigned int src_offset, left_shift, right_shift;
    i = (-(unsigned long)dst) & 3;
    ((unsigned char *)src) = ((unsigned char *)src) - 1;
    ((unsigned char *)dst) = ((unsigned char *)dst) - 1;
    if (i) {
        n -= i;
        do
            *++(((unsigned char *)dst)) = *++(((unsigned char *)src));
        while (--i);
    }
    src_offset = ((unsigned int)(((unsigned char *)src) + 1)) & 3;
    left_shift = src_offset << 3;
    right_shift = 32 - left_shift;
    ((unsigned char *)src) -= src_offset;
    ((unsigned long *)src) = ((unsigned long *)(((unsigned char *)src) + 1)) - 1;
    ((unsigned long *)dst) = ((unsigned long *)(((unsigned char *)dst) + 1)) - 1;
    i = n >> 3;
    v1 = *++(((unsigned long *)src));
    do {
        v2 = *++(((unsigned long *)src));
        *++(((unsigned long *)dst)) = (v1 << left_shift) | (v2 >> right_shift);
        v1 = *++(((unsigned long *)src));
        *++(((unsigned long *)dst)) = (v2 << left_shift) | (v1 >> right_shift);
    } while (--i);
    if (n & 4) {
        v2 = *++(((unsigned long *)src));
        *++(((unsigned long *)dst)) = (v1 << left_shift) | (v2 >> right_shift);
    }
    ((unsigned char *)src) = ((unsigned char *)(((unsigned long *)src) + 1)) - 1;
    ((unsigned char *)dst) = ((unsigned char *)(((unsigned long *)dst) + 1)) - 1;
    n &= 3;
    if (n) {
        ((unsigned char *)src) -= 4 - src_offset;
        do
            *++(((unsigned char *)dst)) = *++(((unsigned char *)src));
        while (--n);
    }
    return;
}
