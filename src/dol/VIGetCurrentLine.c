#include <types.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef struct {
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
    u16 nhlines;
    u16 hlw;
    u8 hsy;
    u8 hcs;
    u8 hce;
    u8 hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

vu16 __VIRegs[59] : FZGX_ADDR___VIRegs;

extern VITiming *lbl_801A6960;

void (*__VIDisableRawPositionInterrupt())(s16, s16);

static inline u32 getCurrentHalfLine(void) {
    u32 hcount;
    u32 vcount0;
    u32 vcount;
    vcount = __VIRegs[22] & 0x7FF;
    do {
        vcount0 = vcount;
        hcount = __VIRegs[23] & 0x7FF;
        vcount = __VIRegs[22] & 0x7FF;
    } while (vcount0 != vcount);
    return ((vcount - 1) * 2) + ((hcount - 1) / lbl_801A6960->hlw);
}

u32 VIGetCurrentLine(void) {
    u32 halfLine;
    VITiming *tm;
    BOOL enabled;
    tm = lbl_801A6960;
    enabled = OSDisableInterrupts();
    halfLine = getCurrentHalfLine();
    OSRestoreInterrupts(enabled);
    if (halfLine >= tm->nhlines) {
        halfLine -= tm->nhlines;
    }
    return halfLine >> 1U;
}
