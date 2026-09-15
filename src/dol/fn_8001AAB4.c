#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef enum {
    VI_TVMODE_NTSC_INT = ((((0)) << 2) + ((0))),
    VI_TVMODE_NTSC_DS = ((((0)) << 2) + ((1))),
    VI_TVMODE_NTSC_PROG = ((((0)) << 2) + ((2))),
    VI_TVMODE_NTSC_3D = ((((0)) << 2) + ((3))),
    VI_TVMODE_PAL_INT = ((((1)) << 2) + ((0))),
    VI_TVMODE_PAL_DS = ((((1)) << 2) + ((1))),
    VI_TVMODE_MPAL_INT = ((((2)) << 2) + ((0))),
    VI_TVMODE_MPAL_DS = ((((2)) << 2) + ((1))),
    VI_TVMODE_DEBUG_INT = ((((3)) << 2) + ((0))),
    VI_TVMODE_DEBUG_PAL_INT = ((((4)) << 2) + ((0))),
    VI_TVMODE_DEBUG_PAL_DS = ((((4)) << 2) + ((1))),
    VI_TVMODE_EURGB60_INT = ((((5)) << 2) + ((0))),
    VI_TVMODE_EURGB60_DS = ((((5)) << 2) + ((1))),
    VI_TVMODE_GCA_INT = ((((6)) << 2) + ((0))),
    VI_TVMODE_GCA_DS = ((((6)) << 2) + ((1))),
    VI_TVMODE_GCA_PROG = ((((6)) << 2) + ((2))),
} VITVMode;

typedef enum { VI_XFBMODE_SF = 0, VI_XFBMODE_DF } VIXFBMode;

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

typedef struct {
    u16 DispPosX;
    u16 DispPosY;
    u16 DispSizeX;
    u16 DispSizeY;
    u16 AdjustedDispPosX;
    u16 AdjustedDispPosY;
    u16 AdjustedDispSizeY;
    u16 AdjustedPanPosY;
    u16 AdjustedPanSizeY;
    u16 FBSizeX;
    u16 FBSizeY;
    u16 PanPosX;
    u16 PanPosY;
    u16 PanSizeX;
    u16 PanSizeY;
    VIXFBMode FBMode;
    u32 nonInter;
    u32 tv;
    u8 wordPerLine;
    u8 std;
    u8 wpl;
    u32 bufAddr;
    u32 tfbb;
    u32 bfbb;
    u8 xof;
    BOOL black;
    BOOL threeD;
    u32 rbufAddr;
    u32 rtfbb;
    u32 rbfbb;
    VITiming *timing;
} SomeVIStruct;

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler);

void OSInitThreadQueue(OSThreadQueue *queue);

OSSram *__OSLockSram(void);

BOOL __OSUnlockSram(BOOL commit);

void OSRegisterVersion(const char *version);

vu16 __VIRegs[59] : FZGX_ADDR___VIRegs;

extern const char *lbl_801A64A0;

extern BOOL lbl_801A6920;

extern volatile u32 lbl_801A6924; // fzgx-allow: S2 SDK asynchronous state

extern volatile u32 lbl_801A6928; // fzgx-allow: S2 SDK asynchronous state

extern OSThreadQueue lbl_801A692C;

extern void (*lbl_801A6934)(u32);

extern void (*lbl_801A6938)(u32);

extern u32 lbl_801A693C;

extern s16 lbl_801A6940;

extern s16 lbl_801A6942;

extern volatile u32 lbl_801A6944; // fzgx-allow: S2 SDK asynchronous state

extern volatile u64 lbl_801A6948; // fzgx-allow: S2 SDK asynchronous state

extern volatile u32 lbl_801A6950; // fzgx-allow: S2 SDK asynchronous state

extern volatile u64 lbl_801A6958; // fzgx-allow: S2 SDK asynchronous state

extern VITiming *lbl_801A6960;

extern u32 CurrTvMode_801A6964;

void (*__VIDisableRawPositionInterrupt())(s16, s16);

static unsigned char lbl_801241C8[68] = {
    60, 60, 32,  68,  111, 108, 112, 104, 105, 110, 32, 83, 68,  75,  32,  45,  32,
    86, 73, 9,   114, 101, 108, 101, 97,  115, 101, 32, 98, 117, 105, 108, 100, 58,
    32, 83, 101, 112, 32,  32,  53,  32,  50,  48,  48, 50, 32,  48,  53,  58,  51,
    51, 58, 49,  51,  32,  40,  48,  120, 50,  51,  48, 49, 41,  32,  62,  62,  0};

