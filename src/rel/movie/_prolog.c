#include "types.h"

/* fzgx:begin fn_5_220 */
extern struct fn_5_220_lbl_5_bss_0 lbl_5_bss_0;
extern u32 fn_1_3CC4(u32);
extern u32 fn_1_407C(u32);
extern u32 fn_1_435C(u32);

struct fn_5_220_lbl_5_bss_0 {
    u8 pad_0[0x28];
    u32 unk_28;
    u32 unk_2C;
    u32 unk_30;
    u32 unk_34;
};

void fn_5_220(void) {
    struct fn_5_220_lbl_5_bss_0 *p_lbl_5_bss_0;
    u32 t0, t2, t3, t5, t7;
    p_lbl_5_bss_0 = (struct fn_5_220_lbl_5_bss_0 *)&lbl_5_bss_0;
    t0 = fn_1_435C(p_lbl_5_bss_0->unk_28);
    fn_1_407C(t0);
    t2 = fn_1_435C(p_lbl_5_bss_0->unk_30);
    t3 = fn_1_407C(t2);
    fn_1_3CC4(t3);
    t5 = fn_1_435C(p_lbl_5_bss_0->unk_2C);
    fn_1_407C(t5);
    t7 = fn_1_435C(p_lbl_5_bss_0->unk_34);
    fn_1_407C(t7);
}
/* fzgx:end fn_5_220 */

/* fzgx:begin fn_5_320 */
typedef u32 (*fn_5_320_Fn0)(void);
struct fn_5_320_lbl_5_data_40_0_E44 {
    u8 pad_0[0x20];
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
};
struct fn_5_320_lbl_5_data_40 {
    struct fn_5_320_lbl_5_data_40_0_E44 unk_0[1];
};

extern s16 lbl_1_bss_962;
extern struct fn_5_320_lbl_5_data_40 lbl_5_data_40;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

void fn_5_320(void) {
    s32 i;
    struct fn_5_320_lbl_5_data_40_0_E44 *p;
    u32 v0;
    p = lbl_5_data_40.unk_0;
    i = lbl_1_bss_962;
    i -= 129;
    p += i;
    lbl_1_bss_71688 = p->unk_24;
    v0 = p->unk_28;
    lbl_1_bss_7168C = v0;
    ((fn_5_320_Fn0)p->unk_20)();
}
/* fzgx:end fn_5_320 */

/* fzgx:begin fn_5_684 */
extern u32 fn_1_412A0(u32);
extern u32 fn_1_48140(u32);
extern u8 lbl_5_bss_5F;
extern u8 lbl_5_bss_61;

void fn_5_684(void) {
    if ((s8)lbl_5_bss_5F != 0) {
    fn_1_48140(154);
    fn_1_48140(155);
    fn_1_48140(147);
    fn_1_412A0(1);
    }
    if ((s8)lbl_5_bss_61 != 0) {
    fn_1_48140(1);
    }
}
/* fzgx:end fn_5_684 */

/* fzgx:begin fn_5_13B0 */
extern u32 fn_1_412A0(u32);
extern u32 fn_1_48140(u32);
extern u32 fn_5_3C44(void);
extern u8 lbl_5_bss_40;

void fn_5_13B0(void) {
    if ((s8)lbl_5_bss_40 != -2) {
    fn_5_3C44();
    }
    fn_1_48140(154);
    fn_1_48140(155);
    fn_1_48140(147);
    fn_1_412A0(1);
}
/* fzgx:end fn_5_13B0 */
