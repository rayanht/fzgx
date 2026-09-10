
#include "types.h"

typedef struct decimal {
    char sign;
    char reserved;
    s16 exp;
    struct {
        u8 length;
        u8 text[36];
        u8 reserved;
    } sig;
} decimal;

extern double exp(double);

extern double frexp(double, int *);

extern double ldexp(double, int);

extern double modf(double, double *);

static inline int __fpclassifyf(f32 x) {
    switch ((*(s32 *)&x) & 0x7F800000) {
    case 0x7F800000: {
        if ((*(s32 *)&x) & 0x007FFFFF)
            return 1;
        return 2;
    }
    case 0: {
        if ((*(s32 *)&x) & 0x007FFFFF)
            return 5;
        return 3;
    }
    }
    return 4;
}

static inline int __fpclassifyd(f64 x) {
    switch (*(int *)&x & 0x7FF00000) {
    case 0x7FF00000: {
        if ((*(int *)&x & 0x000FFFFF) || (*(1 + (int *)&x) & 0xFFFFFFFF))
            return 1;
        return 2;
    }
    case 0: {
        if ((*(int *)&x & 0x000FFFFF) || (*(1 + (int *)&x) & 0xFFFFFFFF))
            return 5;
        return 3;
    }
    }
    return 4;
}

void fn_8007CF18(decimal *result, s32 exp);

void fn_8007E69C(decimal *result, const decimal *x, const decimal *y);

static inline int __count_trailing_zerol(u32 x) {
    int result = 0;
    int bits_not_checked = sizeof(u32) * 8;
    int n = bits_not_checked / 2;
    int mask_size = n;
    u32 mask = (~0UL) >> (bits_not_checked - n);
    while (bits_not_checked) {
        if (!(x & mask)) {
            result += mask_size;
            x >>= mask_size;
            bits_not_checked -= mask_size;
        } else if (mask == 1) {
            break;
        }
        if (n > 1) {
            n /= 2;
        }
        if (mask > 1) {
            mask >>= n;
            mask_size -= n;
        }
    }
    return result;
}

static inline int __count_trailing_zero(f64 x) {
    u32 *l = (u32 *)&x;
    if (l[1] != 0) {
        return __count_trailing_zerol(l[1]);
    }
    return (int)(sizeof(u32) * 8 + __count_trailing_zerol(l[0] | 0x00100000));
}

static inline void __ull2dec(decimal *result, u64 val) {
    result->sign = 0;
    if (val == 0) {
        result->exp = 0;
        result->sig.length = 1;
        result->sig.text[0] = 0;
        return;
    }
    result->sig.length = 0;
    for (; val != 0; val /= 10) {
        result->sig.text[result->sig.length++] = (u8)(val % 10);
    }
    {
        u8 *i = result->sig.text;
        u8 *j = result->sig.text + result->sig.length;
        for (; i < --j; ++i) {
            u8 t = *i;
            *i = *j;
            *j = t;
        }
    }
    result->exp = result->sig.length - 1;
}

void __num2dec_internal(decimal *d, f64 x) {
    s8 sign = (s8)(((int)(*(int *)&x & 0x80000000)) != 0);
    if (x == 0) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = 0;
        return;
    }
    if (!(((sizeof(x) == sizeof(f32)) ? __fpclassifyf((f32)(x)) : __fpclassifyd((f64)(x))) > 2)) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] =
            ((sizeof(x) == sizeof(f32)) ? __fpclassifyf((f32)(x)) : __fpclassifyd((f64)(x))) == 1
                ? 'N'
                : 'I';
        return;
    }
    if (sign != 0) {
        x = -x;
    }
    {
        int exp;
        f64 frac = frexp(x, &exp);
        s32 num_bits_extract = 53 - __count_trailing_zero(frac);
        f64 integer;
        decimal int_d, pow2_d;
        fn_8007CF18(&pow2_d, exp - num_bits_extract);
        modf(ldexp(frac, num_bits_extract), &integer);
        __ull2dec(&int_d, (u64)integer);
        fn_8007E69C(d, &int_d, &pow2_d);
        d->sign = sign;
    }
}
