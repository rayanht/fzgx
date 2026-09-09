#include "types.h"

s32 fn_8008023C(u32 arg0, u32 arg1, u32 arg2) {
    u8 *v0;
    u8 *v1;
    u32 v2;

    v0 = (u8 *)arg0 - 1;
    v1 = (u8 *)arg1 - 1;
    v2 = arg2 + 1;
    /* Loop enters at the bottom test in the retail control flow. */
    goto test;
loop:
    if (*++v0 != *++v1) {
        if (*v0 < *v1) {
            return -1;
        }
        return 1;
    }
test:
    if (--v2 != 0) {
        /* Loop back to the body after the retail bottom-test branch. */
        goto loop;
    }
    return 0;
}

