#include "types.h"

extern s32 fn_80089244(void *out_a, void *out_b);
extern void fn_8008B8B4(void *value);
extern void fn_8008B830(void *value);
extern s32 fn_8008AB20(void *value, void *out_a, s32 arg2, s32 arg3, s32 arg4);
extern void fn_800891B4(void *value);

s32 fn_8008AF58(s32 arg) {
    s32 result;
    void *value_b;
    void *value_c;
    void *value_a;

    result = fn_80089244(&value_c, &value_a);
    if (result == 0) {
        if (result == 0) {
            if (arg == 0x90) {
                fn_8008B8B4(value_a);
            } else {
                fn_8008B830(value_a);
            }
        }
        result = fn_8008AB20(value_a, &value_b, 2, 3, 1);
        if (result == 0) {
            fn_800891B4(value_b);
        }
        fn_800891B4(value_c);
    }
    return result;
}
