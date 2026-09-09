#include "types.h"

extern int fn_12_3A36C(void *);
extern char lbl_12_rodata_1180[136];
extern void MWSFSVM_Error(const char *, ...);
extern int fn_12_3A7D8(void *);
extern int fn_12_2B1E8(int, s32);

typedef struct MovieState {
    u8 field_00[0x78];
    s32 field_78;
    s32 field_7C;
    s32 field_80;
} MovieState;

void fn_12_3391C(MovieState *self) {
    s32 field_78;
    s32 field_7C;
    s32 field_80;
    int result;

    if (fn_12_3A36C(self) == 0) {
        MWSFSVM_Error(lbl_12_rodata_1180);
        return;
    }

    field_78 = self->field_78;
    field_7C = self->field_7C;
    field_80 = self->field_80;
    result = fn_12_3A7D8(self);
    if (field_7C > field_80) {
        fn_12_2B1E8(result, field_78);
        self->field_80 = self->field_80 + 1;
        self->field_7C = self->field_80;
    }
}
