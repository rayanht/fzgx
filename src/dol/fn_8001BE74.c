#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef struct VITimingInfo {
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
    u8 bs1;
    u8 bs2;
    u8 bs3;
    u8 bs4;
    u16 be1;
    u16 be2;
    u16 be3;
    u16 be4;
    u16 numHalfLines;
    u16 hlw;
    u8 hsy;
    u8 hcs;
    u8 hce;
    u8 hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITimingInfo;

vu16 __VIRegs[59] : FZGX_ADDR___VIRegs;

extern VITimingInfo *lbl_801A6960;

static inline void GetCurrentDisplayPosition(u32 *hct, u32 *vct) {
    u32 hcount, vcount0, vcount;
    vcount = __VIRegs[(22)] & 0x7FF;
    do {
        vcount0 = vcount;
        hcount = __VIRegs[(23)] & 0x7FF;
        vcount = __VIRegs[(22)] & 0x7FF;
    } while (vcount0 != vcount);
    *hct = hcount;
    *vct = vcount;
}

static inline u32 getCurrentHalfLine(void) {
    u32 hcount, vcount;
    GetCurrentDisplayPosition(&hcount, &vcount);
    return ((vcount - 1) << 1) + ((hcount - 1) / lbl_801A6960->hlw);
}

u32 fn_8001BE74() { return (getCurrentHalfLine() < lbl_801A6960->numHalfLines) ? 1 : 0; }
