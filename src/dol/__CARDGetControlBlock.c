#include <dolphin/card/CARDPriv.h>

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

extern CARDControl lbl_80177960[2];

s32 __CARDGetControlBlock(s32 chan, CARDControl **pcard) {
    BOOL enabled;
    s32 result;
    CARDControl *card;
    card = &lbl_80177960[chan];
    if (chan < 0 || chan >= 2 || card->diskID == ((void *)0)) {
        return -128;
    }
    enabled = OSDisableInterrupts();
    if (!card->attached) {
        result = -3;
    } else if (card->result == -1) {
        result = -1;
    } else {
        card->result = -1;
        result = 0;
        card->apiCallback = 0;
        *pcard = card;
    }
    OSRestoreInterrupts(enabled);
    return result;
}
