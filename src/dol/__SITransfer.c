#include <dolphin/si/SIPriv.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/si.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef struct SIComm_s {
    u32 tcint : 1;
    u32 tcintmsk : 1;
    u32 comerr : 1;
    u32 rdstint : 1;
    u32 rdstintmsk : 1;
    u32 pad0 : 4;
    u32 outlngth : 7;
    u32 pad1 : 1;
    u32 inlngth : 7;
    u32 pad2 : 5;
    u32 channel : 2;
    u32 tstart : 1;
} SIComm_s;

typedef union SIComm_u {
    u32 val;
    SIComm_s f;
} SIComm_u;

struct SIBiosData {
    unsigned char padding_0[68];
    SIControl Si;
    u32 Type[4];
};

vu32 __SIRegs[64] : FZGX_ADDR___SIRegs;

extern struct SIBiosData lbl_80123B50;

BOOL __SITransfer(s32 chan, void *output, u32 outputBytes, void *input, u32 inputBytes,
                  SICallback callback) {
    struct SIBiosData *data = &lbl_80123B50;

    BOOL enabled;
    u32 rLen;
    u32 i;
    u32 sr;
    SIComm_u comcsr;
    enabled = OSDisableInterrupts();
    if ((data->Si).chan != -1) {
        OSRestoreInterrupts(enabled);
        return 0;
    }
    sr = __SIRegs[14];
    sr &= (0xf000000) >> (8 * chan);
    __SIRegs[14] = sr;
    (data->Si).chan = chan;
    (data->Si).callback = callback;
    (data->Si).inputBytes = inputBytes;
    (data->Si).input = input;
    rLen = (((u32)(outputBytes) + (4) - 1) & ~((4) - 1)) / 4;
    for (i = 0; i < rLen; i++) {
        __SIRegs[32 + i] = ((u32 *)output)[i];
    }
    comcsr.val = __SIRegs[13];
    comcsr.f.tcint = 1;
    comcsr.f.tcintmsk = callback ? 1 : 0;
    comcsr.f.outlngth = (outputBytes == 128) ? 0 : outputBytes;
    comcsr.f.inlngth = (inputBytes == 128) ? 0 : inputBytes;
    comcsr.f.channel = chan;
    comcsr.f.tstart = 1;
    __SIRegs[13] = comcsr.val;
    OSRestoreInterrupts(enabled);
    return 1;
}
