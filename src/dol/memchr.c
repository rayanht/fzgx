#include "types.h"

s32 memchr(u32 arg0, u32 arg1, u32 arg2) {
    u32 unk_1;
    u32 unk_2;
    u32 v2;
    arg1 &= 0xff;
    arg0 -= 1;
    arg2 += 1;
    while (((arg2) -= 1) != 0) {
        arg0 = (u32)((u8 *)arg0 + 1);
        if (*(u8 *)arg0 == arg1) {
            return arg0;
        }
    }
    return 0;
}
