#include "types.h"

extern u32 gx;

u32 fn_800365A0(u32 value) {
    u32 *p;
    u32 old;

    p = (u32 *)gx;
    p = (u32 *)((u8 *)p + 0x414);
    old = *p;
    *p = value;
    return old;
}
