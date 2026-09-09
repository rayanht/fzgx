#include "types.h"

extern u32 __begin_critical_region(u32);
extern u32 __fwrite(u32, u32, u32, u32);
extern u32 __end_critical_region(u32);

u32 fwrite(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t0;
    u32 t1;

    v0 = arg0;
    v1 = arg1;
    v2 = arg2;
    v3 = arg3;
    t0 = __begin_critical_region(2);
    t1 = __fwrite(v0, v1, v2, v3);
    v0 = t1;
    __end_critical_region(2);
    return v0;
}
