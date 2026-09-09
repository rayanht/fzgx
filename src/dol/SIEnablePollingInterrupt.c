#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/si.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

struct SIBiosBss {
    SIPacket Packet[4];
    OSAlarm Alarm[4];
    OSTime TypeTime[4];
    OSTime XferTime[4];
    SITypeAndStatusCallback TypeCallback[4][4];
    __OSInterruptHandler RDSTHandler[4];
    BOOL InputBufferValid[4];
    u32 InputBuffer[4][2];
    vu32 InputBufferVcount[4];
};

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern struct SIBiosBss Packet_8015CA10;

BOOL SIEnablePollingInterrupt(BOOL enable) {
    struct SIBiosBss *bss = &Packet_8015CA10;

    BOOL enabled;
    BOOL rc;
    u32 reg;
    int i;
    enabled = OSDisableInterrupts();
    reg = __SIRegs[13];
    rc = (reg & 0x08000000) ? 1 : 0;
    if (enable) {
        reg |= 0x08000000;
        for (i = 0; i < 4; ++i) {
            (bss->InputBufferVcount)[i] = 0;
        }
    } else {
        reg &= ~0x08000000;
    }
    reg &= ~(SI_COMCSR_TCINT | SI_COMCSR_TSTART);
    __SIRegs[13] = reg;
    OSRestoreInterrupts(enabled);
    return rc;
}
