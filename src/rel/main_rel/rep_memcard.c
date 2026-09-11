#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/rep_memcard.h"

extern u32 lbl_801A6410;
extern void fn_80008BA8(u32 arg0, u32 arg1, u32 arg2);
extern void fn_1_46B4(u32 arg0, u32 arg1, u8 *arg2, s32 arg3);
extern u32 fn_1_4630(u32 arg0, u32 arg1, u8 *arg2, s32 arg3);
extern u8 lbl_1_bss_8EDA0;
extern void fn_1_154F1C(void);
extern void *memset(void *dest, int value, u32 size);
extern void fn_1_155120(void);
extern const f64 lbl_1_rodata_D5A8;
extern void fn_1_496FC(f32, f32);
extern void fn_1_4955C(f32, f32);
extern void fn_1_495FC(void);
extern f32 fn_1_4B090(void *);
extern int fn_1_4B16C(void *);
extern const f32 lbl_1_rodata_D5A0;
extern void fn_1_4966C(f32, f32);
extern int fn_1_FA638(void);
extern void fn_1_4AF64(void *, ...);
extern void fn_1_49614(void);

/* fzgx:begin fn_1_154CC4 */
void fn_1_154CC4(u32 arg0) {
    lbl_1_data_49AB4.unk_0 = arg0;
}
/* fzgx:end fn_1_154CC4 */

/* fzgx:begin fn_1_154CD0 */
void fn_1_154CD0(u32 arg0, u32 arg1) {
    if (lbl_1_bss_8ED90 != 0) {
        fn_1_46B4(lbl_801A6410, lbl_1_bss_8ED90, lbl_1_data_49AC8, 0x12f);
        lbl_1_bss_8ED90 = 0;
        lbl_1_bss_8ED94.unk_0 = 0;
    }

    lbl_1_bss_8ED90 = fn_1_4630(lbl_801A6410, arg1, lbl_1_data_49AC8, 0x133);
    fn_80008BA8(lbl_1_bss_8ED90, arg0, arg1);
    lbl_1_bss_8ED94.unk_0 = arg1;
}
/* fzgx:end fn_1_154CD0 */

/* fzgx:begin fn_1_154D84 */
// Saves the pending memory-card data and clears the pending state.
u32 fn_1_154D84(u32 arg0) {
    if (lbl_1_bss_8ED90 == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }

    fn_80008BA8(arg0, lbl_1_bss_8ED90, lbl_1_bss_8ED94.unk_0);
    fn_1_46B4(lbl_801A6410, lbl_1_bss_8ED90, lbl_1_data_49AC8, 0x13f);
    lbl_1_bss_8ED90 = 0;
    lbl_1_bss_8ED94.unk_0 = 0;
    return 1;
}
/* fzgx:end fn_1_154D84 */

/* fzgx:begin fn_1_154E24 */
u8 fn_1_154E24(void) {
    return lbl_1_bss_8EDA0;
}
/* fzgx:end fn_1_154E24 */

/* fzgx:begin fn_1_154E34 */
u32 fn_1_154E34(u32 *arg0) {
    *arg0 = lbl_1_bss_8ED94.unk_0;
    return lbl_1_bss_8ED90;
}
/* fzgx:end fn_1_154E34 */

/* fzgx:begin fn_1_154E4C noprologue */
#include "types.h"

struct fn_1_154E4C_lbl_1_bss_8EDF0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u8 pad_14[0xC];
    u32 unk_20;
    u32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    u32 unk_30;
};

extern f32 lbl_1_rodata_D598;
extern f32 lbl_1_rodata_D59C;
extern struct fn_1_154E4C_lbl_1_bss_8EDF0 lbl_1_bss_8EDF0;
extern u32 fn_1_154FA8(f32);
extern u32 memset(u32, u32, u32);

void fn_1_154E4C(void) {
    u32 v0;
    memset((u32)&lbl_1_bss_8EDF0, 0, 304);
    lbl_1_bss_8EDF0.unk_C = 0;
    lbl_1_bss_8EDF0.unk_28 = lbl_1_rodata_D598;
    lbl_1_bss_8EDF0.unk_30 = 2;
    lbl_1_bss_8EDF0.unk_8 = ((lbl_1_bss_8EDF0.unk_8 & 0xFFFFFFFD));
    lbl_1_bss_8EDF0.unk_10 = 0;
    lbl_1_bss_8EDF0.unk_20 = 80;
    lbl_1_bss_8EDF0.unk_24 = 385;
    lbl_1_bss_8EDF0.unk_2C = lbl_1_rodata_D59C;
    fn_1_154FA8(lbl_1_rodata_D598);
}
/* fzgx:end fn_1_154E4C */

/* fzgx:begin fn_1_154ED0 */
typedef struct {
    u8 pad_0[0x134];
    Obj_1_bss_8EDF0_At10 *unk_134;
} Fn_1_154ED0_Arg;

void fn_1_154ED0(Fn_1_154ED0_Arg *arg0) {
    fn_1_154F1C();
    lbl_1_bss_8EDF0.unk_C = (u32)arg0;
    lbl_1_bss_8EDF0.unk_10 = arg0->unk_134;
    lbl_1_bss_8EDF0.unk_0 = 0;
    lbl_1_bss_8EDF0.unk_4 = 0;
}
/* fzgx:end fn_1_154ED0 */

