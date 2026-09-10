#include "types.h"

typedef struct {
    s32 counter;
    s32 field_04;
    s32 field_08;
    s32 field_0c;
    s32 field_10;
    u8 field_14[0x20];
    u8 field_34[0x100];
    s32 field_134;
    u8 field_138[0x400];
    u8 field_538[0x440];
} State;

extern u32 lbl_80186630[4];
extern void ADXT_DestroyAll(void);
extern void *memset(void *, int, u32);

void fn_8004F6B0(void) {
    State *state = (State *)&lbl_80186630;

    if (--state->counter == 0) {
        ADXT_DestroyAll();
        state->field_04 = -1;
        state->field_08 = 0;
        state->field_0c = 0;
        state->field_134 = 0;
        state->field_10 = 0;
        memset(state->field_14, 0, 0x20);
        memset(state->field_34, 0xff, 0x100);
        memset(state->field_138, 0, 0x400);
        memset(state->field_538, 0, 0x440);
    }
}
