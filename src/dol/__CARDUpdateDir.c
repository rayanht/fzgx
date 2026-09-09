#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDDir.h"

extern CARDControl lbl_80177960[2];

static inline CARDDir *__CARDGetDirBlock(CARDControl *card) { return card->currentDir; }

s32 __CARDUpdateDir(s32 chan, CARDCallback callback) {
    CARDControl *card;
    CARDDirCheck *check;
    u32 tmp[2];
    u32 addr;
    CARDDir *dir;
    card = &lbl_80177960[chan];
    if (!card->attached) {
        return -3;
    }
    dir = __CARDGetDirBlock(card);
    check = ((CARDDirCheck *)&(dir)[127]);
    ++check->checkCode;
    __CARDCheckSum(dir, 0x2000 - sizeof(u32), &check->checkSum, &check->checkSumInv);
    DCStoreRange(dir, 0x2000);
    card->eraseCallback = callback;
    addr = ((u32)dir - (u32)card->workArea) / 0x2000 * card->sectorSize;
    return __CARDEraseSector(chan, addr, EraseCallback_CARDDir);
}