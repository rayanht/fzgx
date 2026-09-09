#include "types.h"

extern u32 gx;

u32 fn_8003658C(u32 arg0) {
    u32 *p;
    u32 v0;

    p = (u32 *)gx + 0x410 / 4;
    v0 = *p++;
    p--;
    *p = arg0;
    return v0;
}
