#include "types.h"

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *value_a8;
} MovieModuleState;

extern int fn_12_3A36C(MovieModuleState *self);
extern char lbl_12_rodata_1C28[49];
extern void MWSFSVM_Error(const char *fmt, ...);
extern char lbl_12_rodata_1C5C[48];
extern void fn_12_35B08(MovieModuleState *self, void *arg, void *out);
extern void fn_12_147C(void *value, void *arg, void *extra);

void fn_12_359B0(MovieModuleState *self, void *arg, void *extra) {
    u8 local[0x80];
    void *value_a8;

    if (fn_12_3A36C(self) == 0) {
        MWSFSVM_Error(lbl_12_rodata_1C28);
    } else if (*(void **)arg == 0) {
        MWSFSVM_Error(lbl_12_rodata_1C5C);
    } else {
        value_a8 = self->value_a8;
        fn_12_35B08(self, arg, local);
        fn_12_147C(value_a8, local, extra);
    }
}
