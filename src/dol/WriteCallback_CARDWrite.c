#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDWrite.h"
#include "sdk_addresses.h"

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

extern CARDControl lbl_80177960[2];

void WriteCallback_CARDWrite(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    u16 *fat;
    CARDDir *dir;
    CARDDir *ent;
    CARDFileInfo *fileInfo;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    fileInfo = card->fileInfo;
    if (fileInfo->length < 0) {
        result = -14;
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    fileInfo->length -= card->sectorSize;
    if (fileInfo->length <= 0) {
        dir = fn_8002C4BC(card);
        ent = &dir[fileInfo->fileNo];
        ent->time = (u32)((OSGetTime()) / ((u32)__OSBusClock / 4));
        callback = card->apiCallback;
        card->apiCallback = 0;
        result = __CARDUpdateDir(chan, callback);
    } else {
        fat = fn_8002C0B8(card);
        fileInfo->offset += card->sectorSize;
        fileInfo->iBlock = fat[fileInfo->iBlock];
        if (!(5 <= (fileInfo->iBlock) && (fileInfo->iBlock) < (card)->cBlock)) {
            result = -6;
            goto error; // fzgx-allow: S1 SDK error cleanup path
        }
        result = __CARDEraseSector(chan, card->sectorSize * (u32)fileInfo->iBlock,
                                   EraseCallback_CARDWrite);
    }
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    return;
error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}