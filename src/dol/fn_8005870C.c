#include "types.h"

struct fn_8005870C_lbl_8018F2A8 {
    u32 unk_0;
};

extern struct fn_8005870C_lbl_8018F2A8 lbl_8018F2A8[];
extern u32 lbl_8018F2AC[];
extern u32 memset(u32, u32, u32);

void fn_8005870C(void) {
    struct fn_8005870C_lbl_8018F2A8 *p;

    p = (struct fn_8005870C_lbl_8018F2A8 *)&lbl_8018F2A8;
    if (--p->unk_0 == 0) {
        memset((u32)&lbl_8018F2AC, 0, 3072);
    }
}
