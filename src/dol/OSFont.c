#include <dolphin/os.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

// Hardware or OS state can change asynchronously.
volatile int
    __OSTVMode : FZGX_ADDR___OSTVMode; // fzgx-allow: S2 SDK asynchronous state

u16 OSGetFontEncode(void);

vu16 __VIRegs[59] : FZGX_ADDR___VIRegs;

u16 OSGetFontEncode();

u16 OSGetFontEncode() {
    static u16 fontEncode = -1;
    if (fontEncode <= 1) {
        return fontEncode;
    }
    switch (__OSTVMode) {
    case 0:
        fontEncode = (__VIRegs[(55)] & 2) ? 1u : 0u;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    default:
        fontEncode = 0u;
    }
    return fontEncode;
}
