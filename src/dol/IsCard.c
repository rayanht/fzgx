#include <dolphin/card/CARDPriv.h>

extern u16 lbl_801A6518;

extern u32 lbl_8012ABC0[8];

BOOL IsCard(u32 id) {
    u32 size;
    s32 sectorSize;
    if (id & (0xFFFF0000) && (id != 0x80000004 || lbl_801A6518 == 0xFFFF)) { // fzgx-allow: A1 CARD device identifier, not a pointer
        return 0;
    }
    if ((id & 3) != 0) {
        return 0;
    }
    size = id & 0xfc;
    switch (size) {
    case 4:
    case 8:
    case 16:
    case 32:
    case 64:
    case 128:
        break;
    default:
        return 0;
        break;
    }
    sectorSize = lbl_8012ABC0[(id & 0x00003800) >> 11];
    if (sectorSize == 0) {
        return 0;
    }
    if ((size * 1024 * 1024 / 8) / sectorSize < 8) {
        return 0;
    }
    return 1;
}
