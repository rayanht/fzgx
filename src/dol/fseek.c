#include "types.h"

extern u32 __begin_critical_region(u32);
extern u32 __end_critical_region(u32);
extern u32 fn_8007FC34(u32, u32, u32);

u32 fseek(u32 arg0, u32 arg1, u32 arg2) {
    u32 result;

    __begin_critical_region(2);
    result = fn_8007FC34(arg0, arg1, arg2);
    __end_critical_region(2);
    return result;
}
