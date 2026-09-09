#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDCreate.h"

s32 CARDCreateAsync(s32 chan, const char *fileName, u32 size, CARDFileInfo *fileInfo,
                    CARDCallback callback) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    u16 fileNo;
    u16 freeNo;
    u16 *fat;
    if (strlen(fileName) > (u32)32) {
        return -12;
    }
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }
    if (size <= 0 || (size % card->sectorSize) != 0) {
        return -128;
    }
    freeNo = (u16)-1;
    dir = fn_8002C4BC(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        ent = &dir[fileNo];
        if (ent->gameName[0] == 0xff) {
            if (freeNo == (u16)-1) {
                freeNo = fileNo;
            }
        } else if (fn_8008023C(ent->gameName, card->diskID->gameName, sizeof(ent->gameName)) == 0 &&
                   fn_8008023C(ent->company, card->diskID->company, sizeof(ent->company)) == 0 &&
                   __CARDCompareFileName(ent, fileName)) {
            return __CARDPutControlBlock(card, -7);
        }
    }
    if (freeNo == (u16)-1) {
        return __CARDPutControlBlock(card, -8);
    }
    fat = fn_8002C0B8(card);
    if (card->sectorSize * fat[0x0003u] < size) {
        return __CARDPutControlBlock(card, -9);
    }
    card->apiCallback = callback ? callback : fn_80029824;
    card->freeNo = freeNo;
    ent = &dir[freeNo];
    ent->length = (u16)(size / card->sectorSize);
    strncpy(ent->fileName, fileName, 32);
    card->fileInfo = fileInfo;
    fileInfo->chan = chan;
    fileInfo->fileNo = freeNo;
    result = __CARDAllocBlock(chan, size / card->sectorSize, CreateCallbackFat);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }
    return result;
}