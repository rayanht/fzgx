#include "types.h"

extern s32 fn_80046C28(u32 arg0, u32 arg1, s16 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, u8 *arg6, u32 *arg7, u32 *arg8, u32 *arg9);

s32 fn_8004B9A4(u32 arg0, s32 arg1, s32 *arg2) {
    u32 local_20;
    u32 local_1c;
    u32 local_18;
    s16 local_14;
    u8 local_13;
    u8 local_12;
    u8 local_11;
    u8 local_10;

    if (arg1 < 2) {
        return 0;
    }
    if (*(u16 *)arg0 != 32768) {
        return 0;
    }
    if (fn_80046C28(arg0, arg1, &local_14, &local_13, &local_12, &local_11, &local_10, &local_20, &local_1c, &local_18) < 0) {
        return 0;
    }
    *arg2 = local_14;
    return 1;
}
