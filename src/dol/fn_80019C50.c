#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu32 __DIRegs[16] : FZGX_ADDR___DIRegs;

extern DVDCommandBlock *executing_801A68C0;

// Hardware or OS state can change asynchronously.
extern volatile BOOL PausingFlag_801A68D0; // fzgx-allow: S2 SDK asynchronous state

// Hardware or OS state can change asynchronously.
extern volatile BOOL FatalErrorFlag_801A68D8; // fzgx-allow: S2 SDK asynchronous state

extern vu32 ResumeFromHere_801A68E8;

extern DVDCommandBlock DummyCommandBlock_8015CE80;

BOOL fn_80019C50(void) {
    BOOL enabled;
    s32 retVal;
    s32 state;
    u32 coverReg;
    enabled = OSDisableInterrupts();
    if (FatalErrorFlag_801A68D8) {
        state = -1;
    } else if (PausingFlag_801A68D0) {
        state = 8;
    } else {
        if (executing_801A68C0 == (DVDCommandBlock *)0) {
            state = 0;
        } else if (executing_801A68C0 == &DummyCommandBlock_8015CE80) {
            state = 0;
        } else {
            state = executing_801A68C0->state;
        }
    }
    switch (state) {
    case 1:
    case 9:
    case 10:
    case 2:
        retVal = 1;
        break;
    case -1:
    case 11:
    case 7:
    case 3:
    case 4:
    case 5:
    case 6:
        retVal = 0;
        break;
    case 0:
    case 8:
        coverReg = __DIRegs[1];
        if (((coverReg >> 2) & 1) || (coverReg & 1)) {
            retVal = 0;
        } else if (ResumeFromHere_801A68E8) {
            retVal = 0;
        } else {
            retVal = 1;
        }
    }
    OSRestoreInterrupts(enabled);
    return retVal;
}
