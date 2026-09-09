#ifndef DOLPHIN_OS_OSERROR_H
#define DOLPHIN_OS_OSERROR_H
#include <dolphin/os/OSContext.h>

typedef u8 __OSException;

typedef u16 OSError;

typedef void (*OSErrorHandler)(OSError error, OSContext *context, ...);
#endif
