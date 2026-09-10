#include "types.h"

typedef void (*fn_8002420C_Fn)(u32);

extern u32 lbl_801A64FC;

#pragma peephole off
void fn_8002420C(u8 *arg0) {
    u8 i;

    for (i = 0; i < 9; i++) {
        ((fn_8002420C_Fn)lbl_801A64FC)(*(u32 *)(arg0 + i * 0x14 + 0xc));
    }

    for (i = 0; i < 9; i++) {
        ((fn_8002420C_Fn)lbl_801A64FC)(*(u32 *)(arg0 + i * 0x14 + 0xc0));
    }

    if (*(s32 *)(arg0 + 0x1a4) != 0) {
        for (i = 0; i < 3; i++) {
            ((fn_8002420C_Fn)lbl_801A64FC)(*(u32 *)(arg0 + i * 4 + 0x1ac));
        }
    }
}
#pragma peephole reset

