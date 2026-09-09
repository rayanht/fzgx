#include "types.h"
extern s16 lbl_1_bss_960;
extern struct fn_4_D760_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_412A0(u32);
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_1_48140(u32);
extern u32 fn_1_A8F78(void);
extern u32 lbl_4_data_3018;
extern u8 lbl_4_bss_5684;
extern u8 lbl_4_bss_5685;

/* fzgx:begin fn_4_D760 */
struct fn_4_D760_lbl_4_bss_5680 {
    u32 unk_0;
};
struct fn_4_D760_lbl_801A6410 {
    u32 unk_0;
};

extern struct fn_4_D760_lbl_4_bss_5680 lbl_4_bss_5680;

void fn_4_D760(void) {
    u32 v0;
    u32 v1;
    u32 t4, t5;
    v0 = lbl_4_bss_5680.unk_0;
    lbl_4_bss_5684 = 1;
    fn_1_435C(*(u32 *)((u8 *)v0 + 4));
    fn_1_426C(*(u32 *)((u8 *)lbl_4_bss_5680.unk_0 + 24));
    fn_1_A8F78();
    fn_1_48140(143);
    if (lbl_1_bss_960 != 1) {
    if (lbl_1_bss_960 != 3) {
    v1 = 1;
    t4 = fn_1_412A0(v1);
    v1 = t4;
    v1 = 154;
    t5 = fn_1_48140(v1);
    v1 = t5;
    }
    v1 = 158;
    fn_1_48140(v1);
    }
    fn_1_435C(*(u32 *)((u8 *)lbl_4_bss_5680.unk_0 + 8));
    fn_1_426C(*(u32 *)((u8 *)lbl_4_bss_5680.unk_0 + 28));
    fn_1_46B4(lbl_801A6410.unk_0, lbl_4_bss_5680.unk_0, (u32)&lbl_4_data_3018, 1378);
    lbl_4_bss_5680.unk_0 = 0;
}
/* fzgx:end fn_4_D760 */

/* fzgx:begin fn_4_D848 */
extern struct fn_4_D848_lbl_4_bss_5680 lbl_4_bss_5680;
extern u32 fn_80083DB0(u32, u32);

struct fn_4_D848_lbl_4_bss_5680 {
    u32 unk_0;
};

void fn_4_D848(u32 arg0) {
    fn_80083DB0(arg0, (lbl_4_bss_5680.unk_0 + 40));
}
/* fzgx:end fn_4_D848 */

/* fzgx:begin fn_4_D878 */
void fn_4_D878(void) {
    lbl_4_bss_5685 = 1;
}
/* fzgx:end fn_4_D878 */
