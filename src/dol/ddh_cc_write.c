#include "types.h"

extern s32 lbl_801A6E08[2];
extern void MWTRACE(s32 level, const char *format, ...);
extern s32 fn_8008F29C(u8 *dst, s32 size);

s32 ddh_cc_write(u8 *dst, s32 size) {
    s32 left = size;
    u8 *current = dst;

    if (!lbl_801A6E08[0]) {
        MWTRACE(8, "cc not initialized\n");
        return -10001;
    }

    MWTRACE(8, "cc_write : Output data 0x%08x %ld bytes\n\000\000\000", dst, size);
    while (left > 0) {
        s32 written;

        MWTRACE(1, "cc_write sending %ld bytes\n", left);
        written = fn_8008F29C(current, left);
        if (written == 0) {
            break;
        }
        current += written;
        left -= written;
    }

    return 0;
}
