#ifndef DOLPHIN_DVD_SHARED_STATE_H
#define DOLPHIN_DVD_SHARED_STATE_H

#include <dolphin/dvd.h>
#include <dolphin/os/OSAlarm.h>

typedef struct DVDLowBuffer {
    void *addr;
    u32 length;
    u32 offset;
} DVDLowBuffer;

/* These objects share the retail section bases used by OSInit and DVDLow. */
extern DVDCommandBlock __OSDriveBlock;
extern OSAlarm __DVDLowAlarmForWA;
extern DVDLowBuffer __DVDLowPrev;
extern DVDLowBuffer __DVDLowCurr;

#endif
