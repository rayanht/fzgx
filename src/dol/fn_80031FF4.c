#include "types.h"

extern u32 __GXSaveCPUFifoAux(void);

u32 fn_80031FF4(void) {
    return __GXSaveCPUFifoAux();
}
