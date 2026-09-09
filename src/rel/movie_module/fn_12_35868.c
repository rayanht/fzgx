#include "types.h"

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *value_a8;
} MovieModuleState;

extern int fn_12_3A36C(MovieModuleState *self);
extern char lbl_12_rodata_1A90[47];
extern void MWSFSVM_Error(...);
extern u8 lbl_12_rodata_1AC0[256];
extern void fn_12_35B08(MovieModuleState *self, void *movie, void *result);
extern void fn_12_D60(void *value, void *result, void *arg);

void fn_12_35868(MovieModuleState *self, void *movie, void *arg) {
    u8 result[0x80];

    if (fn_12_3A36C(self) == 0) {
        MWSFSVM_Error(lbl_12_rodata_1A90);
    } else if (*(void **)movie == 0) {
        MWSFSVM_Error((const char *)lbl_12_rodata_1AC0);
    } else {
        void *value = self->value_a8;
        fn_12_35B08(self, movie, result);
        fn_12_D60(value, result, arg);
    }
}
