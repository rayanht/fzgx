#include "types.h"

extern void OSResetSystem(int, u32, int);

__declspec(section ".init") void fn_80005518(void) {
    OSResetSystem(0, 0, 0);
}
