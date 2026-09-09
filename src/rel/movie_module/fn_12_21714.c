#include "types.h"

extern int fn_12_2D73C(void *arg0, int arg1);
extern int fn_12_2F210(void *arg0, int arg1, int arg2, int arg3, int arg4);

int fn_12_21714(void *arg0, int arg1) {
    int result;
    int value;

    if (!fn_12_2D73C(arg0, 6)) {
        return 0;
    }

    value = fn_12_2F210(arg0, 3, 8, arg1, 0);
    result = 0;
    if (value) {
        result = value;
    }
    return result;
}
