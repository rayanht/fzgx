#include "types.h"

typedef struct MovieObject {
    u8 pad04[0x4];
    s32 state;
    u8 pad08[0x58];
    s32 value;
} MovieObject;

typedef struct MovieManager {
    u8 pad24[0x24];
    s32 value;
} MovieManager;

extern s32 lbl_12_bss_1B9DC[52];
extern u8 lbl_12_rodata_2D5C[180];
extern void MWSFSVM_Error(const u8 *message, ...);
extern MovieManager *fn_12_38DBC(void);
extern u32 fn_12_3A9A0(MovieObject *self);

u32 fn_12_3AA58(MovieObject *self) {
    if (lbl_12_bss_1B9DC[0] != 1) {
        return 0;
    }
    if (self == 0) {
        MWSFSVM_Error(lbl_12_rodata_2D5C);
        return 0;
    }
    if (self->state != 1) {
        return 0;
    }
    if (self->value == 1) {
        return 0;
    }
    if (fn_12_38DBC()->value == 1) {
        return 0;
    }
    return fn_12_3A9A0(self);
}
