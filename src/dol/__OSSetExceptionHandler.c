#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#pragma peephole off

typedef void (*__OSExceptionHandler)(__OSException exception, OSContext *context);

extern __OSExceptionHandler *OSExceptionTable_801A676C;

__OSExceptionHandler __OSSetExceptionHandler(__OSException exception,
                                             __OSExceptionHandler handler) {
    __OSExceptionHandler oldHandler;
    oldHandler = OSExceptionTable_801A676C[exception];
    OSExceptionTable_801A676C[exception] = handler;
    return oldHandler;
}
