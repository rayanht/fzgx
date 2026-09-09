#include <dolphin/card/CARDPriv.h>

CARDDir *fn_8002C4BC(CARDControl *card);
u16 *fn_8002C0B8(CARDControl *card);

s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard) {
    CARDControl *card;
    CARDDir *dir;
    CARDDir *ent;
    s32 result;
    u16 *fat;
    result = __CARDGetControlBlock(fileInfo->chan, &card);
    if (result < 0) {
        return result;
    }
    if (!(5 <= (fileInfo->iBlock) && (fileInfo->iBlock) < (card)->cBlock) ||
        card->cBlock * card->sectorSize <= fileInfo->offset) {
        return __CARDPutControlBlock(card, -128);
    }
    dir = fn_8002C4BC(card);
    ent = &dir[fileInfo->fileNo];
    if (ent->length * card->sectorSize <= offset ||
        ent->length * card->sectorSize < offset + length) {
        return __CARDPutControlBlock(card, -11);
    }
    card->fileInfo = fileInfo;
    fileInfo->length = length;
    if (offset < fileInfo->offset) {
        fileInfo->offset = 0;
        fileInfo->iBlock = ent->startBlock;
        if (!(5 <= (fileInfo->iBlock) && (fileInfo->iBlock) < (card)->cBlock)) {
            return __CARDPutControlBlock(card, -6);
        }
    }
    fat = fn_8002C0B8(card);
    while (fileInfo->offset < (((u32)(offset)) & ~((card->sectorSize) - 1))) {
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!(5 <= (fileInfo->iBlock) && (fileInfo->iBlock) < (card)->cBlock)) {
            return __CARDPutControlBlock(card, -6);
        }
    }
    fileInfo->offset = offset;
    *pcard = card;
    return 0;
}
