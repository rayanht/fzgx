#include "types.h"

struct fn_80072864_lbl_801A6D38_T {
    u8 pad_0[0x18];
    u32 unk_18;
};

extern struct fn_80072864_lbl_801A6D38_T *lbl_801A6D38;
extern u32 fn_80034890(u32);

void fn_80072864(u32 arg0) {
    u32 v0;
    u32 t0;
    v0 = arg0;
    if ((s32)arg0 != (s32)lbl_801A6D38->unk_18) {
    t0 = fn_80034890(v0);
    v0 = t0;
    v0 = (u32)lbl_801A6D38;
    *(u32 *)((u8 *)v0 + 24) = arg0;
    }
}
