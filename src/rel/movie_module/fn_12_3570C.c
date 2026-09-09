#include "types.h"

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *movie;
    u8 pad_ac[0x3c];
    void *value_e8;
} MovieModuleState;

extern u8 lbl_12_rodata_15D0[];
extern int fn_12_3A36C(void);
extern void MWSFSVM_Error(const char *, ...);
extern void fn_12_8DC(void *, int);

void fn_12_3570C(MovieModuleState *self, int mode) {
    const u8 *text = lbl_12_rodata_15D0;

    if (fn_12_3A36C() == 0) {
        MWSFSVM_Error((const char *)(text + 0x398));
    } else if (self->value_e8 == 0 && mode == 0x101) {
        MWSFSVM_Error((const char *)(text + 0x3cc));
    } else if (self->value_e8 == 0 && mode == 0) {
        MWSFSVM_Error((const char *)(text + 0x414));
    } else {
        fn_12_8DC(self->movie, mode);
    }
}
