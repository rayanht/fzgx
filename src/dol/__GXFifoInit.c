#include "types.h"

extern u32 __OSSetInterruptHandler(u32, u32);
extern u32 __OSUnmaskInterrupts(u32);
extern u32 fn_800102AC(u32);
extern u32 lbl_801A6BF0;
extern u32 lbl_801A6BF4;
extern u32 lbl_801A6BF8;
extern u32 lbl_801A6C00;
extern void GXCPInterruptHandler(void);

u32 __GXFifoInit(void) {
    u32 t1, t2;
    __OSSetInterruptHandler(17, (u32)GXCPInterruptHandler);
    t1 = __OSUnmaskInterrupts(16384);
    t2 = fn_800102AC(t1);
    lbl_801A6BF8 = t2;
    lbl_801A6C00 = 0;
    lbl_801A6BF0 = 0;
    lbl_801A6BF4 = 0;
    return t2;
}
