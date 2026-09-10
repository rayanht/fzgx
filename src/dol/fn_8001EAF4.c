#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*ARCallback)(void);

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

extern ARCallback lbl_801A69E0;

void fn_8001EAF4(__OSInterrupt interrupt, OSContext *context) {
    OSContext exceptionContext;
    u16 tmp;
    tmp = __DSPRegs[5];
    tmp = (u16)((tmp & ~0x00000088) | 0x20);
    __DSPRegs[5] = tmp;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (lbl_801A69E0) {
        (*lbl_801A69E0)();
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
