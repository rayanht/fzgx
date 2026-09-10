#include "types.h"

extern u32 DVDLowWaitCoverClose(u32);
extern void cbForStateMotorStopped(void);

void fn_800186C0(void) {
    DVDLowWaitCoverClose((u32)cbForStateMotorStopped);
}
