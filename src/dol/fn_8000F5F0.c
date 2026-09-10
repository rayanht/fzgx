#include "types.h"

extern u32 OSGetResetButtonState(void);

u32 fn_8000F5F0(void) {
    return OSGetResetButtonState();
}
