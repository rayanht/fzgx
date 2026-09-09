#include "types.h"

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);

typedef struct Fn80023228Work {
    u8 _pad0[0x1c];
    u32 flags;
    u8 _pad1[0x158];
    s16 field_178;
    s16 field_17a;
} Fn80023228Work;

void fn_80023228(Fn80023228Work *work, s16 field_178, s16 field_17a) {
    u32 interrupts;
    interrupts = OSDisableInterrupts();
    work->field_178 = field_178;
    work->field_17a = field_17a;
    work->flags = work->flags | 0x40;
    OSRestoreInterrupts(interrupts);
}
