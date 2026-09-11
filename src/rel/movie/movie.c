#include "types.h"

/* fzgx:begin fn_5_3E54 */
extern u32 lbl_5_bss_AF4;
extern u32 lbl_5_bss_B90;

void fn_5_3E54(u32 arg0) {
    lbl_5_bss_B90 = *(u32 *)((u8 *)&lbl_5_bss_AF4 + ((s8)arg0 << 2));
}
/* fzgx:end fn_5_3E54 */

/* fzgx:begin fn_5_3E74 */
struct fn_5_3E74_Arg0 {
    s32 unk_0;
    u8 pad_4[0xc];
    u8 unk_10[0x100];
};

extern s32 fn_80082928(char *, const char *, ...);
extern u32 lbl_5_bss_B90;
extern char lbl_5_data_1784[];
extern char *strchr(const char *, int);
extern s8 lbl_5_bss_5D;

u32 fn_5_3E74(struct fn_5_3E74_Arg0 *arg0) {
    u32 v1;
    s32 v3;
    s16 i;
    u8 c;

    v1 = 0;
    v3 = 0;
    fn_80082928((char *)lbl_5_bss_B90, lbl_5_data_1784, arg0, (u8 *)arg0 + 4,
                (u8 *)arg0 + 8, (u8 *)arg0 + 12, (u8 *)arg0 + 16);
    if (arg0->unk_0 == -1) {
        lbl_5_bss_B90 = 0;
    } else {
        i = 0;
        while ((c = arg0->unk_10[i]) != '*' && i < 255) {
            if (c == '[') {
                v3 = 1;
            } else if (c == ']') {
                v3 = 0;
            }
            i++;
            if (v3 == 0) {
                v1++;
            }
        }
        arg0->unk_10[i] = 0;
        lbl_5_bss_B90 = (u32)strchr((const char *)lbl_5_bss_B90, '\n') + 1;
    }
    if (lbl_5_bss_5D == 5) {
        v1 = (v1 >> 1) & 0x7f;
    }
    return v1;
}
/* fzgx:end fn_5_3E74 */

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
