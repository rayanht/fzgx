#include "types.h"

extern u32 fwrite(u32, u32, u32, u32);

u32 __FileWrite(u32 arg0, u32 arg1, s32 arg2) {
    s32 result;
    if (arg2 == (fwrite(arg1, 1, arg2, arg0))) {
        return arg0;
    }
    return 0;
}
