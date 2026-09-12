#include "types.h"
#include "rel/title/globals.h"
extern u32 fn_1_D0790(void);
extern u8 lbl_8_bss_230;
extern struct fn_8_784_lbl_1_bss_6EAD0 lbl_1_bss_6EAD0;
extern struct fn_8_784_lbl_8_bss_22C lbl_8_bss_22C;
extern u32 fn_1_5370(u32, u32);
extern u32 fn_1_A1588(u32, u32);
extern u32 lbl_8_bss_228;
extern void fn_8_4D8(void);
extern int fn_8_6FC(void);
extern void fn_8_704(void);
extern s32 fn_8_754(void);

/* fzgx:begin fn_8_6FC */
// fn_8_6FC: returns a constant.
int fn_8_6FC(void) {
    return 0;
}
/* fzgx:end fn_8_6FC */

/* fzgx:begin fn_8_754 */
s32 fn_8_754(void) {
    lbl_8_bss_230 = 0;
    fn_1_D0790();
    return 0;
}
/* fzgx:end fn_8_754 */

/* fzgx:begin fn_8_784 */
struct fn_8_784_lbl_8_bss_22C {
    u32 unk_0;
};
struct fn_8_784_lbl_1_bss_6EAD0 {
    u32 unk_0;
};

void fn_8_784(u32 arg0) {
    *(u32 *)((u8 *)arg0 + 168) = (u32)fn_8_4D8;
    *(u32 *)((u8 *)arg0 + 196) = (u32)fn_8_704;
    *(u32 *)((u8 *)arg0 + 204) = (u32)fn_8_6FC;
    *(u32 *)((u8 *)arg0 + 172) = (u32)fn_8_754;
    lbl_8_bss_228 = 0;
    lbl_8_bss_22C.unk_0 = -1;
    fn_1_5370(1, 0);
    *(u32 *)((u8 *)arg0 + 0) = ((*(u32 *)((u8 *)arg0 + 0) | 0x8200000) | 33033);
    fn_1_A1588(*(u32 *)((u8 *)lbl_1_bss_6EAD0.unk_0 + 0), 1);
}
/* fzgx:end fn_8_784 */
