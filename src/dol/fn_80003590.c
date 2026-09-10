#include "types.h"

extern u32 TRK_fill_mem(u32);

__declspec(section ".init") u32 fn_80003590(u32 arg0) {
    TRK_fill_mem(arg0);
    return arg0;
}
