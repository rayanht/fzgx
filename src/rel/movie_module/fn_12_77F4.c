#include "types.h"

typedef struct {
    int first;
    int second;
} FnResult;

typedef struct {
    char pad[0x1d8];
    void *value;
} MovieObject;

typedef struct {
    char pad[0xc];
    s16 x;
    s16 y;
} Scale;

extern FnResult fn_8007E914(void *arg0, void *arg1);

void fn_12_77F4(MovieObject *movie, void *arg1, int *out, const Scale *scale) {
    FnResult result;
    s16 x;
    s16 y;
    int first;
    int second;

    result = fn_8007E914(arg1, movie->value);
    first = result.first;
    second = result.second;
    x = scale->x;
    y = scale->y;
    out[0] = (first << 3) * x + (second << 3);
    out[1] = (first << 4) * y + (second << 4);
}
