#include "types.h"

extern void GXSetTevIndirect(void *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4,
                         u32 arg5, u32 arg6, u32 arg7, u32 arg8, u32 arg9);

void fn_80036EDC(void *arg0) {
    GXSetTevIndirect(arg0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