/* fzgx:begin fn_1_154F1C */
// Reset the memory-card state and clear its backing buffer.
void fn_1_154F1C(void) {
    lbl_1_bss_8EDF0.unk_1C = 0;
    lbl_1_bss_8EDF0.unk_14 = 0;
    lbl_1_bss_8EDF0.unk_18 = 0;
    memset(&lbl_1_bss_8EDF0.unk_34, 0, 250);
    lbl_1_bss_8EDF0.unk_34 = 0;
}
/* fzgx:end fn_1_154F1C */

/* fzgx:begin fn_1_154F74 */
// Stores the two memory-card state values used by the replication subsystem.
void fn_1_154F74(u32 arg0, u32 arg1) {
    lbl_1_bss_8EDF0.unk_20 = arg0;
    lbl_1_bss_8EDF0.unk_24 = arg1;
}
/* fzgx:end fn_1_154F74 */

/* fzgx:begin fn_1_154F88 */
// Stores the current float value in the memory-card state.
void fn_1_154F88(f32 value) {
    lbl_1_bss_8EDF0.unk_2C = value;
}
/* fzgx:end fn_1_154F88 */

/* fzgx:begin fn_1_154F98 */
void fn_1_154F98(u32 value) {
    lbl_1_bss_8EDF0.unk_30 = value;
}
/* fzgx:end fn_1_154F98 */

/* fzgx:begin fn_1_154FA8 */
void fn_1_154FA8(void) {
    lbl_1_bss_8EDF0.unk_8 |= 4;
}
/* fzgx:end fn_1_154FA8 */

/* fzgx:begin fn_1_154FC0 */
void fn_1_154FC0(void) {
    lbl_1_bss_8EDF0.unk_8 &= ~4;
}
/* fzgx:end fn_1_154FC0 */

/* fzgx:begin fn_1_154FD8 */
void fn_1_154FD8(void) {
    Obj_1_bss_8EDF0 *obj;
    f32 value;
    f32 ratio;
    int count;

    obj = &lbl_1_bss_8EDF0;
    if ((obj->unk_8 & 1) == 0) {
        obj->unk_0++;
        if ((s32)obj->unk_4 != 0) {
            obj->unk_4--;
        }
    }

    if ((s32)obj->unk_4 <= 0) {
        if (((s32)obj->unk_0 % (s32)obj->unk_30) == 0) {
            fn_1_155120();
        }
    }

    fn_1_496FC((f32)(s32)obj->unk_20, (f32)(s32)obj->unk_24);
    fn_1_4955C(obj->unk_28, obj->unk_28);
    fn_1_495FC();

    value = fn_1_4B090(&obj->unk_34);
    ratio = value / (f32)(fn_1_4B16C(&obj->unk_34));
    fn_1_4966C(lbl_1_rodata_D5A0, ratio * obj->unk_2C);

    if (fn_1_FA638() != 0) {
        fn_1_4AF64(&obj->unk_34);
    }

    fn_1_49614();
}
/* fzgx:end fn_1_154FD8 */

/* fzgx:begin fn_1_15530C noprologue */
#include "types.h"
#include "rel/main_rel/rep_memcard.h"

extern const f64 lbl_1_rodata_D5B0;
extern f64 fn_80083E84(u8 *text);
extern s32 atoi(u8 *text);
extern void *memset(void *dest, s32 value, u32 size);

u8 *fn_1_15530C(u8 *text) {
    Obj_1_bss_8EDF0 *obj = &lbl_1_bss_8EDF0;

    switch (*text) {
    case 'l':
    {
        u8 *dest;
        obj->unk_1C = 0;
        dest = &obj->unk_34;
        obj->unk_14 = 0;
        text++;
        obj->unk_18 = 0;
        memset(dest, 0, 0xFA);
        *dest = 0;
        break;
    }
    case 'w':
    {
        f32 value;
        text++;
        value = (f32)fn_80083E84(text);
        while ((*text >= '0' && *text <= '9') || *text == '.') {
            text++;
        }
        obj->unk_4 = (s16)(*(const f32 *)(const void *)&lbl_1_rodata_D5B0 * value);
        break;
    }
    case 't':
    {
        s32 value;
        text++;
        value = atoi(text);
        while ((*text >= '0' && *text <= '9') || *text == '.') {
            text++;
        }
        value = value - obj->unk_0;
        if (value >= 0) {
            obj->unk_4 = value;
        } else {
            obj->unk_4 = 0;
        }
        break;
    }
    case 'p':
    {
        s32 value = 0;
        text++;
        while ((*text >= '0') && (*text <= '9')) {
            if (value != 0) {
                value *= 10;
            }
            value = *text + value;
            text++;
            value -= 0x30;
        }
        break;
    }
    case 's':
    {
        f32 value;
        text++;
        value = (f32)fn_80083E84(text);
        while ((*text >= '0' && *text <= '9') || *text == '.') {
            text++;
        }
        obj->unk_28 = value;
        break;
    }
    default:
        text++;
        break;
    }

    return text;
}
/* fzgx:end fn_1_15530C */
