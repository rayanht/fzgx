#include "types.h"

extern u32 fn_80059AB4(void);
extern u32 fn_80059B44(void);

void fn_8004B180(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    u32 v0;
    fn_80059B44();
    *(u32 *)((u8 *)arg0 + 12) = arg3;
    v0 = (arg4 << 11);
    *(u32 *)((u8 *)arg0 + 16) = v0;
    *(u32 *)((u8 *)arg0 + 76) = arg1;
    *(u32 *)((u8 *)arg0 + 80) = arg2;
    *(u8 *)((u8 *)arg0 + 65) = 1;
    fn_80059AB4();
}
