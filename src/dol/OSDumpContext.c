#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include "sdk_addresses.h"
#pragma peephole off

void OSReport(const char *msg, ...);

OSContext *OSGetCurrentContext();

void OSSetCurrentContext(OSContext *context);

// Hardware or OS state can change asynchronously.
volatile OSContext
    *__OSCurrentContext : FZGX_ADDR___OSCurrentContext; // fzgx-allow: S2 SDK
                                                                         // asynchronous state

// Hardware or OS state can change asynchronously.
volatile OSContext
    *__OSFPUContext : FZGX_ADDR___OSFPUContext; // fzgx-allow: S2 SDK asynchronous
                                                                 // state

void OSSetCurrentContext(register OSContext *context);

static inline OSContext *OSGetCurrentContext(void) { return (OSContext *)__OSCurrentContext; }

static inline void OSClearContext(register OSContext *context) {
    context->mode = 0;
    context->state = 0;
    if (context == __OSFPUContext)
        __OSFPUContext = ((void *)0);
}

void OSDumpContext(OSContext *context) {
    u32 i;
    u32 *p;
    OSReport("------------------------- Context 0x%08x -------------------------\n", context);
    for (i = 0; i < 16; ++i) {
        OSReport("r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n", i, context->gpr[i],
                 context->gpr[i], i + 16, context->gpr[i + 16], context->gpr[i + 16]);
    }
    OSReport("LR   = 0x%08x                   CR   = 0x%08x\n", context->lr, context->cr);
    OSReport("SRR0 = 0x%08x                   SRR1 = 0x%08x\n", context->srr0, context->srr1);
    OSReport("\nGQRs----------\n");
    for (i = 0; i < 4; ++i) {
        OSReport("gqr%d = 0x%08x \t gqr%d = 0x%08x\n", i, context->gqr[i], i + 4,
                 context->gqr[i + 4]);
    }
    if (context->state & 0x01u) {
        OSContext *currentContext;
        OSContext fpuContext;
        BOOL enabled;
        enabled = OSDisableInterrupts();
        currentContext = OSGetCurrentContext();
        OSClearContext(&fpuContext);
        OSSetCurrentContext(&fpuContext);
        OSReport("\n\nFPRs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("fr%d \t= %d \t fr%d \t= %d\n", i, (u32)context->fpr[i], i + 1,
                     (u32)context->fpr[i + 1]);
        }
        OSReport("\n\nPSFs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("ps%d \t= 0x%x \t ps%d \t= 0x%x\n", i, (u32)context->psf[i], i + 1,
                     (u32)context->psf[i + 1]);
        }
        OSClearContext(&fpuContext);
        OSSetCurrentContext(currentContext);
        OSRestoreInterrupts(enabled);
    }
    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32 *)context->gpr[1]; p && (u32)p != 0xffffffff && i++ < 16; p = (u32 *)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }
}
