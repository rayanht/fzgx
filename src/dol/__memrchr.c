#include "types.h"

s32 __memrchr(u32 arg0, u32 arg1, u32 arg2) {
    u32 v1;

    arg1 = (u8)arg1;
    arg0 += arg2;
    arg2++;
    while (--arg2 != 0) {
        arg0--;
        if (*(u8 *)arg0 == arg1) {
            return arg0;
        }
    }
    return 0;
}

