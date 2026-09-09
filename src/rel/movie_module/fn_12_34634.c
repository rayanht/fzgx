#include "types.h"

struct MovieModule {
    u8 pad_00[0x70];
    char field_70;
    char field_71;
};

extern int fn_12_3A36C(struct MovieModule *);
extern const u8 lbl_12_rodata_1480[];
extern const char lbl_12_rodata_12E0[];
extern void MWSFSVM_Error(const char *, ...);

void fn_12_34634(struct MovieModule *self) {
    if (fn_12_3A36C(self) == 0) {
        MWSFSVM_Error((const char *)lbl_12_rodata_1480);
    } else {
        if (fn_12_3A36C(self) == 0) {
            MWSFSVM_Error(lbl_12_rodata_12E0);
        } else {
            if (self->field_70 == 1) {
                self->field_71 = 1;
            }
            self->field_70 = 0;
        }
    }
}
