#include "types.h"

extern u8 Debug_BBA_801A6808;

__declspec(section ".init") u8 __get_debug_bba(void) {
    return Debug_BBA_801A6808;
}
