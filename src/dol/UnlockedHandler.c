#include <dolphin/exi/EXIPriv.h>
#include <dolphin/os/OSContext.h>
#pragma scheduling off

s32 EXIGetID(s32 chan, u32 dev, u32 *id);

void UnlockedHandler(s32 chan, OSContext *context) {
    u32 id;
    EXIGetID(chan, 0, &id);
}
