#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 lbl_801A6E30;
extern void fn_8008FAB4(u32, u32, u32);
extern u32 lbl_801A6E34;
extern u8 lbl_801A6E3C;
extern u32 OSRestoreInterrupts(u32);

u32 fn_8008F6BC(u32 arg0, u32 arg1) {
    u32 interrupt_state;
    u32 base;
    interrupt_state = OSDisableInterrupts();
    if (lbl_801A6E30 & 0x10000) {
        base = 0x1000;
    } else {
        base = 0;
    }
    base += 0x20000;
    base -= 0x2000;
    fn_8008FAB4(base, arg0, (arg1 + 3) & ~3);
    lbl_801A6E34 = 0;
    lbl_801A6E3C = 0;
    OSRestoreInterrupts(interrupt_state);
    return 0;
}
