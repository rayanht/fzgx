#include "types.h"
extern u32 fn_1_D0790(void);
extern u32 lbl_13_bss_38;
extern int fn_13_A40(void);
extern s32 fn_13_A48(void);
extern s16 lbl_1_bss_962;
extern struct fn_13_B08_lbl_13_data_18 lbl_13_data_18;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;
extern u32 lbl_1_bss_26C60;
extern void fn_13_3FC(void);
extern u32 fn_1_3F038(void);
extern u32 lbl_13_bss_40;

/* fzgx:begin fn_13_A40 */
// fn_13_A40: returns a constant.
int fn_13_A40(void) {
    return 0;
}
/* fzgx:end fn_13_A40 */

/* fzgx:begin fn_13_A48 */
s32 fn_13_A48(void) {
    fn_1_D0790();
    return 0;
}
/* fzgx:end fn_13_A48 */

/* fzgx:begin fn_13_A6C */
struct fn_13_A6C_Arg0 {
    u8 pad_0[0xAC];
    u32 unk_AC;
    u8 pad_B0[0x1C];
    u32 unk_CC;
};

void fn_13_A6C(struct fn_13_A6C_Arg0 *arg0) {
    arg0->unk_CC = (u32)fn_13_A40;
    arg0->unk_AC = (u32)fn_13_A48;
    lbl_13_bss_38 = 0;
}
/* fzgx:end fn_13_A6C */

/* fzgx:begin _prolog */
extern u32 lbl_1_bss_7167C;
extern u32 lbl_1_bss_71680;
extern u32 lbl_1_bss_71684;
extern u16 lbl_1_bss_96A;
extern u8 lbl_13_bss_3C;
extern void fn_13_AFC(void);
extern void fn_13_B00(void);
extern void fn_13_B08(void);
extern void fn_1_A8F78(void);

void _prolog(void) {
    lbl_1_bss_7167C = (u32)fn_13_AFC;
    lbl_1_bss_71680 = (u32)fn_13_B00;
    lbl_1_bss_71684 = (u32)fn_13_B08;
    lbl_1_bss_96A = 0xA7;
    fn_1_A8F78();
    lbl_13_bss_3C = 0;
}
/* fzgx:end _prolog */

/* fzgx:begin fn_13_AFC */
// fn_13_AFC: empty in retail (single blr).
void fn_13_AFC(void) {
}
/* fzgx:end fn_13_AFC */

/* fzgx:begin fn_13_B00 */
// fn_13_B00: empty in retail (single blr).
void fn_13_B00(void) {
}
/* fzgx:end fn_13_B00 */

/* fzgx:begin _epilog */
// _epilog: empty in retail (single blr).
void _epilog(void) {
}
/* fzgx:end _epilog */

/* fzgx:begin fn_13_B08 */
typedef u32 (*fn_13_B08_Fn0)(void);
struct fn_13_B08_lbl_13_data_18_0_E16 {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
};
struct fn_13_B08_lbl_13_data_18 {
    struct fn_13_B08_lbl_13_data_18_0_E16 unk_0[1];
};

void fn_13_B08(void) {
    s32 index;
    struct fn_13_B08_lbl_13_data_18_0_E16 *p;
    index = lbl_1_bss_962;
    index -= 167;
    p = &lbl_13_data_18.unk_0[0];
    p += index;
    lbl_1_bss_71688 = p->unk_8;
    lbl_1_bss_7168C = p->unk_C;
    ((fn_13_B08_Fn0)p->unk_4)();
}
/* fzgx:end fn_13_B08 */

/* fzgx:begin fn_13_B64 */
void fn_13_B64(void) {
    lbl_1_bss_26C60 = (u32)fn_13_3FC;
}
/* fzgx:end fn_13_B64 */

/* fzgx:begin fn_13_B78 */
// fn_13_B78: empty in retail (single blr).
void fn_13_B78(void) {
}
/* fzgx:end fn_13_B78 */

/* fzgx:begin fn_13_B7C */
extern struct fn_13_B7C_lbl_13_bss_3C lbl_13_bss_3C;
extern u16 lbl_1_bss_96A;

struct fn_13_B7C_lbl_13_bss_3C {
    u8 unk_0;
};

void fn_13_B7C(void) {
    u32 t0;
    t0 = fn_1_3F038();
    if ((s32)t0 != 0) {
    lbl_13_bss_3C.unk_0 = 1;
    lbl_1_bss_96A = 169;
    lbl_13_bss_40 = 167;
    }
}
/* fzgx:end fn_13_B7C */
