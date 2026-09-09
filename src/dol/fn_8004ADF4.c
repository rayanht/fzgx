#include "types.h"

extern void fn_80046718(void);
extern void fn_80046738(void);

s32 fn_8004ADF4(u32 arg0) {
    fn_80046738();
    *(u32 *)((u8 *)arg0 + 48) = 0;
    *(u8 *)((u8 *)arg0 + 3) = 0;
    if ((s32)*(u32 *)((u8 *)arg0 + 16) == 0) {
    *(u8 *)((u8 *)arg0 + 1) = 3;
    } else {
    *(u8 *)((u8 *)arg0 + 1) = 2;
    }
    *(u8 *)((u8 *)arg0 + 2) = 0;
    *(u32 *)((u8 *)arg0 + 32) = 0;
    *(u32 *)((u8 *)arg0 + 36) = 0;
    *(u8 *)((u8 *)arg0 + 67) = 1;
    *(u32 *)((u8 *)arg0 + 88) = (0x100000 - 1);
    fn_80046718();
    return 1;
}
