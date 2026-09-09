#ifndef DOLPHIN_EXI_H
#define DOLPHIN_EXI_H
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

typedef void (*EXICallback)(s32 chan, OSContext *context);

BOOL EXIAttach(s32 chan, EXICallback extCallback);
u32 EXIClearInterrupts(s32 chan, BOOL exi, BOOL tc, BOOL ext);
BOOL EXIDeselect(s32 chan);
BOOL EXIDetach(s32 chan);
BOOL EXIDma(s32 chan, void *buf, s32 len, u32 type, EXICallback callback);
u32 EXIGetState(s32 chan);
BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, EXICallback callback);
BOOL EXIImmEx(s32 chan, void *buf, s32 len, u32 mode);
BOOL EXILock(s32 chan, u32 dev, EXICallback unlockedCallback);
BOOL EXIProbe(s32 chan);
s32 EXIProbeEx(s32 chan);
BOOL EXISelect(s32 chan, u32 dev, u32 freq);
EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback);
BOOL EXISync(s32 chan);
BOOL EXIUnlock(s32 chan);
#endif
