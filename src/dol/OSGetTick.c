#include "types.h"

asm u32 OSGetTick(void) {
    nofralloc
    mftb r3, 268
    blr
}
