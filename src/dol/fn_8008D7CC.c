#include "types.h"

extern s32 fn_8008A754(u32 arg0);
extern u8 fn_8008CB38(u32 arg0, u32 arg1, u32 arg2, u8 arg3);

s32 fn_8008D7CC(u32 arg0, u32 arg1, s32 arg2) {
    s32 mode;
    u8 value;

    mode = 0;
    if (fn_8008A754(arg0) == 0) {
        return 1;
    }

    if (arg2 == 0) {
        mode = 0;
    } else if (arg2 == 1) {
        mode = 1;
    } else if (arg2 == 2) {
        mode = 2;
    }

    value = fn_8008CB38(0xD4, arg0, arg1, (u8)mode);
    switch (value) {
    case 0:
        return 0;
    case 2:
        return 2;
    case 1:
    default:
        return 1;
    }
}
