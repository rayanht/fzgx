#include <dolphin/card/CARDPriv.h>

void BlockReadCallback(s32 chan, s32 result);

void BlockWriteCallback(s32 chan, s32 result);

extern CARDControl lbl_80177960[2];

void BlockReadCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    card->xferred += 512u;
    card->addr += 512u;
    (u8 *)card->buffer += 512u;
    if (--card->repeat <= 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    result = __CARDReadSegment(chan, BlockReadCallback);
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    return;
error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}

s32 __CARDRead(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback) {
    CARDControl *card;
    card = &lbl_80177960[chan];
    if (!card->attached) {
        return -3;
    }
    card->xferCallback = callback;
    card->repeat = (int)(length / 512u);
    card->addr = addr;
    card->buffer = dst;
    return __CARDReadSegment(chan, BlockReadCallback);
}

void BlockWriteCallback(s32 chan, s32 result) {
    CARDControl *card;
    CARDCallback callback;
    card = &lbl_80177960[chan];
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    card->xferred += 128u;
    card->addr += 128u;
    (u8 *)card->buffer += 128u;
    if (--card->repeat <= 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    result = __CARDWritePage(chan, BlockWriteCallback);
    if (result < 0) {
        goto error; // fzgx-allow: S1 SDK error cleanup path
    }
    return;
error:
    if (card->apiCallback == 0) {
        __CARDPutControlBlock(card, result);
    }
    callback = card->xferCallback;
    if (callback) {
        card->xferCallback = 0;
        callback(chan, result);
    }
}

s32 __CARDWrite(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback) {
    CARDControl *card;
    card = &lbl_80177960[chan];
    if (!card->attached) {
        return -3;
    }
    card->xferCallback = callback;
    card->repeat = (int)(length / 128u);
    card->addr = addr;
    card->buffer = dst;
    return __CARDWritePage(chan, BlockWriteCallback);
}
