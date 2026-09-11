#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 __OSUnmaskInterrupts(u32);
extern u32 __OSMaskInterrupts(u32);
extern u32 OSRestoreInterrupts(u32);
extern u32 *lbl_801A6678;

u32 fn_8008EB8C(u32 arg0) {
    u32 old_interrupts;
    u32 old_value;

    old_interrupts = OSDisableInterrupts();
    if (arg0) {
        __OSUnmaskInterrupts(64);
    } else {
        __OSMaskInterrupts(64);
    }
    old_value = *lbl_801A6678;
    *lbl_801A6678 = arg0;
    OSRestoreInterrupts(old_interrupts);
    return old_value;
}
