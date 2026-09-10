#include "types.h"

extern void (*lbl_801A64FC)(u32);

#pragma peephole off
void fn_80024C88(u8 *arg0) {
    u8 i;

    for (i = 0; i < 6; i++) {
        lbl_801A64FC(*(u32 *)(arg0 + i * 20 + 12));
    }
    for (i = 0; i < 6; i++) {
        lbl_801A64FC(*(u32 *)(arg0 + i * 20 + 132));
    }
    if (*(s32 *)(arg0 + 288) != 0) {
        for (i = 0; i < 3; i++) {
            lbl_801A64FC(*(u32 *)(arg0 + i * 4 + 292));
        }
    }
}
#pragma peephole reset

