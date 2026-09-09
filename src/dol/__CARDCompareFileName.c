#include "types.h"

s32 __CARDCompareFileName(u32 arg0, s8 *arg1) {
    u8 *v0;
    s8 *v1;
    s8 v4;
    s32 v2;
    s8 v3;

    v0 = (u8 *)arg0 + 8;
    v1 = arg1;
    v2 = 32;
    while (--v2 >= 0) {
        v3 = *(s8 *)v0;
        v0++;
        v4 = *v1;
        v1++;
        if (v3 != v4) {
            return 0;
        }
        if (v4 == 0) {
            return 1;
        }
    }
    if (*v1 == 0) {
        return 1;
    }
    return 0;
}
