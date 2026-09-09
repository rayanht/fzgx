#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include "sdk_addresses.h"
#pragma peephole off

// Hardware or OS state can change asynchronously.
volatile OSContext
    *__OSFPUContext : FZGX_ADDR___OSFPUContext; // fzgx-allow: S2 SDK asynchronous
                                                                 // state

void OSClearContext(register OSContext *context) {
    context->mode = 0;
    context->state = 0;
    if (context == __OSFPUContext)
        __OSFPUContext = ((void *)0);
}
