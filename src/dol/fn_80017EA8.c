#include "types.h"

extern u32 DVDLowStopMotor(u32);
extern void cbForStateGoToRetry(void);

u32 fn_80017EA8(void) {
    return DVDLowStopMotor((u32)cbForStateGoToRetry);
}
