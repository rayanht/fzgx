#include <dolphin/card/CARDPriv.h>

extern CARDControl lbl_80177960[2];

s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback) {
    CARDControl *card;
    s32 result;
    card = &lbl_80177960[chan];
    card->cmd[0] = 0xF1;
    card->cmd[1] = ((u8)(((addr) >> 17) & 0x7f));
    card->cmd[2] = ((u8)(((addr) >> 9) & 0xff));
    card->cmdlen = 3;
    card->mode = -1;
    card->retry = 3;
    result = __CARDStart(chan, 0, callback);
    if (result == -1) {
        result = 0;
    } else if (result >= 0) {
        if (!EXIImmEx(chan, card->cmd, card->cmdlen, 1)) {
            card->exiCallback = ((void *)0);
            result = -3;
        } else {
            result = 0;
        }
        EXIDeselect(chan);
        EXIUnlock(chan);
    }
    return result;
}
