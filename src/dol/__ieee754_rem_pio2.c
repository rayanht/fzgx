
#include "types.h"

extern int __kernel_rem_pio2(double *, double *, int, int, int, const int *);

extern double __fabs(double value);

extern const int lbl_80095408[];

extern const int lbl_80095510[];

static const double zero = 0.0;

static const double half = 0.5;

static const double two24 = 1.67772160000000000000e+07;

static const double invpio2 = 6.36619772367581382433e-01;

static const double pio2_1 = 1.57079632673412561417e+00;

static const double pio2_1t = 6.07710050650619224932e-11;

static const double pio2_2 = 6.07710050630396597660e-11;

static const double pio2_2t = 2.02226624879595063154e-21;

static const double pio2_3 = 2.02226624871116645580e-21;

static const double pio2_3t = 8.47842766036889956997e-32;

int __ieee754_rem_pio2(double x, double *y) {
    double z, w, t, r, fn;
    double tx[3];
    int e0, i, j, nx, n, ix, hx;
    hx = *(int *)&x;
    ix = hx & 0x7fffffff;
    if (ix <= 0x3fe921fb) {
        y[0] = x;
        y[1] = 0;
        return 0;
    }
    if (ix < 0x4002d97c) {
        if (hx > 0) {
            z = x - pio2_1;
            if (ix != 0x3ff921fb) {
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;
            } else {
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z - y[0]) - pio2_2t;
            }
            return 1;
        } else {
            z = x + pio2_1;
            if (ix != 0x3ff921fb) {
                y[0] = z + pio2_1t;
                y[1] = (z - y[0]) + pio2_1t;
            } else {
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z - y[0]) + pio2_2t;
            }
            return -1;
        }
    }
    if (ix <= 0x413921fb) {
        t = __fabs(x);
        n = (int)(t * invpio2 + half);
        fn = (double)n;
        r = t - fn * pio2_1;
        w = fn * pio2_1t;
        if (n < 32 && ix != lbl_80095510[n - 1]) {
            y[0] = r - w;
        } else {
            j = ix >> 20;
            y[0] = r - w;
            i = j - ((*(int *)&y[0] >> 20) & 0x7ff);
            if (i > 16) {
                t = r;
                r = t - fn * pio2_2;
                w = fn * pio2_2t - ((t - r) - fn * pio2_2);
                y[0] = r - w;
                i = j - ((*(int *)&y[0] >> 20) & 0x7ff);
                if (i > 49) {
                    t = r;
                    w = fn * pio2_3;
                    r = t - w;
                    w = fn * pio2_3t - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        }
        return n;
    }
    if (ix >= 0x7ff00000) {
        y[0] = y[1] = x - x;
        return 0;
    }
    *(1 + (int *)&z) = *(1 + (int *)&x);
    e0 = (ix >> 20) - 1046;
    *(int *)&z = ix - (e0 << 20);
    for (i = 0; i < 2; i++) {
        tx[i] = (double)(int)z;
        z = (z - tx[i]) * two24;
    }
    tx[2] = z;
    nx = 3;
    while (tx[nx - 1] == zero)
        nx--;
    n = __kernel_rem_pio2(tx, y, e0, nx, 2, lbl_80095408);
    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    return n;
}
