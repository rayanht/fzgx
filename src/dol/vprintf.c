#include "types.h"

extern u8 __files[320];
extern s32 fwide(u32, u32);
extern u32 __begin_critical_region(u32);
extern u32 __FileWrite(void);
extern u32 __end_critical_region(u32);
extern u32 __pformatter_80080A38(u32, u32, u32, u32);

s32 vprintf(u32 format, u32 args) {
    u32 stream;
    u32 result;

    stream = (u32)&__files + 0x50;
    if (fwide(stream, -1) >= 0) {
        return -1;
    }
    __begin_critical_region(2);
    result = __pformatter_80080A38((u32)&__FileWrite, stream, format, args);
    __end_critical_region(2);
    return result;
}
