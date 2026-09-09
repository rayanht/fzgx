#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include "sdk_addresses.h"
#pragma peephole off

void DBPrintf(char *format, ...);

// Hardware or OS state can change asynchronously.
volatile OSContext
    *__OSFPUContext : FZGX_ADDR___OSFPUContext; // fzgx-allow: S2 SDK asynchronous
                                                                 // state

void OSSwitchFPUContext_8000C350(register __OSException exception, register OSContext *context);

void __OSContextInit(void) {
    __OSSetExceptionHandler(7, OSSwitchFPUContext_8000C350);
    __OSFPUContext = ((void *)0);
    DBPrintf("FPU-unavailable handler installed\n");
}
