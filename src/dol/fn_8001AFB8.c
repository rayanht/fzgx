#include <types.h>
#include <dolphin/types.h>

// Hardware or OS state can change asynchronously.
typedef volatile u64 vu64;

typedef enum { VI_XFBMODE_SF = 0, VI_XFBMODE_DF } VIXFBMode;

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

typedef struct VIPositionInfo {
    u16 dispPosX;
    u16 dispPosY;
    u16 dispSizeX;
    u16 dispSizeY;
    u16 adjDispPosX;
    u16 adjDispPosY;
    u16 adjDispSizeY;
    u16 adjPanPosY;
    u16 adjPanSizeY;
    u16 fbSizeX;
    u16 fbSizeY;
    u16 panPosX;
    u16 panPosY;
    u16 panSizeX;
    u16 panSizeY;
    VIXFBMode xfbMode;
    u32 nonInter;
    u32 tv;
    u8 wordPerLine;
    u8 std;
    u8 wpl;
    u32 bufAddr;
    u32 tfbb;
    u32 bfbb;
    u8 xof;
    BOOL isBlack;
    BOOL is3D;
    u32 rbufAddr;
    u32 rtfbb;
    u32 rbfbb;
    VITimingInfo *timing;
} VIPositionInfo;

struct viBss {
    vu16 regs[59];
    unsigned char padding_118[2];
    vu16 shdwRegs[59];
    unsigned char padding_238[2];
    VIPositionInfo HorVer;
};

extern vu64 lbl_801A6948;

extern VITimingInfo timing[10];

extern struct viBss lbl_8015CF68;

static inline void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine,
                            VIXFBMode xfbMode, u16 dispPosY, u32 *tfbb, u32 *bfbb) {
    u32 bytesPerLine, xoffInWords;
    xoffInWords = (u32)panPosX / 16;
    bytesPerLine = (u32)wordPerLine * 32;
    *tfbb = bufAddr + xoffInWords * 32 + bytesPerLine * panPosY;
    *bfbb = (xfbMode == VI_XFBMODE_SF) ? *tfbb : (*tfbb + bytesPerLine);
    if (dispPosY % 2 == 1) {
        u32 tmp = *tfbb;
        *tfbb = *bfbb;
        *bfbb = tmp;
    }
    *tfbb = (u32)(((u32)(*tfbb)) & 0x3FFFFFFF);
    *bfbb = (u32)(((u32)(*bfbb)) & 0x3FFFFFFF);
}

void fn_8001AFB8(VIPositionInfo *hv, u32 *tfbb, u32 *bfbb, u32 *rtfbb, u32 *rbfbb) {
    struct viBss *bss = &lbl_8015CF68;

    u32 shifted;
    calcFbbs(hv->bufAddr, hv->panPosX, hv->adjPanPosY, hv->wordPerLine, hv->xfbMode,
             hv->adjDispPosY, tfbb, bfbb);
    if (hv->is3D) {
        calcFbbs(hv->rbufAddr, hv->panPosX, hv->adjPanPosY, hv->wordPerLine, hv->xfbMode,
                 hv->adjDispPosY, rtfbb, rbfbb);
    }
    if (((*tfbb) < 16 * 1024 * 1024) && ((*bfbb) < 16 * 1024 * 1024) &&
        ((*rtfbb) < 16 * 1024 * 1024) && ((*rbfbb) < 16 * 1024 * 1024)) {
        shifted = 0;
    } else {
        shifted = 1;
    }
    if (shifted) {
        *tfbb >>= 5;
        *bfbb >>= 5;
        *rtfbb >>= 5;
        *rbfbb >>= 5;
    }
    (bss->regs)[(15)] = (u16)(*tfbb & 0xFFFF);
    lbl_801A6948 |= (1ull << (63 - ((15))));
    (bss->regs)[(14)] = (u16)((((*tfbb >> 16))) | hv->xof << 8 | shifted << 12);
    lbl_801A6948 |= (1ull << (63 - ((14))));
    (bss->regs)[(19)] = (u16)(*bfbb & 0xFFFF);
    lbl_801A6948 |= (1ull << (63 - ((19))));
    (bss->regs)[(18)] = (u16)(*bfbb >> 16);
    lbl_801A6948 |= (1ull << (63 - ((18))));
    if (hv->is3D) {
        (bss->regs)[(17)] = *rtfbb & 0xffff;
        lbl_801A6948 |= (1ull << (63 - ((17))));
        (bss->regs)[(16)] = *rtfbb >> 16;
        lbl_801A6948 |= (1ull << (63 - ((16))));
        (bss->regs)[(21)] = *rbfbb & 0xFFFF;
        lbl_801A6948 |= (1ull << (63 - ((21))));
        (bss->regs)[(20)] = *rbfbb >> 16;
        lbl_801A6948 |= (1ull << (63 - ((20))));
    }
}
