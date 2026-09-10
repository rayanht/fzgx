#include "types.h"

typedef struct MovieModuleState {
    u8 pad_2c[0x2c];
    s32 state;
    u8 pad_30[0xbc];
    void *resource;
    void *resource_end;
} MovieModuleState;

extern u8 lbl_12_rodata_17D0[252];
extern void *fn_80058498(void *resource, void *resource_end, s32 arg2);
extern void MWSFSVM_Error(u8 *message, ...);
extern void mwSfdDestroy(MovieModuleState *self);

u32 fn_12_354BC(MovieModuleState *self) {
    s32 valid;

    if (self->state == 0 || self->state == 0x101) {
        valid = 1;
    } else {
        valid = 0;
    }

    if (valid == 0) {
        return 0;
    }

    if (fn_80058498(self->resource, self->resource_end, 0) == 0) {
        MWSFSVM_Error(lbl_12_rodata_17D0);
        mwSfdDestroy(self);
        return 0;
    }
}
