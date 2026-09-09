#include "types.h"
#include "rel/option/globals.h"

extern s16 lbl_1_bss_960;
extern struct fn_4_D760_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_412A0(u32);
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_1_48140(u32);
extern u32 fn_1_A8F78(void);
extern u32 lbl_4_data_3018;

/* fzgx:begin fn_4_D760 */
struct fn_4_D760_lbl_801A6410 {
    u32 unk_0;
};

extern s16 lbl_1_bss_960;
extern struct fn_4_D760_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_412A0(u32);
extern u32 fn_1_426C(u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 fn_1_48140(u32);
extern u32 fn_1_A8F78(void);
extern u32 lbl_4_data_3018;

// Initialize the option name-entry state and dispatch the next menu resources.
void fn_4_D760(void) {
    lbl_4_bss_5684 = 1;
    fn_1_435C(lbl_4_bss_5680->unk_4);
    fn_1_426C(lbl_4_bss_5680->unk_18);
    fn_1_A8F78();
    fn_1_48140(143);

    if (lbl_1_bss_960 != 1) {
        if (lbl_1_bss_960 != 3) {
            fn_1_412A0(1);
            fn_1_48140(154);
        }
        fn_1_48140(158);
    }

    fn_1_435C(lbl_4_bss_5680->unk_8);
    fn_1_426C(lbl_4_bss_5680->unk_1C);
    fn_1_46B4(lbl_801A6410.unk_0, (u32)lbl_4_bss_5680,
              (u32)&lbl_4_data_3018, 1378);
    lbl_4_bss_5680 = 0;
}
/* fzgx:end fn_4_D760 */

/* fzgx:begin fn_4_D848 */
extern void fn_80083DB0(void *, void *);

// Copies the name-entry data into the active name-entry buffer.
void fn_4_D848(u32 arg0) {
    fn_80083DB0((void *)arg0, &lbl_4_bss_5680->unk_28);
}
/* fzgx:end fn_4_D848 */

/* fzgx:begin fn_4_D878 */
void fn_4_D878(void) {
    lbl_4_bss_5685 = 1;
}
/* fzgx:end fn_4_D878 */
