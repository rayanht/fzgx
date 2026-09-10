#include "types.h"

extern const f64 lbl_801A71C0;
extern u8 lbl_80178BF0[40];

extern u64 OSGetTime(void);
extern void fn_8003E344(void);
extern void OSSetPeriodicAlarm(void *, u64, u32, u32, void (*)(void));

void fn_8003E8CC(f32 arg0) {
    u32 v0;
    u32 period;

    v0 = *(u32 *)0x800000F8;  /* fzgx-allow: A1,A2 unnamed OS/hardware memory */
    period = (u32)(arg0 * (f32)((v0 >> 2) / 1000));
    OSSetPeriodicAlarm(lbl_80178BF0, OSGetTime(), 0, period, fn_8003E344);
}
