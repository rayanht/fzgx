#include "types.h"

extern u32 fn_8004AC04(u32, u32);
extern u32 fn_8004B180(u32, u32, u32, u32, u32);
extern void fn_8004B0EC(void *);

void fn_12_34F04(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    fn_8004B0EC((void *)arg0);
    fn_8004B180(arg0, arg1, arg2, arg3, arg4);
    fn_8004AC04(arg0, arg4);
}
