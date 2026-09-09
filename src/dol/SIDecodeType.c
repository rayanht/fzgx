#include <dolphin/si/SIPriv.h>
#include <dolphin/si.h>

u32 SIDecodeType(u32 type) {
    u32 error;
    error = type & 0xff;
    type &= ~0xff;
    if (error & 0x0008) {
        return 0x0008;
    }
    if (error & (0x0001 | 0x0002 | 0x0004 | 0x0040)) {
        return 0x0040;
    }
    if (error) {
        return 0x0080;
    }
    if ((type & 0x18000000u) == 0x00000000u) {
        switch (type & 0xffff0000) {
        case (0x00000000u | 0x05000000):
        case (0x00000000u | 0x00010000):
        case (0x00000000u | 0x00020000):
        case (0x00000000u | 0x02000000):
        case (0x00000000u | 0x00040000):
            return type & 0xffff0000;
            break;
        }
        return 0x0040;
    }
    if ((type & 0x18000000u) != 0x08000000u) {
        return 0x0040;
    }
    switch (type & 0xffff0000) {
    case (0x08000000u | 0x01000000):
    case (0x08000000u | 0x00000000):
        return type & 0xffff0000;
        break;
    }
    if ((type & 0xffe00000) == (0x08000000u | 0x00200000)) {
        return (0x08000000u | 0x00200000);
    }
    if ((type & 0x80000000) && !(type & 0x04000000)) {
        if ((type & (0x08000000u | 0x80000000 | 0x01000000 | 0x02000000 | 0x00100000)) ==
            (0x08000000u | 0x80000000 | 0x01000000 | 0x02000000 | 0x00100000)) {
            return (0x08000000u | 0x80000000 | 0x01000000 | 0x02000000 | 0x00100000);
        } else if (!(type & 0x02000000)) {
            return (0x08000000u | 0x80000000);
        }
    }
    if ((type & (0x08000000u | 0x01000000)) == (0x08000000u | 0x01000000)) {
        return (0x08000000u | 0x01000000);
    }
    return 0x0040;
}
