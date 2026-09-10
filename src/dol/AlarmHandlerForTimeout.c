#include <types.h>
#include <dolphin/os.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSContext.h>

typedef void (*DVDLowCallback)(u32 intType);

extern DVDLowCallback Callback_801A6860;

void AlarmHandlerForTimeout(OSAlarm *alarm, OSContext *context) {
    OSContext tmpContext;
    DVDLowCallback callback;
    __OSMaskInterrupts(0x400);
    OSClearContext(&tmpContext);
    OSSetCurrentContext(&tmpContext);
    callback = Callback_801A6860;
    Callback_801A6860 = 0;
    if (callback != 0) {
        callback(0x10);
    }
    OSClearContext(&tmpContext);
    OSSetCurrentContext(context);
}
