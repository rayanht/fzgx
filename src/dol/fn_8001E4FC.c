#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*AIDCallback)();

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

extern AIDCallback lbl_801A69A4;

extern u8 *lbl_801A69A8;

// Hardware or OS state can change asynchronously.
extern volatile s32 lbl_801A69B4; // fzgx-allow: S2 SDK asynchronous state

void __AICallbackStackSwitch(register AIDCallback cb);

void __AICallbackStackSwitch(register AIDCallback cb);

void fn_8001E4FC(s16 interrupt, OSContext *context) {
    OSContext tempContext;
    u32 temp = __DSPRegs[5];
    __DSPRegs[5] = (temp & ~0xA0) | 8;
    OSClearContext(&tempContext);
    OSSetCurrentContext(&tempContext);
    if (lbl_801A69A4 && !lbl_801A69B4) {
        lbl_801A69B4 = 1;
        if (lbl_801A69A8) {
            __AICallbackStackSwitch(lbl_801A69A4);
        } else {
            lbl_801A69A4();
        }
        lbl_801A69B4 = 0;
    }
    OSClearContext(&tempContext);
    OSSetCurrentContext(context);
}
