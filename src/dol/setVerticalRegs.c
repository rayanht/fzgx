#include <types.h>
#include <dolphin/types.h>

// Hardware or OS state can change asynchronously.
typedef volatile u64 vu64;

struct viBss {
    vu16 regs[59];
};

extern vu64 lbl_801A6948;

extern struct viBss lbl_8015CF68;

void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven, u16 psbOdd,
                 u16 psbEven, BOOL black) {
    struct viBss *bss = &lbl_8015CF68;

    u16 actualPrbOdd, actualPrbEven, actualPsbOdd, actualPsbEven, actualAcv, c, d;
    if ((bss->regs)[(54)] & 1) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }
    if (dispPosY % 2 == 0) {
        actualPrbOdd = (u16)(prbOdd + d * dispPosY);
        actualPsbOdd = (u16)(psbOdd + d * ((c * acv - dispSizeY) - dispPosY));
        actualPrbEven = (u16)(prbEven + d * dispPosY);
        actualPsbEven = (u16)(psbEven + d * ((c * acv - dispSizeY) - dispPosY));
    } else {
        actualPrbOdd = (u16)(prbEven + d * dispPosY);
        actualPsbOdd = (u16)(psbEven + d * ((c * acv - dispSizeY) - dispPosY));
        actualPrbEven = (u16)(prbOdd + d * dispPosY);
        actualPsbEven = (u16)(psbOdd + d * ((c * acv - dispSizeY) - dispPosY));
    }
    actualAcv = (u16)(dispSizeY / c);
    if (black) {
        actualPrbOdd += 2 * actualAcv - 2;
        actualPsbOdd += 2;
        actualPrbEven += 2 * actualAcv - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }
    (bss->regs)[(0)] = (u16)(equ | actualAcv << 4);
    lbl_801A6948 |= (1ull << (63 - ((0))));
    (bss->regs)[(7)] = (u16)actualPrbOdd << 0;
    lbl_801A6948 |= (1ull << (63 - ((7))));
    (bss->regs)[(6)] = (u16)actualPsbOdd << 0;
    lbl_801A6948 |= (1ull << (63 - ((6))));
    (bss->regs)[(9)] = (u16)actualPrbEven << 0;
    lbl_801A6948 |= (1ull << (63 - ((9))));
    (bss->regs)[(8)] = (u16)actualPsbEven << 0;
    lbl_801A6948 |= (1ull << (63 - ((8))));
}
