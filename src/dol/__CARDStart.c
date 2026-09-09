#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBios.h"
#include "sdk_addresses.h"

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

extern CARDControl lbl_80177960[2];

static inline void SetupTimeoutAlarm(CARDControl *card) {
    fn_8000AF78(&card->alarm);
    switch (card->cmd[0]) {
    case 0xF2:
        OSSetAlarm(&card->alarm, ((100) * (((u32)__OSBusClock / 4) / 1000)), TimeoutHandler);
        break;
    case 0xF3:
        break;
    case 0xF4:
    case 0xF1:
        OSSetAlarm(&card->alarm,
                   (((OSTime)2) * ((u32)__OSBusClock / 4)) * (card->sectorSize / 0x2000),
                   TimeoutHandler);
        break;
    }
}

s32 __CARDStart(s32 chan, CARDCallback txCallback, CARDCallback exiCallback) {
    BOOL enabled;
    CARDControl *card;
    s32 result;
    enabled = OSDisableInterrupts();
    card = &lbl_80177960[chan];
    if (!card->attached) {
        result = -3;
    } else {
        if (txCallback) {
            card->txCallback = txCallback;
        }
        if (exiCallback) {
            card->exiCallback = exiCallback;
        }
        card->unlockCallback = UnlockedCallback;
        if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
            result = -1;
        } else {
            card->unlockCallback = 0;
            if (!EXISelect(chan, 0, 4)) {
                EXIUnlock(chan);
                result = -3;
            } else {
                SetupTimeoutAlarm(card);
                result = 0;
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return result;
}