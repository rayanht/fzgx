#include "types.h"

extern void *fn_12_3310C(const void *, u32);
extern int fn_12_32EAC(void *, s32 *);
extern void fn_12_330E0(void *);
extern int fn_12_321E8(void *, s32 *);

void fn_12_336CC(const void *data, u32 size, void *out) {
    s32 value;
    s32 result;
    void *movie;
    s32 output;
    int i;

    *(s32 *)((u8 *)out + 0x1c) = -1;
    if (size < 0x800 || data == 0) {
        return;
    }
    for (i = 2; i <= 3; i++) {
        movie = fn_12_3310C((const u8 *)data + (i - 1) * 0x800,
                            size - (i - 1) * 0x800);
        if (movie == 0) {
            continue;
        }
        if (fn_12_32EAC(movie, &value) == 0 || value == 0) {
            fn_12_330E0(movie);
            continue;
        }
        if (fn_12_321E8(movie, &result) == 0) {
            output = -1;
        } else {
            output = result;
        }
        *(s32 *)((u8 *)out + 0x1c) = output;
        fn_12_330E0(movie);
        return;
    }
}
