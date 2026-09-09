#include "types.h"

typedef struct FnState {
    u8 *cursor;
    s32 state;
} FnState;

u32 fn_800829EC(FnState *ctx, u32 value, s32 mode) {
    FnState *p = ctx;

    switch (mode) {
    case 0: {
        s32 c = *p->cursor;
        if ((s8)c == 0) {
            p->state = 1;
            return (u32)-1;
        }
        p->cursor++;
        return c;
    }
    case 1:
        if (p->state == 0) {
            p->cursor--;
        } else {
            p->state = 0;
        }
        return value;
    case 2:
        return p->state;
    default:
        return 0;
    }
}
