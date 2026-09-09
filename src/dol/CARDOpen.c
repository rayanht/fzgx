#include "types.h"
#include "dolphin/sdk/tww/card/CARDOpen.h"

extern DVDDiskID lbl_80177B80;

static inline s32 __CARDAccess(CARDControl *card, CARDDir *ent) {
    if (ent->gameName[0] == 0xFF)
        return -4;
    if (card->diskID == &lbl_80177B80 ||
        (fn_8008023C(ent->gameName, card->diskID->game_name, sizeof(ent->gameName)) == 0 &&
         fn_8008023C(ent->company, card->diskID->company, sizeof(ent->company)) == 0))
        return 0;
    return -10;
}

static inline s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo) {
    CARDDir *dir;
    CARDDir *ent;
    s32 fileNo;
    s32 result;
    if (!card->attached)
        return -3;
    dir = fn_8002C4BC(card);
    for (fileNo = 0; fileNo < 127; fileNo++) {
        ent = &dir[fileNo];
        result = __CARDAccess(card, ent);
        if (result < 0)
            continue;
        if (__CARDCompareFileName(ent, fileName)) {
            *pfileNo = fileNo;
            return 0;
        }
    }
    return -4;
}

s32 CARDOpen(s32 chan, const char *fileName, CARDFileInfo *fileInfo) {
    CARDControl *card;
    s32 fileNo;
    s32 result;
    CARDDir *dir;
    CARDDir *ent;
    (void)0;
    fileInfo->chan = -1;
    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;
    result = __CARDGetFileNo(card, fileName, &fileNo);
    if (result >= 0) {
        dir = fn_8002C4BC(card);
        ent = &dir[fileNo];
        if (!((ent->startBlock) >= 5 && (ent->startBlock) < (card)->cBlock))
            result = -6;
        else {
            fileInfo->chan = chan;
            fileInfo->fileNo = fileNo;
            fileInfo->offset = 0;
            fileInfo->iBlock = ent->startBlock;
        }
    }
    return __CARDPutControlBlock(card, result);
}