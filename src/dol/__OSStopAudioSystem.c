#include <dolphin/os.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

void __OSStopAudioSystem(void) {
    u32 r28;
    __DSPRegs[5] = 0x804;
    r28 = __DSPRegs[27];
    __DSPRegs[27] = r28 & ~0x8000;
    r28 = (__DSPRegs[5]);
    while (r28 & (0x400)) {
        r28 = (__DSPRegs[5]);
    };
    r28 = (__DSPRegs[5]);
    while (r28 & (0x200)) {
        r28 = (__DSPRegs[5]);
    };
    __DSPRegs[5] = 0x8ac;
    __DSPRegs[0] = 0;
    while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000)
        ;
    r28 = OSGetTick();
    while ((s32)(OSGetTick() - r28) < 0x2c)
        ;
    __DSPRegs[5] |= 1;
    r28 = (__DSPRegs[5]);
    while (r28 & (0x001)) {
        r28 = (__DSPRegs[5]);
    };
}
