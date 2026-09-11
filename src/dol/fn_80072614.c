#include "dolphin/hw_regs.h"
#include "types.h"

struct fn_80072614_lbl_8019E250 {
    u8 pad_0[0x34];
    u32 unk_34;
};

extern struct fn_80072614_lbl_8019E250 lbl_8019E250;

#pragma opt_dead_assignments off
void fn_80072614(u32 *arg0) {
    u32 value;
    u32 fifo;
    struct fn_80072614_lbl_8019E250 *p;

    p = &lbl_8019E250;
    value = *arg0;
    fifo = GX_FIFO_BASE;  /* fzgx-allow: A1,A2 unnamed OS/hardware memory */
    if (p->unk_34 == value) {
        return;
    }
    p->unk_34 = value;
    *(volatile u8 *)fifo = 16; /* Hardware access must remain ordered. */
    *(volatile u32 *)fifo = 0x100a; /* Hardware access must remain ordered. */
    *(volatile u32 *)fifo = value; /* Hardware access must remain ordered. */
}
#pragma opt_dead_assignments reset

