#include "types.h"

extern u8 lbl_8019E140[16];
extern u32 lbl_801A6CF0;
extern char lbl_8015AA78[11];
extern u8 lbl_8015AA84[160];
extern void OSPanic(const char *, int, const char *, ...);

s32 fn_800702E4(u32 arg0) {
    s32 k;
    s32 i;
    s32 j;
    u32 n;
    u32 result;

    result = 0;
    for (i = 0; i < 16; i++) {
        if (lbl_8019E140[i] == 0) {
            n = arg0 - 1;
            j = i + 1;
            while (n != 0 && j < 16) {
                if (lbl_8019E140[j] != 0) {
                    break;
                }
                n--;
                j++;
            }
            if (n == 0) {
                result = lbl_801A6CF0 + (i << 10);
                for (k = 0; k < arg0; k++) {
                    lbl_8019E140[i + k] = arg0 - k;
                }
                break;
            }
        }
    }
    if (result == 0) {
        OSPanic(lbl_8015AA78, 158, (const char *)lbl_8015AA84);
    }
    return result;
}
