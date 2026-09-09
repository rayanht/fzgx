#include "types.h"

extern u32 fn_8008B028(u32);

__declspec(section ".init") u32 fn_80003590(u32 arg0) {
    fn_8008B028(arg0);
    return arg0;
}
