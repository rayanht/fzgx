#include <types.h>

typedef u8 GXBool;

extern u16 *__peReg;

void GXPokeDstAlpha(GXBool enable, u8 alpha) {
    u32 val = 0;
    (val) = (val & ~(((1 << (8)) - 1) << (31 - (0x18) - (8) + 1))) |
            ((int)(alpha) << (31 - (0x18) - (8) + 1));
    (val) = (val & ~(((1 << (1)) - 1) << (31 - (0x17) - (1) + 1))) |
            ((int)(enable) << (31 - (0x17) - (1) + 1));
    __peReg[2] = val;
}
