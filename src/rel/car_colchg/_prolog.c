#include "types.h"
#include "rel/car_colchg/globals.h"

extern struct Struct_lbl_1_bss_D58 lbl_1_bss_D58;
extern u16 lbl_1_bss_96A;
s32 fn_1_4C10(void);
void fn_1_435C(u32);
void fn_1_407C(void);
void fn_1_3CC4(void);

/* fzgx:begin _prolog noprologue */
#include "types.h"

extern struct _prolog_lbl_801A6410 lbl_801A6410;
extern struct _prolog_lbl_9_data_0 lbl_9_data_0;
extern struct _prolog_lbl_9_bss_0 lbl_9_bss_0;
extern struct _prolog_lbl_1_bss_970 lbl_1_bss_970;
extern u16 lbl_1_bss_96A;
extern u32 lbl_1_bss_7167C;
extern u32 lbl_1_bss_71680;
extern u32 lbl_1_bss_71684;
extern const f32 lbl_9_rodata_0;
extern const f32 lbl_9_rodata_4;

extern u32 fn_1_4630(u32, u32, void *, u32);
extern u32 fn_1_45D0(u32, u32, void *, u32);
extern u32 fn_1_7BA08(u32, u32, u32);
extern void fn_1_7BA48(u32);
extern void fn_1_3CF0(u32, u32);
extern void fn_1_5124(u32, u32);
extern void fn_1_435C(u32);
extern u32 fn_1_3F8C(void *, void *, u32, u32);
extern void fn_1_8CED0(void *, u32, u32);
extern void fn_1_8D0A4(void *);
extern void fn_8006CE1C(f32);
extern void fn_80074CF4(f32, f32, f32);
extern void fn_1_7BAF8(void);
extern void fn_9_1AFC(void);
extern void fn_9_298(void);
extern void fn_9_2E0(void);
extern void fn_9_1C54(void);

struct _prolog_lbl_801A6410 {
    u32 unk_0;
};
struct _prolog_lbl_9_data_0 {
    u8 pad_0[0x4];
    u8 unk_4[0x10];
    u8 unk_14[0xC];
    u8 unk_20[0x4];
};
struct _prolog_arr {
    u8 pad_0[0x324];
    s32 unk_324;
    u8 pad_328[0x118];
};
struct _prolog_lbl_9_bss_0 {
    u32 unk_0;
    struct _prolog_arr *unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u8 unk_14[0xC8];
};
struct _prolog_lbl_1_bss_970 {
    u32 unk_0;
    u8 unk_4;
};

void _prolog(void) {
    struct _prolog_lbl_9_data_0 *d;
    struct _prolog_lbl_9_bss_0 *p;
    u32 t;
    u32 h;
    struct { u8 * value; } q;
    s16 i;
    f32 v;
    d = (struct _prolog_lbl_9_data_0 *)&lbl_9_data_0;
    p = (struct _prolog_lbl_9_bss_0 *)&lbl_9_bss_0;
    p->unk_8 = fn_1_4630(lbl_801A6410.unk_0, 0x10, &d->unk_4, 0x93);
    p->unk_4 = (struct _prolog_arr *)fn_1_4630(lbl_801A6410.unk_0, 0xAE40, &d->unk_4, 0x94);
    for (i = 0; i < 0x29; i++) {
    p->unk_4[i].unk_324 = -1;
    }
    h = fn_1_45D0(lbl_801A6410.unk_0, fn_1_7BA08(0x20, 0x20, 0x40), &d->unk_4, 0x96);
    p->unk_0 = h;
    fn_1_7BA48(h);
    p->unk_C = fn_1_45D0(lbl_801A6410.unk_0, 0x173c, &d->unk_4, 0x97);
    fn_1_3CF0(p->unk_C, 0x80);
    p->unk_10 = fn_1_45D0(lbl_801A6410.unk_0, 0x173c, &d->unk_4, 0x98);
    fn_1_3CF0(p->unk_10, 0x80);
    fn_1_5124(p->unk_C, p->unk_10);
    lbl_1_bss_970.unk_0 = 0;
    lbl_1_bss_970.unk_4 = 0x72;
    lbl_1_bss_96A = 0x72;
    fn_8006CE1C(lbl_9_rodata_0);
    v = lbl_9_rodata_4;
    fn_80074CF4(v, v, v);
    fn_1_435C(p->unk_10);
    fn_1_3F8C(&d->unk_14, fn_1_7BAF8, p->unk_0, 2);
    fn_1_3F8C(&d->unk_20, fn_9_1AFC, 0, 3);
    q.value = (u8 *)p + 0x14;
    for (i = 0; i < 2; i++) {
    fn_1_8CED0(q.value, 0x200, 0x200);
    fn_1_8D0A4(q.value);
    q.value += 0x64;
    }
    lbl_1_bss_7167C = (u32)fn_9_298;
    lbl_1_bss_71680 = (u32)fn_9_2E0;
    lbl_1_bss_71684 = (u32)fn_9_1C54;
}
/* fzgx:end _prolog */

/* fzgx:begin fn_9_298 */
struct Struct_lbl_1_bss_D58 {
    u8 pad[8];
    u16 unk8;
};

void fn_9_298(void) {
    if (fn_1_4C10() == 0) {
        if ((lbl_1_bss_D58.unk8 >> 12) & 1) {
            lbl_1_bss_96A = 0x75;
        }
    }
}
/* fzgx:end fn_9_298 */

/* fzgx:begin fn_9_2E0 */
void fn_9_2E0(void) {
    fn_1_435C(lbl_9_bss_C);
    fn_1_407C();
    fn_1_3CC4();
    fn_1_435C(lbl_9_bss_10);
    fn_1_407C();
}
/* fzgx:end fn_9_2E0 */
