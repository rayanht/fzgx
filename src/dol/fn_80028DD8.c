#include "types.h"

extern u32 OSDisableInterrupts(void);
extern void fn_800296F0(void *);
extern void OSRestoreInterrupts(u32);
extern u32 lbl_801A6BB8;
extern void __DSP_boot_task(void *);

typedef struct {
    u32 field0;
    u8 pad04[4];
    u32 field8;
} Fn80028DD8Data;

void *fn_80028DD8(Fn80028DD8Data *data) {
    u32 interrupts;
    interrupts = OSDisableInterrupts();
    fn_800296F0(data);
    data->field0 = 0;
    data->field8 = 1;
    OSRestoreInterrupts(interrupts);
    if (data == (Fn80028DD8Data *)lbl_801A6BB8) {
        __DSP_boot_task(data);
    }
    return data;
}
