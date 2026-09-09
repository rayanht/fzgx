#include <dolphin/exi.h>
#include <dolphin/os.h>
#include <dolphin/os/OSRtc.h>

SramControlBlock Scb_8015BFC0 __attribute__((aligned(32)));

static inline BOOL ReadSram(void *buffer) {
    BOOL err;
    u32 cmd;
    DCInvalidateRange(buffer, 64);
    if (!EXILock(0, 1, 0)) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000000 | 0x00000100;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, ((void *)0));
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, 64, 0, ((void *)0));
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

void __OSInitSram(void) {
    Scb_8015BFC0.locked = Scb_8015BFC0.enabled = 0;
    Scb_8015BFC0.sync = ReadSram(Scb_8015BFC0.sram);
    Scb_8015BFC0.offset = 64;
}
