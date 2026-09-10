#include "types.h"
#include "dolphin/os/OSTime.h"

extern u16 lbl_801A6CBC;
extern u16 lbl_801A6CC4;
extern u16 lbl_801A6CC6;
extern u32 fn_80032360(void);
extern char lbl_8015AA10[];
extern u32 lbl_801A6CB0;
extern u32 lbl_801A6CC0;
extern u32 lbl_801A6CD4;
extern u32 lbl_801A6CD8;
extern u32 lbl_801A6CE4;
extern u8 lbl_801A6CB4;
extern u32 __OSBusClock : 0x800000F8; /* fzgx-allow: A1 fixed cached-RAM bus-clock word; retail carries no reloc */
extern u32 GXGetFifoPtrs(u32, u32 *, u32 *);
extern void OSReport(const char *, ...);
extern OSTime OSGetTime(void);

s32 fn_8006FDEC(void) {
    u32 value_c;
    u32 value_8;
    s32 ret;
    OSTime t0;

    ret = 0;
    t0 = OSGetTime();

    while (lbl_801A6CB4 == 0) {
        if (OSGetTime() - t0 > (OSTime)(__OSBusClock >> 2)) {
            OSReport(lbl_8015AA10, lbl_801A6CC6, lbl_801A6CC4, lbl_801A6CBC,
                     (lbl_801A6CC0 << 3) / ((__OSBusClock >> 2) / 125000));
            if (lbl_801A6CB0 != 0) {
                ((void (*)(void))lbl_801A6CB0)();
            }
            ret = 1;
            break;
        }
    }

    GXGetFifoPtrs(fn_80032360(), &value_c, &value_8);

    if (lbl_801A6CD8 > value_8) {
        lbl_801A6CD4 = lbl_801A6CE4 + value_8 - lbl_801A6CD8;
    } else {
        lbl_801A6CD4 = value_8 - lbl_801A6CD8;
    }

    return ret;
}
