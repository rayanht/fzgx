#include "types.h"

extern u8 lbl_8015CC10[160];
extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern void fn_800135CC(u32, u32);
extern void SIGetTypeAsync(u32, void (*)(u32, u32));

struct SIEntry {
    u8 pad0[12];
    u32 callback;
    u32 type;
    u8 pad18[16];
    u32 value;
};

u32 fn_800136E8(u32 channel, u32 arg1, u32 arg2, u32 arg3) {
    u32 interrupts;
    struct SIEntry *entry;

    entry = (struct SIEntry *)lbl_8015CC10 + channel;
    interrupts = OSDisableInterrupts();
    entry->value = arg3;
    entry->callback = arg1;
    entry->type = arg2;
    SIGetTypeAsync(channel, (void (*)(u32, u32))fn_800135CC);
    OSRestoreInterrupts(interrupts);
    return 0;
}
