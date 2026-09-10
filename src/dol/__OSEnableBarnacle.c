#include <dolphin/exi/EXIPriv.h>

s32 EXIGetID(s32 chan, u32 dev, u32 *id);

extern s32 lbl_801A6840;

extern u32 lbl_801A6844;

extern u32 lbl_801A6848;

extern u32 lbl_801A684C;

BOOL ProbeBarnacle(s32 chan, u32 dev, u32 *revision);

void __OSEnableBarnacle(s32 chan, u32 dev) {
    u32 id;
    if (EXIGetID(chan, dev, &id)) {
        switch (id) {
        case 0xffffffff:
        case 0x00000004:
        case 0x00000008:
        case 0x00000010:
        case 0x00000020:
        case 0x01010000:
        case 0x01020000:
        case 0x02020000:
        case 0x03010000:
        case 0x04220000:
        case 0x04020100:
        case 0x04020200:
        case 0x04020300:
        case 0x04040404:
        case 0x04060000:
        case 0x04120000:
        case 0x04130000:
        case 0x80000000 | 0x00000004:
        case 0x80000000 | 0x00000008:
        case 0x80000000 | 0x00000010:
        case 0x80000000 | 0x00000020:
            break;
        default:
            if (ProbeBarnacle(chan, dev, &id)) {
                lbl_801A6840 = chan;
                lbl_801A6844 = dev;
                lbl_801A6848 = lbl_801A684C = 0xa5ff005a;
            }
            break;
        }
    }
}
