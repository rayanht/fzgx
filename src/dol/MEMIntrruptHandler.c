#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

extern OSErrorHandler __OSErrorTable[(16 + 1)];

vu16 __MEMRegs[64] : FZGX_ADDR___MEMRegs;

void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext *context) {
    u32 addr;
    u32 cause;
    cause = __MEMRegs[0xf];
    addr = (((u32)__MEMRegs[0x12] & 0x3ff) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;
    if (__OSErrorTable[15]) {
        __OSErrorTable[15](15, context, cause, addr);
        return;
    }
    __OSUnhandledException(15, context, cause, addr);
}
