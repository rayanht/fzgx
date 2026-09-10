#include "types.h"

extern u32 gx;

#pragma peephole off
u32 fn_80030848(u32 index) {
    if (index >= 0x14) {
        return 0;
    }
    return gx + (index << 4) + 0x2d0;
}
#pragma peephole reset

