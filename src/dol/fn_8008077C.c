#include "types.h"

extern s32 __pformatter(u32, u32, u32, u32);
extern void fn_80080974(void);

s32 fn_8008077C(u32 arg0, u32 arg1, u32 arg2) {
    s32 result;
    struct {
        u32 a[3];
    } loc_8;

    loc_8.a[0] = arg0;
    loc_8.a[1] = -1;
    loc_8.a[2] = 0;
    result = __pformatter((u32)fn_80080974, (u32)&loc_8, arg1, arg2);
    if (arg0 != 0) {
        s32 index;

        index = -2;
        if ((u32)result < (u32)-1) {
            index = result;
        }
        *(u8 *)((u8 *)arg0 + index) = 0;
    }
    return result;
}
