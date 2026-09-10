
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

typedef struct decform {
    char style;
    char reserved;
    s16 digits;
} decform;

extern double exp(double);

void __num2dec_internal(decimal *d, f64 x);

static inline int __must_round(const decimal *d, int digits) {
    u8 const *i = d->sig.text + digits;
    if (*i > 5) {
        return 1;
    }
    if (*i < 5) {
        return -1;
    }
    {
        u8 const *e = d->sig.text + d->sig.length;
        for (i++; i < e; i++) {
            if (*i != 0) {
                return 1;
            }
        }
    }
    if (d->sig.text[digits - 1] & 1) {
        return 1;
    }
    return -1;
}

static inline void __dorounddecup(decimal *d, int digits) {
    u8 *b = d->sig.text;
    u8 *i = b + digits - 1;
    while (1) {
        if (*i < 9) {
            *i += 1;
            break;
        }
        if (i == b) {
            *i = 1;
            d->exp++;
            break;
        }
        *i-- = 0;
    }
}

static inline void __rounddec(decimal *d, int digits) {
    if (digits > 0 && digits < d->sig.length) {
        int round_direction = __must_round(d, digits);
        d->sig.length = digits;
        if (round_direction >= 0) {
            __dorounddecup(d, digits);
        }
    }
}

void __num2dec(const decform *form, f64 x, decimal *d) {
    s16 digits = form->digits;
    int i;
    __num2dec_internal(d, x);
    if (d->sig.text[0] > 9) {
        return;
    }
    if (digits > 36) {
        digits = 36;
    }
    __rounddec(d, digits);
    while (d->sig.length < digits) {
        d->sig.text[d->sig.length++] = 0;
    }
    d->exp -= d->sig.length - 1;
    for (i = 0; i < d->sig.length; i++) {
        d->sig.text[i] += '0';
    }
}
