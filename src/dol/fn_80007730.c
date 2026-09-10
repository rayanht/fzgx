#include "types.h"

extern u32 fn_800079C4(u32);
extern u32 fn_80007A00(u32);
extern u8 *fn_800079A0(u32);

u32 fn_80007730(u32 arg0) {
    u32 values[2];
    u32 i;
    u8 *p;
    u32 j;
    u8 *entry;

    values[0] = fn_800079C4(arg0);
    values[1] = fn_80007A00(arg0);
    for (i = 0; i < 2; i++) {
        entry = fn_800079A0(values[i]);
        p = entry;
        for (j = 0; j < 8; j++) {
            if (((p[0] >> 7) & 1) == 0) {
                entry[j * 8 + 3] = (entry[j * 8 + 3] & ~0x40) | ((i << 6) & 0x40);
                return (u32)(entry + j * 8);
            }
            p += 8;
        }
    }
    return 0;
}
