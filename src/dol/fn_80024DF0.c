#include "types.h"

extern u32 OSDisableInterrupts(void);
extern void fn_80024C88(u32);
extern u32 OSRestoreInterrupts(u32);

#pragma peephole off
u32 fn_80024DF0(u32 arg0) {
    u32 t0;
    t0 = OSDisableInterrupts();
    fn_80024C88(arg0);
    OSRestoreInterrupts(t0);
    return 1;
}
#pragma peephole reset

