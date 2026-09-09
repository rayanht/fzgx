#include "types.h"

/* fzgx:begin fn_5_3E54 */
extern u32 lbl_5_bss_AF4;
extern u32 lbl_5_bss_B90;

void fn_5_3E54(u32 arg0) {
    lbl_5_bss_B90 = *(u32 *)((u8 *)&lbl_5_bss_AF4 + ((s8)arg0 << 2));
}
/* fzgx:end fn_5_3E54 */

/* fzgx:begin fn_5_3F94 */
typedef u32 (*fn_5_3F94_Fn0)(void);
typedef u32 (*fn_5_3F94_Fn1)(u32, u32);
struct fn_5_3F94_lbl_5_bss_0 {
    u32 unk_0;
};

extern struct fn_5_3F94_lbl_5_bss_0 lbl_5_bss_0;
extern u32 lbl_5_bss_20;

void fn_5_3F94(void) {
    u32 v0;
    if (lbl_5_bss_20 != 0) {
    ((fn_5_3F94_Fn0)lbl_5_bss_20)();
    }
    v0 = lbl_5_bss_0.unk_0;
    if (v0 != 0) {
    ((fn_5_3F94_Fn1)*(u32 *)((u8 *)*(u32 *)((u8 *)v0 + 0) + 40))(v0, 1);
    }
}
/* fzgx:end fn_5_3F94 */

/* fzgx:begin fn_5_3FF0 */
typedef u32 (*fn_5_3FF0_Fn0)(void);
typedef u32 (*fn_5_3FF0_Fn1)(u32, u32);
struct fn_5_3FF0_lbl_5_bss_0 {
    u32 unk_0;
    u8 pad_4[0x1C];
    u32 unk_20;
    u32 unk_24;
};

extern struct fn_5_3FF0_lbl_5_bss_0 lbl_5_bss_0;

void fn_5_3FF0(void) {
    struct fn_5_3FF0_lbl_5_bss_0 *p_lbl_5_bss_0;
    u32 v0;
    p_lbl_5_bss_0 = (struct fn_5_3FF0_lbl_5_bss_0 *)&lbl_5_bss_0;
    if (p_lbl_5_bss_0->unk_20 != 0) {
        ((fn_5_3FF0_Fn0)p_lbl_5_bss_0->unk_24)();
    }
    v0 = p_lbl_5_bss_0->unk_0;
    if (v0 != 0) {
        ((fn_5_3FF0_Fn1)*(u32 *)((u8 *)*(u32 *)((u8 *)v0 + 0) + 40))(v0, 0);
    }
}
/* fzgx:end fn_5_3FF0 */
