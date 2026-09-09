#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBios.h"

extern CARDControl lbl_80177960[2];

s32 __CARDReadSegment(s32 chan, CARDCallback callback) {
    CARDControl *card;
    s32 result;
    card = &lbl_80177960[chan];
    card->cmd[0] = 0x52;
    card->cmd[1] = ((u8)(((card->addr) >> 17) & 0x7f));
    card->cmd[2] = ((u8)(((card->addr) >> 9) & 0xff));
    card->cmd[3] = ((u8)(((card->addr) >> 7) & 0x03));
    card->cmd[4] = ((u8)((card->addr) & 0x7f));
    card->cmdlen = 5;
    card->mode = 0;
    card->retry = 0;
    result = __CARDStart(chan, callback, 0);
    if (result == -1) {
        result = 0;
    } else if (result >= 0) {
        if (!EXIImmEx(chan, card->cmd, card->cmdlen, 1) ||
            !EXIImmEx(chan, (u8 *)card->workArea + sizeof(CARDID), card->latency, 1) ||
            !EXIDma(chan, card->buffer, 512, card->mode, __CARDTxHandler)) {
            card->txCallback = 0;
            EXIDeselect(chan);
            EXIUnlock(chan);
            result = -3;
        } else {
            result = 0;
        }
    }
    return result;
}