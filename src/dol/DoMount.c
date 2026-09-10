#include <dolphin/card/CARDPriv.h>
#include <dolphin/exi.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSRtc.h>

s32 EXIGetID(s32 chan, u32 dev, u32 *id);

extern CARDControl lbl_80177960[2];

extern u16 lbl_801A6518;

OSSramEx *__OSLockSramEx();

extern u32 lbl_8012ABC0[8];

extern u32 lbl_8012ABE0[8];

void DoUnmount(s32 chan, s32 result);

BOOL IsCard(u32 id);

void DoUnmount(s32 chan, s32 result);

s32 DoMount(s32 chan) {
    CARDControl *card;
    u32 id;
    u8 status;
    s32 result;
    OSSramEx *sram;
    int i;
    u8 checkSum;
    int step;
    card = &lbl_80177960[chan];
    if (card->mountStep == 0) {
        if (EXIGetID(chan, 0, &id) == 0) {
            result = -3;
        } else if (IsCard(id)) {
            result = 0;
        } else {
            result = -2;
        }
        if (result < 0) {
            goto error; // fzgx-allow: S1 SDK error cleanup path
        }
        card->cid = id;
        card->size = (u16)(id & 0xFC);
        card->sectorSize = lbl_8012ABC0[(id & 0x00003800) >> 11];
        card->cBlock = (u16)((card->size * 1024 * 1024 / 8) / card->sectorSize);
        card->latency = lbl_8012ABE0[(id & 0x00000700) >> 8];
        result = __CARDClearStatus(chan);
        if (result < 0) {
            goto error; // fzgx-allow: S1 SDK error cleanup path
        }
        result = __CARDReadStatus(chan, &status);
        if (result < 0) {
            goto error; // fzgx-allow: S1 SDK error cleanup path
        }
        if (!EXIProbe(chan)) {
            result = -3;
            goto error; // fzgx-allow: S1 SDK error cleanup path
        }
        if (!(status & 0x40)) {
            result = __CARDUnlock(chan, card->id);
            if (result < 0) {
                goto error; // fzgx-allow: S1 SDK error cleanup path
            }
            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++) {
                sram->flashID[chan][i] = card->id[i];
                checkSum += card->id[i];
            }
            sram->flashIDCheckSum[chan] = (u8)~checkSum;
            __OSUnlockSramEx(1);
            return result;
        } else {
            card->mountStep = 1;
            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++) {
                checkSum += sram->flashID[chan][i];
            }
            __OSUnlockSramEx(0);
            if (sram->flashIDCheckSum[chan] != (u8)~checkSum) {
                result = -5;
                goto error; // fzgx-allow: S1 SDK error cleanup path
            }
        }
    }
    if (card->mountStep == 1) {
        if (card->cid == 0x80000004) { // fzgx-allow: A1 CARD device identifier, not a pointer
            u16 vendorID;
            sram = __OSLockSramEx();
            vendorID = *(u16 *)sram->flashID[chan];
            __OSUnlockSramEx(0);
            if (lbl_801A6518 == 0xffff || vendorID != lbl_801A6518) {
                result = -2;
                goto error; // fzgx-allow: S1 SDK error cleanup path
            }
        }
        card->mountStep = 2;
        result = __CARDEnableInterrupt(chan, 1);
        if (result < 0) {
            goto error; // fzgx-allow: S1 SDK error cleanup path
        }
        EXISetExiCallback(chan, __CARDExiHandler);
        EXIUnlock(chan);
        DCInvalidateRange(card->workArea, (5 * 8 * 1024));
    }
    step = card->mountStep - 2;
    result = __CARDRead(chan, (u32)card->sectorSize * step, (8 * 1024),
                        (u8 *)card->workArea + ((8 * 1024) * step), __CARDMountCallback);
    if (result < 0) {
        __CARDPutControlBlock(card, result);
    }
    return result;
error:
    EXIUnlock(chan);
    DoUnmount(chan, result);
    return result;
}
