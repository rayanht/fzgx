#include "types.h"

extern u32 gx;

void fn_800350F4(u32 arg0) {
    u32 *reg = (u32 *)(gx + 0x1EC);
    *reg = (*reg & 0xFFFFFE7F) | (arg0 << 7);
}