static VITiming timing[10] = {{6,   240, 24,  25,  3,  2,  12,  13,  12,  13,  520, 519,
                               520, 519, 525, 429, 64, 71, 105, 162, 373, 122, 412},
                              {6,   240, 24,  24,  4,  4,  12,  12,  12,  12,  520, 520,
                               520, 520, 526, 429, 64, 71, 105, 162, 373, 122, 412},
                              {5,   287, 35,  36,  1,  0,  13,  12,  11,  10,  619, 618,
                               617, 620, 625, 432, 64, 75, 106, 172, 380, 133, 420},
                              {5,   287, 33,  33,  2,  2,  13,  11,  13,  11,  619, 621,
                               619, 621, 624, 432, 64, 75, 106, 172, 380, 133, 420},
                              {6,   240, 24,  25,  3,  2,  16,  15,  14,  13,  518, 517,
                               516, 519, 525, 429, 64, 78, 112, 162, 373, 122, 412},
                              {6,   240, 24,  24,  4,  4,  16,  14,  16,  14,  518, 520,
                               518, 520, 526, 429, 64, 78, 112, 162, 373, 122, 412},
                              {12,   480,  48,   48,  6,  6,  24,  24,  24,  24,  1038, 1038,
                               1038, 1038, 1050, 429, 64, 71, 105, 162, 373, 122, 412},
                              {12,   480,  44,   44,  10, 10, 24,  24,  24,  24,  1038, 1038,
                               1038, 1038, 1050, 429, 64, 71, 105, 168, 379, 122, 412},
                              {6,   241, 24,  25,  1,  0,  12,  13,  12,  13,  520, 519,
                               520, 519, 525, 429, 64, 71, 105, 159, 370, 122, 412},
                              {12,   480,  48,   48,  6,  6,  24,  24,  24,  24,  1038, 1038,
                               1038, 1038, 1050, 429, 64, 71, 105, 180, 391, 122, 412}};

static u16 taps[25] = {0x01F0, 0x01DC, 0x01AE, 0x0174, 0x0129, 0x00DB, 0x008E, 0x0046, 0x000C,
                       0x00E2, 0x00CB, 0x00C0, 0x00C4, 0x00CF, 0x00DE, 0x00EC, 0x00FC, 0x0008,
                       0x000F, 0x0013, 0x0013, 0x000F, 0x000C, 0x0008, 0x0001};

static volatile u16 lbl_8015CF68[59]; // fzgx-allow: S2 SDK asynchronous state

static unsigned char sdk_gap____bss_0_76[120];

static SomeVIStruct HorVer;

#pragma section code_type ".fzgxpool"
static void sdk_layout____bss_0(void) {
    volatile unsigned char sink; // fzgx-allow: S2 SDK asynchronous state
    sink = *(unsigned char *)&lbl_8015CF68;
    sink = *(unsigned char *)&sdk_gap____bss_0_76;
    sink = *(unsigned char *)&HorVer;
}
#pragma section code_type ".text"

static inline u32 getEncoderType(void) { return 1; }

void fn_8001A55C(__OSInterrupt unused, OSContext *context);

VITiming *getTiming(VITVMode mode);

void __VIInit(VITVMode mode);

