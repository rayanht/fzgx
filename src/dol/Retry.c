#include <dolphin/card/CARDPriv.h>

void OSCancelAlarm(OSAlarm *alarm);

s32 Retry(s32 chan);

void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);

void TimeoutHandler(OSAlarm *alarm, OSContext *context);

#include "sdk_addresses.h"

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

extern CARDControl lbl_80177960[2];

static inline void SetupTimeoutAlarm(CARDControl *card) {
    OSCancelAlarm(&card->alarm);
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

s32 Retry(s32 chan) {
    CARDControl *card;
    card = &lbl_80177960[chan];
    if (!EXISelect(chan, 0, 4)) {
        EXIUnlock(chan);
        return -3;
    }
    SetupTimeoutAlarm(card);
    if (!EXIImmEx(chan, card->cmd, card->cmdlen, 1)) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return -3;
    }
    if (card->cmd[0] == 0x52 &&
        !EXIImmEx(chan, (u8 *)card->workArea + sizeof(CARDID), card->latency, 1)) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return -3;
    }
    if (card->mode == 0xffffffff) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return 0;
    }
    if (!EXIDma(chan, card->buffer, (s32)((card->cmd[0] == 0x52) ? 512 : 128), card->mode,
                __CARDTxHandler)) {
        EXIDeselect(chan);
        EXIUnlock(chan);
        return -3;
    }
    return 0;
}
