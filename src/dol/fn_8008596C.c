#include "types.h"

/* MSL __float_nan / __float_huge */
extern unsigned long lbl_801A6648[];
extern unsigned long lbl_801A664C[];

#define NAN (*(float *)lbl_801A6648)
#define INFINITY (*(float *)lbl_801A664C)

static const double one = 1.00000000000000000000e+00;
static const double pi = 3.14159265358979311600e+00;
static const double pio2_hi = 1.57079632679489655800e+00;
static const double pio2_lo = 6.12323399573676603587e-17;
static const double pS0 = 1.66666666666666657415e-01;
static const double pS1 = -3.25565818622400915405e-01;
static const double pS2 = 2.01212532134862925881e-01;
static const double pS3 = -4.00555345006794114027e-02;
static const double pS4 = 7.91534994289814532176e-04;
static const double pS5 = 3.47933107596021167570e-05;
static const double qS1 = -2.40339491173441421878e+00;
static const double qS2 = 2.02094576023350569471e+00;
static const double qS3 = -6.88283971605453293030e-01;
static const double qS4 = 7.70381505559019352791e-02;

static inline double sqrt(double x) {
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0) {
        return 0;
    } else if (x) {
        return NAN;
    }
    return INFINITY;
}

double fn_8008596C(double x) {
    double z;
    double p;
    double q;
    double r;
    double w;
    double s;
    double c;
    double df;
    int hx;
    int ix;
    hx = *(int *)&x;
    ix = hx & 0x7fffffff;
    if (ix >= 0x3ff00000) {
        if (((ix - 0x3ff00000) | *(1 + (int *)&x)) == 0) {
            if (hx > 0)
                return 0.0;
            else
                return pi + 2.0 * pio2_lo;
        }
        return NAN;
    }
    if (ix < 0x3fe00000) {
        if (ix <= 0x3c600000)
            return pio2_hi + pio2_lo;
        z = x * x;
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        r = p / q;
        return pio2_hi - (x - (pio2_lo - x * r));
    } else if (hx < 0) {
        z = (one + x) * 0.5;
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        s = sqrt(z);
        r = p / q;
        w = r * s - pio2_lo;
        return pi - 2.0 * (s + w);
    } else {
        z = (one - x) * 0.5;
        s = sqrt(z);
        df = s;
        *(1 + (int *)&df) = 0;
        c = (z - df * df) / (s + df);
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        r = p / q;
        w = r * s + c;
        return 2.0 * (df + w);
    }
}
