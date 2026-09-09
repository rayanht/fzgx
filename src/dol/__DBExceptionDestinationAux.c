#include "types.h"

extern char lbl_80123E10[24];
extern void OSReport(const char *, u32, ...);
extern void OSDumpContext(void *);
extern void PPCHalt(void);

void __DBExceptionDestinationAux(void) {
    u32 context = *(u32 *)0xc0; /* fzgx-allow: A2 zero-page context pointer */
    void *exception_context = (void *)(context + 0x80000000);
    u8 pad[1] __attribute__((aligned(8)));

    OSReport(lbl_80123E10, context);
    OSDumpContext(exception_context);
    PPCHalt();
}
