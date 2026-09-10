#include "types.h"

extern u8 fn_8008D7B0(u32, u32, u32 *);
extern s32 fn_8008A754(void);
extern u32 fn_8008CB20(u32, u32, u32 *, u32);

s32 fn_8008DCCC(u32 arg0, u32 arg1, u32 *arg2) {
    u32 v0;
    u32 v1;

    if (fn_8008D7B0(arg0, arg1, arg2) == 0) {
        return 1;
    }
    if (fn_8008A754() == 0) {
        return 1;
    }
    v0 = *arg2;
    v1 = fn_8008CB20(0xd1, 0, &v0, arg1);
    *arg2 = v0;
    switch ((s32)(v1 & 0xff)) {
    case 0:
        return 0;
    case 2:
        return 2;
    default:
        return 1;
    }
}
