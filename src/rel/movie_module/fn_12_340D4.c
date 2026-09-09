#include "types.h"

typedef struct MovieModule {
    u8 pad_00[0x54];
    void *field_54;
} MovieModule;

extern int fn_12_3A36C(MovieModule *, void *);
extern char lbl_12_rodata_12B0[46];
extern void MWSFSVM_Error(char *, ...);

void fn_12_340D4(MovieModule *self, void *value) {
    if (fn_12_3A36C(self, value) == 0) {
        MWSFSVM_Error(lbl_12_rodata_12B0);
    } else {
        self->field_54 = value;
    }
}
