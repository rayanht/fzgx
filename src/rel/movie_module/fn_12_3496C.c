#include "types.h"

struct MovieModule {
    u8 pad_00[0x4c];
    void *field_4c;
};

extern int fn_12_3A36C(struct MovieModule *, void *);
extern const u8 lbl_12_rodata_1420[];
extern void MWSFSVM_Error(const u8 *, ...);
extern void fn_80056730(void *, void *);

void fn_12_3496C(struct MovieModule *self, void *arg) {
    if (fn_12_3A36C(self, arg) == 0) {
        MWSFSVM_Error(lbl_12_rodata_1420);
    } else {
        fn_80056730(self->field_4c, arg);
    }
}
