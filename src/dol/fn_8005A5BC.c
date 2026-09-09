#include "types.h"

typedef void (*fn_8005A5BC_Fn0)(u32, u32);
struct fn_8005A5BC_lbl_80190B70 {
    u32 unk_0;
    u32 unk_4;
    char buffer[1];
};

extern u32 lbl_80190B70[];
extern void strncpy(void *, void *, int);

void fn_8005A5BC(u32 arg0) {
    struct fn_8005A5BC_lbl_80190B70 *p_lbl_80190B70;

    p_lbl_80190B70 = (struct fn_8005A5BC_lbl_80190B70 *)&lbl_80190B70;
    strncpy((void *)((u8 *)p_lbl_80190B70 + 8), (void *)arg0, 255);
    if (p_lbl_80190B70->unk_0 != 0) {
        ((fn_8005A5BC_Fn0)p_lbl_80190B70->unk_0)(
            p_lbl_80190B70->unk_4, (u32)((u8 *)(u32)p_lbl_80190B70 + 8));
    }
}
