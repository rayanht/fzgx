#include "types.h"

struct fn_80074D28_Data {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
};

extern struct fn_80074D28_Data lbl_8019F14C;
extern void lbl_8006D668(struct fn_80074D28_Data *);

void fn_80074D28(struct fn_80074D28_Data *src) {
    lbl_8019F14C = *src;
    lbl_8006D668(&lbl_8019F14C);
}
