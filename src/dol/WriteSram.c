#include <dolphin/exi.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>

void WriteSramCallback(s32 chan, OSContext *context);

BOOL WriteSram(void *buffer, u32 offset, u32 size) {
    BOOL err;
    u32 cmd;
    if (!EXILock(0, 1, WriteSramCallback)) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    offset <<= 6;
    cmd = 0xa0000000 | 0x00000100 + offset;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, ((void *)0));
    err |= !EXISync(0);
    err |= !EXIImmEx(0, buffer, (s32)size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}
