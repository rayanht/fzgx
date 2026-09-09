#ifndef DOLPHIN_SI_H
#define DOLPHIN_SI_H
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>

typedef void (*SICallback)(s32 chan, u32 sr, OSContext *context);

typedef void (*SITypeAndStatusCallback)(s32 chan, u32 type);

u32 SIDecodeType(u32 type);
u32 SIDisablePolling(u32 poll);
u32 SIEnablePolling(u32 poll);
BOOL SIEnablePollingInterrupt(BOOL enable);
BOOL SIGetResponse(s32 chan, void *data);
BOOL SIGetResponseRaw(s32 chan);
u32 SIGetTypeAsync(s32 chan, SITypeAndStatusCallback callback);
BOOL SIRegisterPollingHandler(__OSInterruptHandler handler);
u32 SISetXY(u32 x, u32 y);
BOOL SITransfer(s32 chan, void *output, u32 outputBytes, void *input, u32 inputBytes,
                SICallback callback, OSTime delay);
void SITransferCommands(void);
BOOL SIUnregisterPollingHandler(__OSInterruptHandler handler);
#endif
