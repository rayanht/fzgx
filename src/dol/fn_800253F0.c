#include "types.h"

struct fn_800253F0_Arg0 {
    u32 unk_0;
};

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern u32 (*lbl_801A64FC)(u32);

#pragma peephole off
s32 fn_800253F0(struct fn_800253F0_Arg0 *arg0) {
    u32 t0;
    t0 = OSDisableInterrupts();
    lbl_801A64FC(arg0->unk_0);
    OSRestoreInterrupts(t0);
    return 1;
}
#pragma peephole reset

