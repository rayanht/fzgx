#include "types.h"

struct Fn8004E9A8 {
    u8 pad_0[0x10];
    s32 count_10;
    u8 pad_1[0xCA8 - 0x14];
    s32 field_CA8;
    s32 field_CAC;
};

extern struct Fn8004E9A8 lbl_8017E980;

void fn_8004E9A8(void) {
    struct Fn8004E9A8* state = &lbl_8017E980;

    while (state->field_CAC == 1) {
        state->count_10 += 1;
    }
    state->field_CA8 = 1;
}
