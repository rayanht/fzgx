#include "types.h"

struct fn_80038A18_gx_T {
    u32 unk_0;
    u8 pad_4[0x4F0];
    u32 unk_4F4;
};

extern struct fn_80038A18_gx_T *gx;
extern void fn_8003458C(void);
extern void fn_8003471C(void);

void fn_80038A18(u32 arg0, u32 arg1) {
    if (gx->unk_4F4 != 0) {
        fn_8003458C();
    }
    if (gx->unk_0 == 0) {
        fn_8003471C();
    }
    *(volatile u8 *)((u8 *)0xCC010000 + -32768) = 0x40; /* fzgx-allow: A1,A2 GX FIFO hardware register */
    *(volatile u32 *)((u8 *)0xCC010000 + -32768) = arg0; /* fzgx-allow: A1,A2 GX FIFO hardware register */
    *(volatile u32 *)((u8 *)0xCC010000 + -32768) = arg1; /* fzgx-allow: A1,A2 GX FIFO hardware register */
}
