#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern u64 __OSTimeToSystemTime(u64);
extern void InsertAlarm(void *, u64, u32);

struct OSSetPeriodicAlarm_Alarm {
    u32 unk_0[6];
    u32 unk_18;
    u32 unk_1c;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
};

void OSSetPeriodicAlarm(struct OSSetPeriodicAlarm_Alarm *arg0, u64 start, u64 period, u32 arg6) {
    u32 interrupts;
    u64 system_time;

    interrupts = OSDisableInterrupts();
    *(u64 *)&arg0->unk_18 = period;
    system_time = __OSTimeToSystemTime(start);
    *(u64 *)&arg0->unk_20 = system_time;
    InsertAlarm(arg0, (u64)0, arg6);
    OSRestoreInterrupts(interrupts);
}
