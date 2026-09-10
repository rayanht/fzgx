#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*OSResetCallback)(void);

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

vu32 __PIRegs[12] : FZGX_ADDR___PIRegs;

extern OSResetCallback lbl_801A67D8;

extern BOOL lbl_801A67DC;

extern BOOL lbl_801A67E0;

extern OSTime lbl_801A67F0;

void __OSResetSWInterruptHandler(__OSInterrupt interrupt, OSContext *context) {
    OSResetCallback callback;
    lbl_801A67F0 = __OSGetSystemTime();
    while (__OSGetSystemTime() - lbl_801A67F0 <
               (((100) * (((u32)__OSBusClock / 4) / 125000)) / 8) &&
           !(__PIRegs[0] & 0x00010000)) {
        ;
    }
    if (!(__PIRegs[0] & 0x00010000)) {
        lbl_801A67E0 = lbl_801A67DC = 1;
        __OSMaskInterrupts((0x80000000u >> (22)));
        if (lbl_801A67D8) {
            callback = lbl_801A67D8;
            lbl_801A67D8 = ((void *)0);
            callback();
        }
    }
    __PIRegs[0] = 2;
}
