#include "types.h"

int fn_80083BCC(const char *s1, const char *s2) {
    const u8 *left = (const u8 *)s1;
    const u8 *right = (const u8 *)s2;
    u32 align;
    u32 n;
    u32 lb = *left;
    u32 rb = *right;
    u32 lw;
    u32 rw;
    s32 diff = (s32)(lb - rb);

    if (diff != 0)
        return diff;

    if (((u32)right & 3) != (align = (u32)left & 3))
        goto byte_loop; /* Keep the verified branch to byte_loop. */

    if (align != 0) {
        if (lb == 0)
            return 0;
        for (n = 3 - align; n != 0; --n) {
            lb = *++left;
            rb = *++right;
            diff = (s32)(lb - rb);
            if (diff != 0)
                return diff;
            if (lb == 0)
                return 0;
        }
        ++left;
        ++right;
    }

    lw = *(const u32 *)left;
    rw = *(const u32 *)right;
    if (((lw - 0x01010101U) & 0x80808080U) != 0)
        goto byte_cmp; /* Keep the verified branch to byte_cmp. */

    /* Word loop: equality is tested at the bottom; a zero byte found in the
       advanced word jumps out to the byte comparison. */
    while (lw == rw) {
        lw = *(const u32 *)(left += 4);
        rw = *(const u32 *)(right += 4);
        if (((lw - 0x01010101U) & 0x80808080U) != 0)
            goto byte_cmp; /* Keep the verified branch to byte_cmp. */
    }
    return lw > rw ? 1 : -1;

byte_cmp:
    lb = *left;
    rb = *right;
    diff = (s32)(lb - rb);
    if (diff != 0)
        return diff;

byte_loop:
    if (lb == 0)
        return 0;
    do {
        lb = *++left;
        diff = (s32)(lb - *++right);
        if (diff != 0)
            return diff;
    } while (lb != 0);
    return 0;
}
