#include <types.h>
#include <dolphin/os/OSInterrupt.h>

extern u32 CurrTvMode_801A6964;

u32 VIGetTvFormat(void) {
    u32 fmt;
    int interrupt;
    interrupt = OSDisableInterrupts();
    switch (CurrTvMode_801A6964) {
    case 0:
    case 3:
    case 6:
        fmt = 0;
        break;
    case 1:
    case 4:
        fmt = 1;
        break;
    case 5:
    case 2:
        fmt = CurrTvMode_801A6964;
        break;
    }
    OSRestoreInterrupts(interrupt);
    return fmt;
}
