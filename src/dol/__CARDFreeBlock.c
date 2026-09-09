#include <dolphin/card/CARDPriv.h>

extern CARDControl lbl_80177960[2];

static inline u16 *__CARDGetFatBlock(CARDControl *card) { return card->currentFat; }

s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback) {
    CARDControl *card;
    u16 *fat;
    u16 nextBlock;
    card = card = &lbl_80177960[chan];
    if (!card->attached) {
        return -3;
    }
    fat = __CARDGetFatBlock(card);
    while (nBlock != 0xFFFF) {
        if (!(5 <= (nBlock) && (nBlock) < (card)->cBlock)) {
            return -6;
        }
        nextBlock = fat[nBlock];
        fat[nBlock] = 0;
        nBlock = nextBlock;
        ++fat[3];
    }
    return __CARDUpdateFatBlock(chan, fat, callback);
}
