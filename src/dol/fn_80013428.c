#include "types.h"

extern u8 lbl_8015CC10[160];
extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern void fn_800133DC(u32, u32);
extern void fn_800133E0(u32);
extern u32 fn_800136E8(u32, u32, u32, u32);

struct SIEntry2 {
    u8 status;
    u8 pad0[19];
    u32 callback;
    u8 pad1[16];
};

s32 fn_80013428(u32 channel, u32 callback) {
    u32 interrupts;
    u32 unused[2];
    s32 result;
    struct SIEntry2 *entry;

    entry = (struct SIEntry2 *)lbl_8015CC10 + channel;
    result = callback != 0 ? (s32)callback : (s32)(u32)fn_800133DC;
    interrupts = OSDisableInterrupts();
    if (entry->callback != 0) {
        result = -2;
    } else {
        entry->callback = (u32)result;
        result = 0;
    }
    OSRestoreInterrupts(interrupts);
    if (result != 0) {
        return result;
    }
    entry->status = 0xff;
    fn_800136E8(channel, 1, 3, (u32)fn_800133E0);
}
