#include <dolphin/card/CARDPriv.h>

extern CARDControl lbl_80177960[2];

static inline u16 *__CARDGetFatBlock(CARDControl *card) { return card->currentFat; }

s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback) {
    CARDControl *card;
    u16 *fat;
    u16 iBlock;
    u16 startBlock;
    u16 prevBlock;
    u16 count;
    card = &lbl_80177960[chan];
    if (!card->attached) {
        return -3;
    }
    fat = __CARDGetFatBlock(card);
    if (fat[3] < cBlock) {
        return -9;
    }
    fat[3] -= cBlock;
    startBlock = 0xFFFF;
    iBlock = fat[4];
    count = 0;
    while (0 < cBlock) {
        if (card->cBlock - 5 < ++count) {
            return -6;
        }
        iBlock++;
        if (!(5 <= (iBlock) && (iBlock) < (card)->cBlock)) {
            iBlock = 5;
        }
        if (fat[iBlock] == 0x0000u) {
            if (startBlock == 0xFFFF) {
                startBlock = iBlock;
            } else {
                fat[prevBlock] = iBlock;
            }
            prevBlock = iBlock;
            fat[iBlock] = 0xFFFF;
            --cBlock;
        }
    }
    fat[4] = iBlock;
    card->startBlock = startBlock;
    return __CARDUpdateFatBlock(chan, fat, callback);
}
