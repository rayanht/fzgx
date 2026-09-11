#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 lbl_801A6834;
extern void SISetCommand(u32 channel, u32 command);
extern void SITransferCommands(void);
extern void OSRestoreInterrupts(u32 state);

void fn_800139E8(u32 channel, u32 command, s32 repeat) {
    u32 state;
    u32 value;
    u32 mask;

    mask = command & 0x600;
    if (repeat <= -0x80) {
        value = 0;
    } else if (repeat >= 0x80) {
        value = 0x100;
    } else {
        value = repeat + 0x80;
    }
    value |= mask;
    value &= 0x7ff;

    state = OSDisableInterrupts();
    if (lbl_801A6834 & (0x80000000u >> channel)) {
        value |= 0x300000;
        SISetCommand(channel, value);
        SITransferCommands();
    }
    OSRestoreInterrupts(state);
}
