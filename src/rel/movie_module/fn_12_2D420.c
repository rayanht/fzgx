#include "types.h"

typedef struct MovieModuleSubState {
    u8 pad_0[0xda4];
    s32 field_da4;
    s32 field_da8;
} MovieModuleSubState;

typedef struct MovieModuleState {
    u8 pad_0[0x2908];
    MovieModuleSubState *field_2908;
} MovieModuleState;

void fn_12_2D420(MovieModuleState *arg0, u32 arg1, u32 arg2) {
    MovieModuleSubState *state;

    state = arg0->field_2908;
    if (state == 0) {
        return;
    }
    if (state->field_da4 < 0) {
        state->field_da4 = arg1;
    }
    if (state->field_da8 >= 0) {
        return;
    }
    state->field_da8 = arg2;
}
