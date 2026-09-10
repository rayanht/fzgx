#pragma use_lmw_stmw off
#include "types.h"

extern u32 lbl_801A6DA0;
extern u32 lbl_801A6DA4;
extern u32 lbl_801A6DA8;
extern u32 OSGetArenaHi(void);
extern u32 fn_80071794(u32);
extern void OSSetArenaHi(u32);

u32 fn_8007785C(u32 count, s32 useArena) {
    u32 i;
    u32 top;

    if (useArena != 0) {
        top = OSGetArenaHi();
        top -= (count * 48) & 0xFFFFFFE0;
        lbl_801A6DA8 = top;
        top -= (count * 4) & 0xFFFFFFE0;
        lbl_801A6DA4 = top;
        lbl_801A6DA0 = 0;
        OSSetArenaHi(lbl_801A6DA4);
    } else {
        lbl_801A6DA8 = fn_80071794(count * 48);
        lbl_801A6DA4 = fn_80071794(count * 4);
        lbl_801A6DA0 = 1;
        for (i = 0; i < count; i++) {
            ((u32 *)lbl_801A6DA4)[i] = lbl_801A6DA8 + i * 48;
        }
    }
    return lbl_801A6DA4;
}
