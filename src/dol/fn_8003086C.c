#include "types.h"
#include "dolphin/hw_regs.h"
#include "dolphin/os/OSTime.h"

extern OSTime OSGetTime(void);

extern u32 __memReg;
extern u32 __cpReg;
extern u32 gx;
extern u32 lbl_801A6BD8;
extern s64 lbl_801A6BE0;
extern u32 lbl_801A6BE8;

extern u32 fn_80009FF4(void);
extern u32 fn_800321D8(u32);
extern u32 fn_80033EB0(void);
extern u32 fn_80034378(u32);
extern u32 fn_80034444(u32);

#pragma peephole off
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_dead_assignments off
#pragma opt_loop_invariants off
s32 fn_8003086C(s32 arg0) {
    u32 prev;
    u32 hi;
    u32 lo;
    volatile u16 *p50;  /* fzgx-allow: S2 memory-mapped register */
    volatile u16 *p46;  /* fzgx-allow: S2 memory-mapped register */
    OSTime now;
    u32 v;
    s64 diff;

    if (arg0 == 0) {
        if (lbl_801A6BE8 == 0) {
            p46 = (volatile u16 *)(__memReg + 0x4e);  /* fzgx-allow: S2 memory-mapped register */
            p50 = (volatile u16 *)(__memReg + 0x50);  /* fzgx-allow: S2 memory-mapped register */
            hi = *p46;
            do {
                prev = hi;
                hi = *p46;
                lo = *p50;
            } while (hi != prev);
            lbl_801A6BD8 = (hi << 16) | lo;
            now = OSGetTime();
            lbl_801A6BE0 = now;
            lbl_801A6BE8 = 1;
            return 0;
        }
        now = OSGetTime();
        p46 = (volatile u16 *)(__memReg + 0x4e);  /* fzgx-allow: S2 memory-mapped register */
        p50 = (volatile u16 *)(__memReg + 0x50);  /* fzgx-allow: S2 memory-mapped register */
        hi = *p46;
        do {
            prev = hi;
            hi = *p46;
            lo = *p50;
        } while (hi != prev);
        v = (hi << 16) | lo;
        if ((now - lbl_801A6BE0) < 10) {
            return 0;
        }
        if (v != lbl_801A6BD8) {
            lbl_801A6BE0 = now;
            lbl_801A6BD8 = v;
            return 0;
        }
    } else {
        fn_800321D8(0);
        fn_80034378(0);
        fn_80034444(0);
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        *(volatile u32 *)GX_FIFO_BASE = 0;  /* fzgx-allow: A2,S2 GX write-gather FIFO (hw_regs.h) */
        fn_80009FF4();
        *(volatile u16 *)(__cpReg + 2) = 0; /* hardware register */  /* fzgx-allow: S2 memory-mapped register */
        *(volatile u16 *)(__cpReg + 4) = 3; /* hardware register */  /* fzgx-allow: S2 memory-mapped register */
        *(u8 *)(gx + 0x4f2) = 1;
        fn_80033EB0();
    }
    return 1;
}
#pragma opt_loop_invariants reset

#pragma opt_dead_assignments reset

#pragma opt_propagation reset

#pragma opt_common_subs reset

#pragma peephole reset
