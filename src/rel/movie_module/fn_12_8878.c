#include "types.h"

static inline void decode8(u8 *dst, const s16 *source, const u8 *table) {
    dst[0] = table[source[0]];
    dst[1] = table[source[1]];
    dst[2] = table[source[2]];
    dst[3] = table[source[3]];
    dst[4] = table[source[4]];
    dst[5] = table[source[5]];
    dst[6] = table[source[6]];
    dst[7] = table[source[7]];
}

void fn_12_8878(s16 *source, f64 *output, u32 *entries, const u8 *table) {
    u32 *p;
    s32 groups;
    u8 *base;
    s32 stride;
    u8 *dst;
    s32 rows;
    s32 i;

    p = entries + 1;
    for (groups = 6; groups > 0; groups--) {
        dst = (u8 *)p[0];
        stride = (s32)p[1];
        p += 2;
        base = dst;
        for (rows = 8; rows != 0; rows--) {
            decode8(dst, source, table);
            dst += stride;
            source += 8;
        }
        stride &= ~7;
        for (rows = 0; rows < 8; rows++) {
            *output++ = *(f64 *)base;
            base += stride;
        }
    }
}
