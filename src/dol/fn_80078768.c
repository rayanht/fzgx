#include "types.h"

typedef struct {
    u8 pad_00[0x1a];
    u16 count_a;
    u16 count_b;
} Fn80078768Arg0;

typedef struct {
    u8 pad_00[0xc];
    u32 offset;
    u8 pad_10[0xa];
    u16 count_a;
    u16 count_b;
    u8 pad_20[0x4];
} Fn80078768Data;

extern void GXInvalidateVtxCache(void);
extern u8 *fn_80078360(u8 *, u8 *, Fn80078768Data *, u8 *, Fn80078768Arg0 *);

void fn_80078768(Fn80078768Arg0 *arg0, Fn80078768Data *arg1, u8 *arg2, s32 arg3) {
    u8 *entry;
    u8 *result;
    s32 i;

    result = (u8 *)arg1 + arg1->offset;
    entry = (u8 *)arg1 + 0x20;
    GXInvalidateVtxCache();
    if (arg3 != 0) {
        for (i = 0; i < arg0->count_a; i++) {
            result = fn_80078360(entry, arg2, arg1, result, arg0);
            entry += 0x60;
        }
        return;
    }
    for (i = 0; i < arg0->count_a; i++)
        entry += 0x60;
    for (i = 0; i < arg0->count_b; i++) {
        result = fn_80078360(entry, arg2, arg1, result, arg0);
        entry += 0x60;
    }
}
