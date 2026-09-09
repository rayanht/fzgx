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

u32 SIGetStatus(s32 chan);

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern struct SIBiosBss Packet_8015CA10;

static inline BOOL SIGetResponseRaw(s32 chan) {
    struct SIBiosBss *bss = &Packet_8015CA10;

    u32 sr;
    sr = SIGetStatus(chan);
    if (sr & 0x0020) {
        (bss->InputBuffer)[chan][0] = __SIRegs[3 * chan + 1];
        (bss->InputBuffer)[chan][1] = __SIRegs[3 * chan + 2];
        (bss->InputBufferValid)[chan] = 1;
        return 1;
    }
    return 0;
}

BOOL SIGetResponse(s32 chan, void *data) {
    struct SIBiosBss *bss = &Packet_8015CA10;

    BOOL rc;
    BOOL enabled;
    enabled = OSDisableInterrupts();
    SIGetResponseRaw(chan);
    rc = (bss->InputBufferValid)[chan];
    (bss->InputBufferValid)[chan] = 0;
    if (rc) {
        ((u32 *)data)[0] = (bss->InputBuffer)[chan][0];
        ((u32 *)data)[1] = (bss->InputBuffer)[chan][1];
    }
    OSRestoreInterrupts(enabled);
    return rc;
}
