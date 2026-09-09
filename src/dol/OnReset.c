#include <dolphin/os.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu16 __MEMRegs[64] : FZGX_ADDR___MEMRegs;

BOOL OnReset(BOOL final) {
    if (final != 0) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xf0000000);
    }
    return 1;
}
