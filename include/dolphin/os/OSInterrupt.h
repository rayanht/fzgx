#ifndef DOLPHIN_OS_OSINTERRUPT_H
#define DOLPHIN_OS_OSINTERRUPT_H
#include <dolphin/os/OSContext.h>

typedef u32 OSInterruptMask;

typedef s16 __OSInterrupt;

typedef void (*__OSInterruptHandler)(__OSInterrupt interrupt, OSContext *context);

BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
#endif
