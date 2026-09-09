#include "types.h"

struct OSGetProgressiveMode_Scb_8015BFC0 {
    u8 pad_0[0x13];
    u8 flags;
    u8 pad_14[0x30];
    u32 unk_44;
    u32 unk_48;
};

extern struct OSGetProgressiveMode_Scb_8015BFC0 Scb_8015BFC0;
extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern u32 UnlockSram(u32, u32);

u32 OSGetProgressiveMode(void) {
    struct OSGetProgressiveMode_Scb_8015BFC0 *scb;
    u32 interrupts;
    u32 status;
    u32 *state;
    u32 progressive_mode;

    scb = &Scb_8015BFC0;
    interrupts = OSDisableInterrupts();
    status = scb->unk_48;
    state = &scb->unk_48;
    if ((s32)status != 0) {
        OSRestoreInterrupts(interrupts);
        scb = 0;
    } else {
        scb->unk_44 = interrupts;
        *state = 1;
    }
    progressive_mode = (scb->flags >> 7) & 1;
    UnlockSram(0, 0);
    return progressive_mode;
}
