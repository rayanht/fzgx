#include <dolphin/os.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"
#pragma peephole off

vu32 __PIRegs[12] : FZGX_ADDR___PIRegs;

vu16 __MEMRegs[64] : FZGX_ADDR___MEMRegs;

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

vu32 __EXIRegs[16] : FZGX_ADDR___EXIRegs;

vu32 __AIRegs[8] : FZGX_ADDR___AIRegs;

u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current) {
    u32 reg;
    switch (__cntlzw(mask)) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        reg = 0;
        if (!(current & (0x80000000u >> (0))))
            reg |= 0x1;
        if (!(current & (0x80000000u >> (1))))
            reg |= 0x2;
        if (!(current & (0x80000000u >> (2))))
            reg |= 0x4;
        if (!(current & (0x80000000u >> (3))))
            reg |= 0x8;
        if (!(current & (0x80000000u >> (4))))
            reg |= 0x10;
        __MEMRegs[0x0000000e] = (u16)reg;
        mask &= ~((0x80000000u >> (0)) | (0x80000000u >> (1)) | (0x80000000u >> (2)) |
                  (0x80000000u >> (3)) | (0x80000000u >> (4)));
        break;
    case 5:
    case 6:
    case 7:
        reg = __DSPRegs[0x00000005];
        reg &= ~0x1F8;
        if (!(current & (0x80000000u >> (5))))
            reg |= 0x10;
        if (!(current & (0x80000000u >> (6))))
            reg |= 0x40;
        if (!(current & (0x80000000u >> (7))))
            reg |= 0x100;
        __DSPRegs[0x00000005] = (u16)reg;
        mask &= ~((0x80000000u >> (5)) | (0x80000000u >> (6)) | (0x80000000u >> (7)));
        break;
    case 8:
        reg = __AIRegs[0];
        reg &= ~0x2C;
        if (!(current & (0x80000000u >> (8))))
            reg |= 0x4;
        __AIRegs[0] = reg;
        mask &= ~((0x80000000u >> (8)));
        break;
    case 9:
    case 10:
    case 11:
        reg = __EXIRegs[0];
        reg &= ~0x2C0F;
        if (!(current & (0x80000000u >> (9))))
            reg |= 0x1;
        if (!(current & (0x80000000u >> (10))))
            reg |= 0x4;
        if (!(current & (0x80000000u >> (11))))
            reg |= 0x400;
        __EXIRegs[0] = reg;
        mask &= ~((0x80000000u >> (9)) | (0x80000000u >> (10)) | (0x80000000u >> (11)));
        break;
    case 12:
    case 13:
    case 14:
        reg = __EXIRegs[5];
        reg &= ~0xC0F;
        if (!(current & (0x80000000u >> (12))))
            reg |= 0x1;
        if (!(current & (0x80000000u >> (13))))
            reg |= 0x4;
        if (!(current & (0x80000000u >> (14))))
            reg |= 0x400;
        __EXIRegs[5] = reg;
        mask &= ~((0x80000000u >> (12)) | (0x80000000u >> (13)) | (0x80000000u >> (14)));
        break;
    case 15:
    case 16:
        reg = __EXIRegs[10];
        reg &= ~0xF;
        if (!(current & (0x80000000u >> (15))))
            reg |= 0x1;
        if (!(current & (0x80000000u >> (16))))
            reg |= 0x4;
        __EXIRegs[10] = reg;
        mask &= ~((0x80000000u >> (15)) | (0x80000000u >> (16)));
        break;
    case 17:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 18:
    case 19:
    case 26:
        reg = 0xF0;
        if (!(current & (0x80000000u >> (17)))) {
            reg |= 0x800;
        }
        if (!(current & (0x80000000u >> (20)))) {
            reg |= 0x8;
        }
        if (!(current & (0x80000000u >> (21)))) {
            reg |= 0x4;
        }
        if (!(current & (0x80000000u >> (22)))) {
            reg |= 0x2;
        }
        if (!(current & (0x80000000u >> (23)))) {
            reg |= 0x1;
        }
        if (!(current & (0x80000000u >> (24)))) {
            reg |= 0x100;
        }
        if (!(current & (0x80000000u >> (25)))) {
            reg |= 0x1000;
        }
        if (!(current & (0x80000000u >> (18)))) {
            reg |= 0x200;
        }
        if (!(current & (0x80000000u >> (19)))) {
            reg |= 0x400;
        }
        if (!(current & (0x80000000u >> (26)))) {
            reg |= 0x2000;
        }
        __PIRegs[1] = reg;
        mask &= ~((0x80000000u >> (17)) | (0x80000000u >> (20)) | (0x80000000u >> (21)) |
                  (0x80000000u >> (22)) | (0x80000000u >> (23)) | (0x80000000u >> (24)) |
                  (0x80000000u >> (18)) | (0x80000000u >> (19)) | (0x80000000u >> (25)) |
                  (0x80000000u >> (26)));
        break;
    default:
        break;
    }
    return mask;
}
