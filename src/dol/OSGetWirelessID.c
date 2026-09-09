#include <dolphin/os.h>
#include <dolphin/os/OSRtc.h>

struct OSRtcBss {
    SramControlBlock Scb;
};

OSSramEx *__OSLockSramEx();

extern struct OSRtcBss Scb_8015BFC0;

static inline void *LockSram(u32 offset) {
    BOOL *lockedField;

    struct OSRtcBss *bss = &Scb_8015BFC0;

    BOOL enabled;
    enabled = OSDisableInterrupts();
    lockedField = &(bss->Scb).locked;
    if ((*lockedField) != 0) {
        OSRestoreInterrupts(enabled);
        return ((void *)0);
    }
    (bss->Scb).enabled = enabled;
    (*lockedField) = 1;
    return (bss->Scb).sram + offset;
}

static inline OSSramEx *__OSLockSramEx() { return LockSram(sizeof(OSSram)); }

BOOL UnlockSram(BOOL commit, u32 offset);

static inline BOOL __OSUnlockSramEx(BOOL commit) { return UnlockSram(commit, sizeof(OSSram)); }

u16 OSGetWirelessID(s32 channel) {
    OSSramEx *sram;
    u16 id;
    sram = __OSLockSramEx();
    id = sram->wirelessPadID[channel];
    __OSUnlockSramEx(0);
    return id;
}
