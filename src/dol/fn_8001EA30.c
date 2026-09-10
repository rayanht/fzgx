#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*ARCallback)(void);

vu16 __DSPRegs[32] : FZGX_ADDR___DSPRegs;

void OSRegisterVersion(const char *id);

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler);

extern const char *lbl_801A64D8;

extern ARCallback lbl_801A69E0;

extern u32 lbl_801A69F0;

extern u32 lbl_801A69F4;

extern u32 *lbl_801A69F8;

// Hardware or OS state can change asynchronously.
extern volatile BOOL lbl_801A69FC; // fzgx-allow: S2 SDK asynchronous state

void fn_8001EAF4(__OSInterrupt interrupt, OSContext *context);

void fn_8001EB6C(void);

void fn_8001EAF4(__OSInterrupt interrupt, OSContext *context);

void fn_8001EB6C(void);

u32 fn_8001EA30(u32 *stack_index_addr, u32 num_entries) {
    BOOL old;
    u16 refresh;
    if (lbl_801A69FC == 1) {
        return 0x4000;
    }
    OSRegisterVersion(lbl_801A64D8);
    old = OSDisableInterrupts();
    lbl_801A69E0 = 0;
    __OSSetInterruptHandler(6, fn_8001EAF4);
    __OSUnmaskInterrupts((0x80000000u >> (6)));
    lbl_801A69F0 = 0x4000;
    lbl_801A69F4 = num_entries;
    lbl_801A69F8 = stack_index_addr;
    refresh = (u16)(__DSPRegs[13] & 0x000000ff);
    __DSPRegs[13] = (u16)((__DSPRegs[13] & ~0x000000ff) | (refresh & 0x000000ff));
    fn_8001EB6C();
    lbl_801A69FC = 1;
    OSRestoreInterrupts(old);
    return lbl_801A69F0;
}
