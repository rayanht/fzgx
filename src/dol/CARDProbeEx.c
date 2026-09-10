#include <dolphin/card/CARDPriv.h>

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
s32 EXIProbeEx(s32 chan);
s32 EXIGetID(s32 chan, u32 dev, u32 *id);
BOOL IsCard(u32 id);

#include "sdk_addresses.h"

extern CARDControl lbl_80177960[2];

u8 GameChoice : FZGX_ADDR_GameChoice;

extern u32 lbl_8012ABC0[8];

s32 CARDProbeEx(s32 chan, s32 *memSize, s32 *sectorSize) {
    u32 id;
    CARDControl *card;
    BOOL enabled;
    s32 result;
    int probe;
    if (chan < 0 || 2 <= chan) {
        return -128;
    }
    if (GameChoice & 0x80) {
        return -3;
    }
    card = &lbl_80177960[chan];
    enabled = OSDisableInterrupts();
    probe = EXIProbeEx(chan);
    if (probe == -1) {
        result = -3;
    } else if (probe == 0) {
        result = -1;
    } else if (card->attached) {
        if (card->mountStep < 1) {
            result = -1;
        } else {
            if (memSize) {
                *memSize = card->size;
            }
            if (sectorSize) {
                *sectorSize = card->sectorSize;
            }
            result = 0;
        }
    } else if ((EXIGetState(chan) & 8)) {
        result = -2;
    } else if (!EXIGetID(chan, 0, &id)) {
        result = -1;
    } else if (IsCard(id)) {
        if (memSize) {
            *memSize = (s32)(id & 0xfc);
        }
        if (sectorSize) {
            *sectorSize = lbl_8012ABC0[(id & 0x00003800) >> 11];
        }
        result = 0;
    } else {
        result = -2;
    }
    OSRestoreInterrupts(enabled);
    return result;
}
