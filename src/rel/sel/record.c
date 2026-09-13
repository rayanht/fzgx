#include "types.h"

/* fzgx:begin fn_10_26554 */
extern u8 lbl_10_bss_55CE0;
extern char lbl_10_data_6BD0[9];
extern char lbl_10_data_6BDC[19];

extern void fn_1_12EF80(u8, s16 *, s16 *);
extern void fn_1_FA1D8(s16, s16, void *);
extern int fn_1_B7E98(int);
extern void fn_1_F7954(void);
extern void fn_80008BA8(void *, const void *, u32);
extern void OSPanic(const char *, int, const char *, ...);
extern void fn_1_B7CE4(int, void *);
extern void fn_1_AA6D8(int, int, void *);

extern u8 lbl_1_bss_7F0C0[];
extern u32 lbl_1_bss_718C0;
extern u8 lbl_1_bss_8B3A0[];
extern u8 lbl_1_bss_718E0;

static inline void fn_10_26554_call_fn_1_AA6D8(void * a3, void * a2, int a1, int a0) { fn_1_AA6D8(a0, a1, a2); }
void fn_10_26554(void) {
    s16 b;
    u8 work[0x100];
    s16 a;
    u8 *p;

    fn_1_12EF80(lbl_10_bss_55CE0, &b, &a);
    fn_1_FA1D8(b, a, (u8 *)lbl_1_bss_7F0C0 + (b * 6 + a) * 0x180 + 0xf8);
    if (fn_1_B7E98(0) != 0) {
        fn_1_F7954();
        p = (u8 *)lbl_1_bss_718C0 + 4;
        fn_80008BA8(p, (u8 *)lbl_1_bss_8B3A0 + 0x9f, 4);
        fn_80008BA8(p + 4, (u8 *)lbl_1_bss_8B3A0 + 0x8c, 6);
        fn_80008BA8(p + 0xa, (u8 *)lbl_1_bss_8B3A0 + 0xc, 0x80);
        if ((u32)((p + 0x8a) - ((u8 *)lbl_1_bss_718C0 + 4)) != 0x8a) {
            OSPanic(lbl_10_data_6BD0, 0x184, lbl_10_data_6BDC);
        }
        fn_1_B7CE4(1, work);
{
    u8 data[0x24];
        memset(data, 0, 0x24);
        data[0] = 1;
        *(u32 *)(data + 4) = 4;
        *(void **)(data + 0xc) = &lbl_1_bss_718E0;
        *(void **)(data + 8) = work;
        fn_10_26554_call_fn_1_AA6D8(&lbl_1_bss_718E0, data, 0, 0);
}
    }
}
/* fzgx:end fn_10_26554 */