static inline void AdjustPosition(u16 acv) {
    s32 coeff;
    s32 frac;
    HorVer.AdjustedDispPosX =
        (((s16)HorVer.DispPosX + lbl_801A6940) > (0x2D0 - HorVer.DispSizeX)
             ? (0x2D0 - HorVer.DispSizeX)
         : ((s16)HorVer.DispPosX + lbl_801A6940) < (0) ? (0)
                                                       : ((s16)HorVer.DispPosX + lbl_801A6940));
    coeff = (HorVer.FBMode == VI_XFBMODE_SF) ? 2 : 1;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY =
        (((s16)HorVer.DispPosY + lbl_801A6942) > (frac) ? ((s16)HorVer.DispPosY + lbl_801A6942)
                                                        : (frac));
    HorVer.AdjustedDispSizeY = HorVer.DispSizeY +
                               (((s16)HorVer.DispPosY + lbl_801A6942 - frac) < (0)
                                    ? ((s16)HorVer.DispPosY + lbl_801A6942 - frac)
                                    : (0)) -
                               (((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + lbl_801A6942 -
                                 (((s16)acv * 2) - frac)) > (0)
                                    ? ((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + lbl_801A6942 -
                                       (((s16)acv * 2) - frac))
                                    : (0));
    HorVer.AdjustedPanPosY = HorVer.PanPosY - ((((s16)HorVer.DispPosY + lbl_801A6942 - frac) < (0)
                                                    ? ((s16)HorVer.DispPosY + lbl_801A6942 - frac)
                                                    : (0)) /
                                               coeff);
    HorVer.AdjustedPanSizeY = HorVer.PanSizeY +
                              ((((s16)HorVer.DispPosY + lbl_801A6942 - frac) < (0)
                                    ? ((s16)HorVer.DispPosY + lbl_801A6942 - frac)
                                    : (0)) /
                               coeff) -
                              ((((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + lbl_801A6942 -
                                 (((s16)acv * 2) - frac)) > (0)
                                    ? ((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + lbl_801A6942 -
                                       (((s16)acv * 2) - frac))
                                    : (0)) /
                               coeff);
}

static inline void ImportAdjustingValues(void) {
    OSSram *sram = __OSLockSram();
    (void)0;
    lbl_801A6940 = sram->displayOffsetH;
    lbl_801A6942 = 0;
    __OSUnlockSram(0);
}

void fn_8001AAB4(void) {
    u16 dspCfg;
    u32 value;
    u32 tv;
    u32 tvInBootrom;
    if (lbl_801A6920) {
        return;
    }
    OSRegisterVersion(lbl_801A64A0);
    lbl_801A6920 = 1;
    lbl_801A693C = getEncoderType();
    if (!(__VIRegs[1] & 1)) {
        __VIInit(VI_TVMODE_NTSC_INT);
    }
    lbl_801A6924 = 0;
    lbl_801A6948 = 0;
    lbl_801A6958 = 0;
    lbl_801A6944 = 0;
    lbl_801A6950 = 0;
    lbl_801A6928 = 0;
    __VIRegs[39] = taps[0] | ((taps[1] & 0x3F) << 10);
    __VIRegs[38] = (taps[1] >> 6) | (taps[2] << 4);
    __VIRegs[41] = taps[3] | ((taps[4] & 0x3F) << 10);
    __VIRegs[40] = (taps[4] >> 6) | (taps[5] << 4);
    __VIRegs[43] = taps[6] | ((taps[7] & 0x3F) << 10);
    __VIRegs[42] = (taps[7] >> 6) | (taps[8] << 4);
    __VIRegs[45] = taps[9] | (taps[10] << 8);
    __VIRegs[44] = taps[11] | (taps[12] << 8);
    __VIRegs[47] = taps[13] | (taps[14] << 8);
    __VIRegs[46] = taps[15] | (taps[16] << 8);
    __VIRegs[49] = taps[17] | (taps[18] << 8);
    __VIRegs[48] = taps[19] | (taps[20] << 8);
    __VIRegs[51] = taps[21] | (taps[22] << 8);
    __VIRegs[50] = taps[23] | (taps[24] << 8);
    __VIRegs[56] = 0x280;
    ImportAdjustingValues();
    tvInBootrom = *(u32 *)((void *)((u32)(0xCC) + (0x8000 << 16)));
    dspCfg = __VIRegs[1];
    HorVer.nonInter = (s32)((dspCfg >> 2U) & 1);
    HorVer.tv = ((u32)(dspCfg) & 0x300) >> 8;
    if (tvInBootrom == (1) && HorVer.tv == (0)) {
        HorVer.tv = (5);
    }
    tv = (HorVer.tv == 3) ? 0 : HorVer.tv;
    HorVer.timing = getTiming((tv << 2) + HorVer.nonInter);
    lbl_8015CF68[1] = dspCfg;
    lbl_801A6960 = HorVer.timing;
    CurrTvMode_801A6964 = HorVer.tv;
    HorVer.DispSizeX = 640;
    HorVer.DispSizeY = lbl_801A6960->acv * 2;
    HorVer.DispPosX = (720 - HorVer.DispSizeX) / 2;
    HorVer.DispPosY = 0;
    AdjustPosition(lbl_801A6960->acv);
    HorVer.FBSizeX = 640;
    HorVer.FBSizeY = lbl_801A6960->acv * 2;
    HorVer.PanPosX = 0;
    HorVer.PanPosY = 0;
    HorVer.PanSizeX = 640;
    HorVer.PanSizeY = lbl_801A6960->acv * 2;
    HorVer.FBMode = 0;
    HorVer.wordPerLine = 40;
    HorVer.std = 40;
    HorVer.wpl = 40;
    HorVer.xof = 0;
    HorVer.black = 1;
    HorVer.threeD = 0;
    OSInitThreadQueue(&lbl_801A692C);
    tvInBootrom = __VIRegs[24];
    value = tvInBootrom;
    value &= ~0x8000;
    value = (u16)value;
    __VIRegs[24] = value;
    value = __VIRegs[26];
    value = value & ~0x8000;
    value = (u16)value;
    __VIRegs[26] = value;
    lbl_801A6934 = ((void *)0);
    lbl_801A6938 = ((void *)0);
    __OSSetInterruptHandler(0x18, fn_8001A55C);
    __OSUnmaskInterrupts(0x80);
}
