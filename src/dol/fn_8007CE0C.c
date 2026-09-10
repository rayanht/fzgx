
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

BOOL fn_8007CE0C(const decimal *x, const decimal *y) {
    if (x->sig.text[0] == 0) {
        if (y->sig.text[0] == 0)
            return 1;
        return 0;
    }
    if (y->sig.text[0] == 0) {
        if (x->sig.text[0] == 0)
            return 1;
        return 0;
    }
    if (x->exp == y->exp) {
        int i;
        int l = x->sig.length;
        if (l > y->sig.length) {
            l = y->sig.length;
        }
        for (i = 0; i < l; i++) {
            if (x->sig.text[i] != y->sig.text[i]) {
                return 0;
            }
        }
        if (l == x->sig.length) {
            for (; i < y->sig.length; ++i) {
                if (y->sig.text[i] != 0) {
                    return 0;
                }
            }
        } else {
            for (; i < x->sig.length; ++i) {
                if (x->sig.text[i] != 0) {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}
