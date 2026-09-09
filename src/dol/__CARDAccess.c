#include "types.h"
#include "dolphin/sdk/tww/card/CARDOpen.h"

extern DVDDiskID lbl_80177B80;

s32 __CARDAccess(CARDControl *card, CARDDir *ent) {
    if (ent->gameName[0] == 0xFF)
        return -4;
    if (card->diskID == &lbl_80177B80 ||
        (fn_8008023C(ent->gameName, card->diskID->game_name, sizeof(ent->gameName)) == 0 &&
         fn_8008023C(ent->company, card->diskID->company, sizeof(ent->company)) == 0))
        return 0;
    return -10;
}