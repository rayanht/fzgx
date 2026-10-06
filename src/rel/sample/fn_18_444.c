#include "types.h"

#define N 4096
#define F 18
#define THRESHOLD 2

typedef struct Fn18_444_Args {
    u8 *src;
    u8 *dst;
    void (*callback)(u32 size);
} Fn18_444_Args;

u32 *fn_18_444(Fn18_444_Args *args) {
    u8 c;
    s32 k;
    u32 size;
    s32 r;
    void (*callback)(u32 size);
    u8 *p;
    u8 *dst;
    u8 *out;
    s32 j;
    u8 text_buf[N + F - 1];
    s32 i;
    u32 flags;
    u32 end;
    u8 *src;

    src = args->src;
    callback = args->callback;
    out = args->dst;
    end = __lwbrx(src, 0) + 8;
    size = __lwbrx(src, 4);
    if (end == 0 || size == 0) {
        return NULL;
    }
    p = src + 8;
    dst = out;
    for (i = 0; i < N - F; i++) {
        text_buf[i] = 0;
    }
    r = N - F;
    flags = 0;
    for (;;) {
        if (((flags >>= 1) & 0x100) == 0) {
            if (p - src >= end) {
                break;
            }
            flags = *p++ | 0xFF00;
        }
        if (flags & 1) {
            if (p - src >= end) {
                break;
            }
            c = *p++;
            *dst++ = c;
            text_buf[r++] = c;
            r &= N - 1;
        } else {
            if (p - src >= end) {
                break;
            }
            i = p[0];
            if (p + 1 - src >= end) {
                break;
            }
            j = p[1];
            p += 2;
            i |= (j & 0xF0) << 4;
            j = (j & 0x0F) + THRESHOLD;
            for (k = 0; k <= j; k++) {
                c = text_buf[(i + k) & (N - 1)];
                *dst++ = c;
                text_buf[r++] = c;
                r &= N - 1;
            }
        }
    }
    if (callback != NULL) {
        callback(size);
    }
    return &size;
}
