#include "types.h"

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *value_a8;
} MovieModuleState;

extern int fn_12_3A36C(MovieModuleState *, void *, void *);
extern void MWSFSVM_Error(const char *, ...);
extern void fn_12_35B08(MovieModuleState *, void *, void *);
extern void fn_12_D38(void *, void *, void *);
extern char lbl_12_rodata_1A30[47];
extern char lbl_12_rodata_1A60[46];

void fn_12_357BC(MovieModuleState *self, void *arg, void *value) {
    u8 local[0x88];
    void *movie;

    if (fn_12_3A36C(self, arg, value) == 0) {
        MWSFSVM_Error(lbl_12_rodata_1A30);
    } else if (*(void **)arg == 0) {
        MWSFSVM_Error(lbl_12_rodata_1A60);
    } else {
        movie = self->value_a8;
        fn_12_35B08(self, arg, local);
        fn_12_D38(movie, local, value);
    }
}
