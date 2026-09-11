#include "types.h"

extern u32 fn_12_A2C4(const u8 *data);

#pragma opt_common_subs off
u8 *fn_12_A0D8(u8 *data, s32 size, u32 mask) {
    u8 *end = data + size;
    u8 c;
    s32 state = 0;

    while (data < end) {
        c = *data++;
        switch (state) {
        case 0:
            if ((s8)c == 0) {
                state = 1;
            }
            break;
        case 1:
            if ((s8)c == 0) {
                state = 2;
            } else {
                state = 0;
            }
            break;
        case 2:
            if ((s8)c == 1) {
                state = 3;
            } else if ((s8)c != 0) {
                state = 0;
            }
            break;
        case 3:
            if (fn_12_A2C4(data - 4) & mask) {
                return data - 4;
            }
            state = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}
#pragma opt_common_subs reset

