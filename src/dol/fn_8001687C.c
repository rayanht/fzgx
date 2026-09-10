#include <types.h>
#include <dolphin/dvd.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSTime.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef void (*DVDLowCallback)(u32 intType);

void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);

void OSCreateAlarm(OSAlarm *alarm);

u32 __OSBusClock : FZGX_ADDR___OSBusClock;

vu32 __DIRegs[16] : FZGX_ADDR___DIRegs;

// Hardware or OS state can change asynchronously.
extern volatile BOOL StopAtNextInt_801A6858; // fzgx-allow: S2 SDK asynchronous state

extern DVDLowCallback Callback_801A6860;

extern OSAlarm AlarmForTimeout_8015CDD8;

void AlarmHandlerForTimeout(OSAlarm *alarm, OSContext *context);

static inline void SetTimeoutAlarm(OSTime timeout) {
    OSCreateAlarm(&AlarmForTimeout_8015CDD8);
    OSSetAlarm(&AlarmForTimeout_8015CDD8, timeout, AlarmHandlerForTimeout);
}

BOOL fn_8001687C(DVDDiskID *diskID, DVDLowCallback callback) {
    StopAtNextInt_801A6858 = 0;
    Callback_801A6860 = callback;
    __DIRegs[2] = 0xa8000040;
    __DIRegs[3] = 0;
    __DIRegs[4] = sizeof(DVDDiskID);
    __DIRegs[5] = (u32)diskID;
    __DIRegs[6] = sizeof(DVDDiskID);
    __DIRegs[7] = 3;
    SetTimeoutAlarm(((10) * ((u32)__OSBusClock / 4)));
    return 1;
}
