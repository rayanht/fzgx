#include "types.h"

extern int fn_12_3A36C(void *);
extern char lbl_12_rodata_114C[50];
extern void MWSFSVM_Error(const char *, ...);
extern int fn_12_3A7D8(void *);
extern int fn_12_2A508(int);

int fn_12_338C4(void *self) {
    if (fn_12_3A36C(self) == 0) {
        MWSFSVM_Error(lbl_12_rodata_114C);
        return 0;
    }
    return fn_12_2A508(fn_12_3A7D8(self));
}
