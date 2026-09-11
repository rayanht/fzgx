#include "types.h"

extern u8 lbl_80123B50[];
extern u32 lbl_801A644C;
extern u32 lbl_801A6454;
extern u32 SIDecodeType(u32);

u8 *fn_8001317C(u32 arg0) {
    u8 *base;
    s32 temp_r3;

    base = lbl_80123B50;
    temp_r3 = SIDecodeType(arg0);
    switch (temp_r3) {
    case 0x8:
        return base + 0x68;
    case 0x80:
        return (u8 *)&lbl_801A644C;
    case 0x5000000:
        return base + 0x74;
    case 0x10000:
        return base + 0x84;
    case 0x20000:
        return base + 0x94;
    case 0x2000000:
        return base + 0xA4;
    case 0x40000:
        return base + 0xB0;
    case 0x9000000:
        return base + 0xC0;
    case 0x88000000:
        return base + 0xD4;
    case 0x8B100000:
        return base + 0xE8;
    case 0x8200000:
        return base + 0xFC;
    case 0x8000000:
        return base + 0x108;
    case 0x40:
    default:
        return (u8 *)&lbl_801A6454;
    }
}
