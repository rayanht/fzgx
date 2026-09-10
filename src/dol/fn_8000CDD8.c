#include <dolphin/os.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

extern u16 lbl_801A6438;

// Hardware or OS state can change asynchronously.
volatile int
    __OSTVMode : FZGX_ADDR___OSTVMode; // fzgx-allow: S2 SDK asynchronous state

vu16 __VIRegs[59] : FZGX_ADDR___VIRegs;

u16 fn_8000CDD8() {

    if (lbl_801A6438 <= 1) {
        return lbl_801A6438;
    }
    switch (__OSTVMode) {
    case 0:
        lbl_801A6438 = (__VIRegs[(55)] & 2) ? 1u : 0u;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        lbl_801A6438 = 0u;
    }
    return lbl_801A6438;
}
