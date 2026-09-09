#include "types.h"

typedef struct OSAlarm OSAlarm;

struct OSAlarm {
    u8 _pad0[0x18];
    u32 field_18;
    u32 field_1c;
};

extern u32 OSDisableInterrupts(void);
extern u64 __OSGetSystemTime(void);
extern void InsertAlarm(OSAlarm* alarm, u32 now_lo, u64 time, void* arg);
extern void OSRestoreInterrupts(u32 level);

void OSSetAlarm(OSAlarm* alarm, u32 unused, u64 time, void* arg) {
    u32 level;
    u64 now;
    u64 sum;

    level = OSDisableInterrupts();
    alarm->field_1c = 0;
    alarm->field_18 = 0;
    now = __OSGetSystemTime();
    sum = time + now;
    InsertAlarm(alarm, (u32)now, sum, arg);
    OSRestoreInterrupts(level);
}
