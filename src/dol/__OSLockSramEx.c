#include "types.h"

struct OSLockSramEx_Scb_8015BFC0 {
    u8 pad_0[0x44];
    u32 unk_44;
    u32 unk_48;
};

extern struct OSLockSramEx_Scb_8015BFC0 Scb_8015BFC0;
extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);

void *__OSLockSramEx(void) {
    struct OSLockSramEx_Scb_8015BFC0 *p_Scb_8015BFC0;
    u32 interrupts;
    s32 *lock;

    p_Scb_8015BFC0 = (struct OSLockSramEx_Scb_8015BFC0 *)&Scb_8015BFC0;
    interrupts = OSDisableInterrupts();
    lock = (s32 *)&p_Scb_8015BFC0->unk_48;
    if (*lock != 0) {
        OSRestoreInterrupts(interrupts);
        return (void *)0;
    }
    p_Scb_8015BFC0->unk_44 = interrupts;
    *lock = 1;
    return (void *)((u8 *)p_Scb_8015BFC0 + 0x14);
}
