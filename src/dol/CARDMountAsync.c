#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDMount.h"
#include "sdk_addresses.h"

extern CARDControl lbl_80177960[2];

u8 GameChoice : FZGX_ADDR_GameChoice;

s32 CARDMountAsync(s32 chan, void *workArea, CARDCallback detachCallback,
                   CARDCallback attachCallback) {
    CARDControl *card;
    BOOL enabled;
    if (chan < 0 || 2 <= chan) {
        return -128;
    }
    if (GameChoice & 0x80) {
        return -3;
    }
    card = &lbl_80177960[chan];
    enabled = OSDisableInterrupts();
    if (card->result == -1) {
        OSRestoreInterrupts(enabled);
        return -1;
    }
    if (!card->attached && (EXIGetState(chan) & 0x08)) {
        OSRestoreInterrupts(enabled);
        return -2;
    }
    card->result = -1;
    card->workArea = workArea;
    card->extCallback = detachCallback;
    card->apiCallback = attachCallback ? attachCallback : fn_80029824;
    card->exiCallback = 0;
    if (!card->attached && !EXIAttach(chan, __CARDExtHandler)) {
        card->result = -3;
        OSRestoreInterrupts(enabled);
        return -3;
    }
    card->mountStep = 0;
    card->attached = 1;
    EXISetExiCallback(chan, 0);
    fn_8000AF78(&card->alarm);
    card->currentDir = 0;
    card->currentFat = 0;
    OSRestoreInterrupts(enabled);
    card->unlockCallback = __CARDMountCallback;
    if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
        return 0;
    }
    card->unlockCallback = 0;
    return fn_8002D8F8(chan);
}