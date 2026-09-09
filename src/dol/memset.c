#include "types.h"

extern u32 __fill_mem(u32);

__declspec(section ".init") u32 memset(u32 arg0) {
    __fill_mem(arg0);
    return arg0;
}
