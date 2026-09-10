#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*DVDLowCallback)(u32 intType);

vu32 __DIRegs[16] : FZGX_ADDR___DIRegs;

// Hardware or OS state can change asynchronously.
extern volatile BOOL StopAtNextInt_801A6858; // fzgx-allow: S2 SDK asynchronous state

extern DVDLowCallback Callback_801A6860;

// Hardware or OS state can change asynchronously.
extern volatile BOOL WaitingCoverClose_801A6874; // fzgx-allow: S2 SDK asynchronous state

BOOL DVDLowWaitCoverClose(DVDLowCallback callback) {
    Callback_801A6860 = callback;
    WaitingCoverClose_801A6874 = 1;
    StopAtNextInt_801A6858 = 0;
    __DIRegs[1] = 2;
    return 1;
}
