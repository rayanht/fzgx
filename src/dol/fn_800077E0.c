#include "types.h"

extern u32 fn_80007654(u32);
extern u32 fn_800079A0(u32);
extern u32 fn_800079C4(u32);
extern u32 fn_80007A00(u32);

u32 fn_800077E0(u32 key) {
    u32 tab[2];
    u32 h;
    u32 hi;
    u32 i;
    u8 *base;
    u8 *p;
    u32 j;

    h = fn_80007654(key);
    hi = (key >> 22) & 0x3F;
    tab[0] = fn_800079C4(key);
    tab[1] = fn_80007A00(key);
    for (i = 0; i < 2; i++) {
        base = (u8 *)fn_800079A0(tab[i]);
        p = base;
        for (j = 0; j < 8; j++) {
            if (((p[0] >> 7) & 1) && i == ((p[3] >> 6) & 1) && hi == (p[3] & 0x3F) && h == ((*(u32 *)p >> 7) & 0xFFFFFF)) {
                return (u32)(base + j * 8);
            }
            p += 8;
        }
    }
    return 0;
}
