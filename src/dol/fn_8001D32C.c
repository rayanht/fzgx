#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 lbl_801A697C;
extern u32 SIGetType(u32 channel);
extern u32 lbl_801A64C0;
extern u32 lbl_801A64BC;
extern void SISetCommand(u32 channel, u32 command);
extern void SITransferCommands(void);
extern void OSRestoreInterrupts(u32 state);

void fn_8001D32C(u32 *commands) {
    u32 state;
    s32 channel;
    s32 transferred;

    state = OSDisableInterrupts();
    transferred = 0;
    for (channel = 0; channel < 4; channel++, commands++) {
        if (lbl_801A697C & (0x80000000u >> channel)) {
            if ((SIGetType(channel) & 0x20000000u) == 0) {
                u32 command = *commands;
                if (lbl_801A64C0 < 2 && command == 2) {
                    command = 0;
                }
                SISetCommand(channel, lbl_801A64BC | 0x400000 | (command & 3));
                transferred = 1;
            }
        }
    }
    if (transferred) {
        SITransferCommands();
    }
    OSRestoreInterrupts(state);
}
