#include "types.h"

extern void OSDisableInterrupts(void);
// The VI reset register is a hardware MMIO halfword.
extern volatile u32 __VIRegs[];
extern void ICFlashInvalidate(void);
extern void Reset_8000EEF4(s32 reset_code);

void __OSDoHotReset(s32 reset_code) {
    OSDisableInterrupts();
    // Volatile prevents the compiler from removing the MMIO reset write.
    ((volatile u16 *)__VIRegs)[1] = 0;
    ICFlashInvalidate();
    Reset_8000EEF4(reset_code << 3);
}
