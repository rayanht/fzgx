#include <dolphin/card/CARDPriv.h>

void FormatCallback(s32 chan, s32 result);

extern CARDControl lbl_80177960[2];

void FormatCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    ++card->formatStep;
    if (card->formatStep < 5) {
        result = __CARDEraseSector(chan, (u32)card->sectorSize * card->formatStep, FormatCallback);
        if (0 <= result) {
            return;
        }
    } else if (card->formatStep < 2 * 5) {
        int step = card->formatStep - 5;
        result = __CARDWrite(chan, (u32)card->sectorSize * step, (8 * 1024),
                             (u8 *)card->workArea + ((8 * 1024) * step), FormatCallback);
        if (result >= 0) {
            return;
        }
    } else {
        card->currentDir = (CARDDir *)((u8 *)card->workArea + (1 + 0) * (8 * 1024));
        memcpy(card->currentDir, (u8 *)card->workArea + (1 + 1) * (8 * 1024), (8 * 1024));
        card->currentFat = (u16 *)((u8 *)card->workArea + (3 + 0) * (8 * 1024));
        memcpy(card->currentFat, (u8 *)card->workArea + (3 + 1) * (8 * 1024), (8 * 1024));
    }
error:
    callback = card->apiCallback;
    card->apiCallback = 0;
    __CARDPutControlBlock(card, result);
    callback(chan, result);
}
