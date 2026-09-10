#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

void DSPSendMailToDSP(u32 mail) {
    __DSPRegs[0] = mail >> 16;
    __DSPRegs[1] = mail;
}
