#include "types.h"

extern u8 Debug_BBA_801A6808;

__declspec(section ".init") void __set_debug_bba(void) {
    Debug_BBA_801A6808 = 1;
}
