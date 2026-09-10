#include "types.h"

typedef struct MovieSize {
    s32 value0;
    s32 value1;
    s32 value2;
    s16 value3;
    s16 value4;
} MovieSize;

void fn_12_2A674(int arg0, int arg1, int arg2, MovieSize *out) {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;

    a = (arg1 + 15) / 16;
    b = a << 4;
    c = (b + 31) / 32;
    d = b / 2;
    e = (d + 31) / 32;
    out->value4 = c << 5;
    out->value3 = e << 5;
    f = (arg2 + 15) / 16;
    g = f << 4;
    h = g / 2;
    out->value2 = arg0;
    out->value0 = out->value2 + g * (c << 5);
    out->value1 = out->value0 + h * (e << 5);
}
