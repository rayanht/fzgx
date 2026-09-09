#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/prog.h"

extern u32 lbl_1_bss_6F5F4;
extern void fn_1_4A00(s32, s32, u32);
extern s8 fn_1_A5DC4(void);
extern const f32 lbl_1_rodata_49F8;
extern f32 lbl_1_rodata_49FC[11];

/* fzgx:begin fn_1_A6F10 */
u32 *fn_1_A6F10(void) {
    return &lbl_1_bss_6F5F0;
}
/* fzgx:end fn_1_A6F10 */

/* fzgx:begin fn_1_A6F1C */
u32 fn_1_A6F1C(void) {
    return lbl_1_bss_6F5F0;
}
/* fzgx:end fn_1_A6F1C */

/* fzgx:begin fn_1_A6F2C */
s32 fn_1_A6F2C(void) {
    s32 result = 0;
    s32 state;

    if (lbl_1_bss_962 == 0x99) {
        state = lbl_1_data_341B8->unk_4;
        if ((s8)state == 0 || (s8)state == 5) {
            result = 1;
        }
    }

    return result;
}
/* fzgx:end fn_1_A6F2C */

/* fzgx:begin fn_1_A6F6C */
s32 fn_1_A6F6C(void) {
    s32 result = 0;

    if (lbl_1_bss_962 == 0x99) {
        if (*(s8 *)((u8 *)lbl_1_data_341B8 + 4) == 5) {
            result = 1;
        }
    }

    return result;
}
/* fzgx:end fn_1_A6F6C */

/* fzgx:begin fn_1_A6FA0 */
void fn_1_A6FA0(void) {
    fn_1_4A00(0, 0x3c, lbl_1_bss_6F5F4);
    lbl_1_data_341B8->unk_4 = 5;
}
/* fzgx:end fn_1_A6FA0 */

/* fzgx:begin fn_1_A6FE8 */
f32 fn_1_A6FE8(void) {
    if (fn_1_A5DC4()) {
        return lbl_1_rodata_49F8;
    }

    return lbl_1_rodata_49FC[0];
}
/* fzgx:end fn_1_A6FE8 */

/* fzgx:begin fn_1_A714C */
void fn_1_A714C(f32 *a, f32 *b, f32 *c, f32 *d) {
    if (a != 0) {
        *a = *(f32 *)&lbl_1_bss_6F608.unk_0;
    }
    if (b != 0) {
        *b = *(f32 *)&lbl_1_bss_6F608.unk_4;
    }
    if (c != 0) {
        *c = *(f32 *)&lbl_1_bss_6F608.unk_8;
    }
    if (d != 0) {
        *d = *(f32 *)&lbl_1_bss_6F608.unk_C;
    }
}
/* fzgx:end fn_1_A714C */

/* fzgx:begin fn_1_A71AC */
f32 fn_1_A71AC(void) {
    return *(f32 *)&lbl_1_bss_6F608.unk_10;
}
/* fzgx:end fn_1_A71AC */

/* fzgx:begin fn_1_A71BC */
f32 fn_1_A71BC(void) {
    return *(f32 *)((u8 *)&lbl_1_bss_6F608 + 0x14);
}
/* fzgx:end fn_1_A71BC */

/* fzgx:begin fn_1_A728C */
// fn_1_A728C: returns a constant.
int fn_1_A728C(void) {
    return 0;
}
/* fzgx:end fn_1_A728C */
