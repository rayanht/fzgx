#include <types.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef enum {
    VI_TVMODE_NTSC_INT = (((0) << 2) + (0)),
    VI_TVMODE_NTSC_DS = (((0) << 2) + (1)),
    VI_TVMODE_NTSC_PROG = (((0) << 2) + (2)),
    VI_TVMODE_NTSC_3D = (((0) << 2) + (3)),
    VI_TVMODE_PAL_INT = (((1) << 2) + (0)),
    VI_TVMODE_PAL_DS = (((1) << 2) + (1)),
    VI_TVMODE_MPAL_INT = (((2) << 2) + (0)),
    VI_TVMODE_MPAL_DS = (((2) << 2) + (1)),
    VI_TVMODE_DEBUG_INT = (((3) << 2) + (0)),
    VI_TVMODE_DEBUG_PAL_INT = (((4) << 2) + (0)),
    VI_TVMODE_DEBUG_PAL_DS = (((4) << 2) + (1)),
    VI_TVMODE_EURGB60_INT = (((5) << 2) + (0)),
    VI_TVMODE_EURGB60_DS = (((5) << 2) + (1)),
    VI_TVMODE_GCA_INT = (((6) << 2) + (0)),
    VI_TVMODE_GCA_DS = (((6) << 2) + (1)),
    VI_TVMODE_GCA_PROG = (((6) << 2) + (2)),
} VITVMode;

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

VITimingInfo *getTiming(VITVMode mode);

void __VIInit(VITVMode mode) {
    VITimingInfo *tm;
    u32 nonInter;
    vu32 a;
    u32 tv, tvForReg;
    u16 hct, vct;
    nonInter = mode & 2;
    tv = (u32)mode >> 2;
    *(u32 *)((void *)((u32)(0xCC) + (0x8000 << 16))) = tv;
    tm = getTiming(mode);
    __VIRegs[(1)] = 2;
    for (a = 0; a < 1000; a++) {
        ;
    }
    __VIRegs[(1)] = 0;
    __VIRegs[(3)] = tm->hlw << 0;
    __VIRegs[(2)] = (tm->hce << 0) | (tm->hcs << 8);
    __VIRegs[(5)] = (tm->hsy << 0) | ((tm->hbe640 & ((1 << 9) - 1)) << 7);
    __VIRegs[(4)] = ((tm->hbe640 >> 9) << 0) | (tm->hbs640 << 1);
    __VIRegs[(0)] = (tm->equ << 0) | (0 << 4);
    __VIRegs[(7)] = (tm->prbOdd + tm->acv * 2 - 2) << 0;
    __VIRegs[(6)] = tm->psbOdd + 2 << 0;
    __VIRegs[(9)] = (tm->prbEven + tm->acv * 2 - 2) << 0;
    __VIRegs[(8)] = tm->psbEven + 2 << 0;
    __VIRegs[(11)] = (tm->bs1 << 0) | (tm->be1 << 5);
    __VIRegs[(10)] = (tm->bs3 << 0) | (tm->be3 << 5);
    __VIRegs[(13)] = (tm->bs2 << 0) | (tm->be2 << 5);
    __VIRegs[(12)] = (tm->bs4 << 0) | (tm->be4 << 5);
    __VIRegs[(36)] = (40 << 0) | (40 << 8);
    __VIRegs[(27)] = 1;
    __VIRegs[(26)] = (1 << 0) | (1 << 12) | (0 << 15);
    hct = (tm->hlw + 1);
    vct = (tm->numHalfLines / 2 + 1) | (1 << 12) | (0 << 15);
    __VIRegs[(25)] = hct << 0;
    __VIRegs[(24)] = vct;
    if (mode != VI_TVMODE_NTSC_PROG && mode != VI_TVMODE_NTSC_3D && mode != VI_TVMODE_GCA_PROG) {
        __VIRegs[(1)] =
            (1 << 0) | (0 << 1) | (nonInter << 2) | (0 << 3) | (0 << 4) | (0 << 6) | (tv << 8);
        __VIRegs[(54)] = 0;
    } else {
        __VIRegs[(1)] = (1 << 0) | (0 << 1) | (1 << 2) | (0 << 3) | (0 << 4) | (0 << 6) | (tv << 8);
        __VIRegs[(54)] = 1;
    }
}
