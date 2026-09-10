#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*AISCallback)(u32 count);

vu32 __AIRegs[8] : FZGX_ADDR___AIRegs;

extern AISCallback lbl_801A69A0;

void fn_8001E480(s16 interrupt, OSContext *context) {
    OSContext tmpContext;
    __AIRegs[0] |= 8;
    OSClearContext(&tmpContext);
    OSSetCurrentContext(&tmpContext);
    if (lbl_801A69A0 != ((void *)0)) {
        lbl_801A69A0(__AIRegs[2]);
    }
    OSClearContext(&tmpContext);
    OSSetCurrentContext(context);
}
