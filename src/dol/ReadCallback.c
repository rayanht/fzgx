#include "types.h"
#include "dolphin/sdk/mkdd/card/CARDRead.h"

extern CARDControl lbl_80177960[2];

void ReadCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    u16 *fat;
    CARDFileInfo *fileInfo;
    s32 length;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    fileInfo = card->fileInfo;
    if (fileInfo->length < 0) {
        result = -14;
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    length = (s32)(((u32)(fileInfo->offset + card->sectorSize)) & ~((card->sectorSize) - 1)) -
             fileInfo->offset;
    fileInfo->length -= length;
    if (fileInfo->length <= 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    fat = fn_8002C0B8(card);
    fileInfo->offset += length;
    fileInfo->iBlock = fat[fileInfo->iBlock];
    if (!(5 <= (fileInfo->iBlock) && (fileInfo->iBlock) < (card)->cBlock)) {
        result = -6;
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    result = __CARDRead(chan, card->sectorSize * (u32)fileInfo->iBlock,
                        (fileInfo->length < card->sectorSize) ? fileInfo->length : card->sectorSize,
                        card->buffer, ReadCallback);
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