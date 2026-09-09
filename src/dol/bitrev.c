#include <dolphin/card/CARDPriv.h>

u32 bitrev(u32 data) {
    u32 wk;
    u32 i;
    u32 k = 0;
    u32 j = 1;
    wk = 0;
    for (i = 0; i < 32; i++) {
        if (i > 15) {
            if (i == 31) {
                wk |= (((data & (0x01 << 31)) >> 31) & 0x01);
            } else {
                wk |= ((data & (0x01 << i)) >> j);
                j += 2;
            }
        } else {
            wk |= ((data & (0x01 << i)) << (31 - i - k));
            k++;
        }
    }
    return wk;
}
