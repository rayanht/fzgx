#include "types.h"

extern u32 lbl_8015ACBC[21];
extern u32 lbl_8015AC68[21];

u32 fn_80072404(u32 mask, s32 select) {
    u32 *a = lbl_8015ACBC;
    u32 *b = lbl_8015AC68;
    u32 total = 0;
    int i;

    for (i = 0; i < 17; i++) {
        if (mask & 1) {
            if (select != 0) {
                total += *a;
            } else {
                total += *b;
            }
        }
        mask >>= 1;
        a = a + 1;
        b++;
    }
    return total;
}
