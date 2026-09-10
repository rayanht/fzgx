#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 fn_8002420C(u32);
extern u32 OSRestoreInterrupts(u32);

#pragma peephole off
u32 fn_80024378(u32 arg0) {
    u32 t0;
    t0 = OSDisableInterrupts();
    fn_8002420C(arg0);
    OSRestoreInterrupts(t0);
    return 1;
}
#pragma peephole reset

