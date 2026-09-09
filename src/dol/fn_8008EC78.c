#include "types.h"

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern volatile u32 *lbl_801A6678; /* shared interrupt state is hardware-updated */
struct ExiRegs {
    u32 pad[10];
    u32 csr;
};

extern volatile struct ExiRegs __EXIRegs; /* memory-mapped hardware register block */

u32 fn_8008EC78(void) {
    u32 interrupts;
    volatile u32 *state; /* shared state may change outside this function */
    u32 value;
    volatile u32 *flags; /* access the shared flag field exactly as emitted */

    interrupts = OSDisableInterrupts();
    state = lbl_801A6678;
    value = state[3];
    flags = &state[3];
    if ((value & 4) == 0) {
        OSRestoreInterrupts(interrupts);
        return 0;
    }

    value = *flags;
    value = *flags;
    value &= ~4;
    *flags = value;
    value = __EXIRegs.csr;
    value &= 0x405;
    *(volatile u32 *)((u8 *)&__EXIRegs + 0x28) = value; /* hardware CSR write */
    OSRestoreInterrupts(interrupts);
    return 1;
}
