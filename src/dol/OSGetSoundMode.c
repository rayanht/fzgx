#include "types.h"

typedef struct {
    u8 _pad00[0x13];
    u8 flags;
    u8 _pad14[0x30];
    s32 interrupt_state;
    s32 sound_mode_init;
} Scb;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void UnlockSram(u32, u32);
extern Scb Scb_8015BFC0;

int OSGetSoundMode(void) {
    Scb *scb;
    u32 interrupts;
    s32 *mode;
    u8 pad[16];
    int result;

    scb = &Scb_8015BFC0;
    interrupts = OSDisableInterrupts();
    mode = &scb->sound_mode_init;
    if (*mode != 0) {
        OSRestoreInterrupts(interrupts);
        scb = 0;
    } else {
        scb->interrupt_state = interrupts;
        *mode = 1;
    }
    if ((scb->flags & 4) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    UnlockSram(0, 0);
    return result;
}
