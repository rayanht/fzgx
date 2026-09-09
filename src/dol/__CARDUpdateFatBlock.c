#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDBlock.h"

extern CARDControl lbl_80177960[2];

s32 __CARDUpdateFatBlock(s32 chan, u16 *fat, CARDCallback callback) {
    CARDControl *card;
    card = &lbl_80177960[chan];
    ++fat[2];
    __CARDCheckSum(fat + 2, 0x1FFC, fat, fat + 1);
    DCStoreRange(fat, 0x2000);
    card->eraseCallback = callback;
    return __CARDEraseSector(chan, (((u32)fat - (u32)card->workArea) / 8192u) * card->sectorSize,
                             EraseCallback);
}