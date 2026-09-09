#include "types.h"
#include "dolphin/sdk/tww/card/CARDOpen.h"

extern DVDDiskID lbl_80177B80;

static inline BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName) {
    char *entName = (char *)ent->fileName;
    char c1;
    char c2;
    int n = 32;
    while (--n >= 0) {
        if ((c1 = *entName++) != (c2 = *fileName++))
            return 0;
        else if (c2 == '\0')
            return 1;
    }
    if (*fileName == '\0')
        return 1;
    return 0;
}

static inline s32 __CARDAccess(CARDControl *card, CARDDir *ent) {
    if (ent->gameName[0] == 0xFF)
        return -4;
    if (card->diskID == &lbl_80177B80 ||
        (fn_8008023C(ent->gameName, card->diskID->game_name, sizeof(ent->gameName)) == 0 &&
         fn_8008023C(ent->company, card->diskID->company, sizeof(ent->company)) == 0))
        return 0;
    return -10;
}

s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo) {
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