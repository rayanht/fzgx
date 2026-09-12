#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/effect.h"

extern void fn_1_3BDC(s32 arg0);
extern u32 fn_1_3C18(s32 arg0);
extern void fn_80008BEC(void *, int, int);
extern void fn_80008BA8(void *, void *, int);
extern void fn_1_680F8(void);
extern void fn_1_68284(void);
extern void fn_1_68B68(void);
extern void fn_1_68248(void);
extern void fn_1_69BBC(void);
extern void fn_1_69BCC(void);
extern f32 lbl_1_rodata_29AC[5];
extern f32 lbl_1_rodata_2978[4];
extern void lbl_8006DCA4(void);
extern f32 lbl_1_rodata_2AF4[14];
extern s32 fn_1_54E34(void *object, f32 value);
extern void fn_1_5EB98(void);
extern void fn_1_5FEBC(void);
extern void *lbl_801A6410;
extern void fn_1_46B4(u32 value, void *field, u8 *data, s32 code);
extern f32 lbl_1_rodata_2A5C[5];
extern void fn_1_61D08(void);
extern void fn_1_61EF4(void);
extern void fn_1_620C4(void);
extern void fn_1_4730(void *arg0, void *arg1, int arg2, u8 *arg3, int arg4);
extern f32 lbl_1_rodata_2B2C[145];
extern void fn_1_638E8(void);
extern const f32 lbl_1_rodata_2A70[12];
extern void fn_1_64388(void);
extern void fn_1_652F4(void);
extern void fn_1_65748(void);
extern void fn_1_8636C(s16, void *);

extern void *lbl_801A6410;
extern void fn_1_46B4(u32 value, void *field, u8 *data, s32 code);
extern void fn_1_4730(void *arg0, void *arg1, int arg2, u8 *arg3, int arg4);
extern void lbl_8006DCA4(void);
extern s32 fn_1_54E34(void *object, f32 value);
extern void fn_1_65748(void);
extern const f32 lbl_1_rodata_2A70[12];
extern void fn_1_64388(void);
extern void *fn_1_5448C(void *);
extern void fn_1_61E60(void);
extern void fn_1_5489C(void *, void *);
extern void fn_1_862D4(s16 value, void *result);
extern void *fn_1_548AC(u32 size);
extern int fn_1_3FC8C(void);
extern int fn_1_3FC58(void);
extern void *memcpy(void *, const void *, u32);
extern const f32 lbl_1_rodata_29A4;
extern f64 lbl_1_rodata_2988;
extern const f32 lbl_1_rodata_2AA0[21];
extern u32 fn_1_620C8(void *);
extern const f32 lbl_1_rodata_2950;
extern f32 fn_1_8652C(s16);
extern void fn_1_557C4(void *);
extern void fn_1_56000(u8, u8, u8);
extern void fn_1_5621C(f32, f32, f32, f32);
extern void lbl_8006E14C(f32);
extern const f32 lbl_1_rodata_29C0;
extern const f32 lbl_1_rodata_29F0;
extern u32 fn_1_58C4(void);
extern const f64 lbl_1_rodata_2954;

/* fzgx:begin fn_1_58C6C */
#include "types.h"

struct fn_1_58C6C_lbl_1_bss_6C848_T {
    u8 unk_0;
    u8 pad_1[0x7];
    u32 unk_8;
    s16 unk_C;
    u8 pad_E[0xC];
    u16 unk_1A;
};
struct fn_1_58C6C_lbl_1_bss_6C84C_T {
    u8 unk_0;
    u8 pad_1[0x7];
    u32 unk_8;
    s16 unk_C;
    u8 pad_E[0xC];
    u16 unk_1A;
};

void fn_1_58C6C(void) {
    struct fn_1_58C6C_lbl_1_bss_6C848_T *var_r31;
    s32 var_r30;
    s32 var_r30_2;
    struct fn_1_58C6C_lbl_1_bss_6C84C_T *var_r31_2;

    var_r30 = 0xBE;
    var_r31 = (struct fn_1_58C6C_lbl_1_bss_6C848_T *)(*(struct fn_1_58C6C_lbl_1_bss_6C848_T **)((u8 *)(&(*(struct fn_1_58C6C_lbl_1_bss_6C848_T * *)&lbl_1_bss_6C848)) + 0));
    do {
        if (((s16) var_r31->unk_C == 0x19) && ((s8) var_r31->unk_0 != 0) && ((s32) var_r31->unk_1A != 0) && !(var_r31->unk_8 & 0x80000000)) {
            fn_1_620C8((void *)(var_r31));
        }
        var_r30 -= 1;
        var_r31 = (struct fn_1_58C6C_lbl_1_bss_6C848_T *)((u8 *)(var_r31) + 0xE8);
    } while (var_r30 > 0);
    var_r30_2 = 0xC8;
    var_r31_2 = (struct fn_1_58C6C_lbl_1_bss_6C84C_T *)(*(struct fn_1_58C6C_lbl_1_bss_6C84C_T **)((u8 *)(&(*(struct fn_1_58C6C_lbl_1_bss_6C84C_T * *)&lbl_1_bss_6C84C)) + 0));
    do {
        if (((s16) var_r31_2->unk_C == 0x19) && ((s8) var_r31_2->unk_0 != 0) && ((s32) var_r31_2->unk_1A != 0) && !(var_r31_2->unk_8 & 0x80000000)) {
            fn_1_620C8((void *)(var_r31_2));
        }
        var_r30_2 -= 1;
        var_r31_2 = (struct fn_1_58C6C_lbl_1_bss_6C84C_T *)((u8 *)(var_r31_2) + 0xE8);
    } while (var_r30_2 > 0);
}
/* fzgx:end fn_1_58C6C */

/* fzgx:begin fn_1_58D38 */
typedef struct fn_1_58D38_EffectEntry {
    s8 unk_00;
    u8 pad_01[7];
    u32 unk_08;
    s16 unk_0C;
    u8 pad_0E[0x0C];
    u16 unk_1A;
    u8 pad_1C[0xCC];
} fn_1_58D38_EffectEntry;

typedef struct fn_1_58D38_EffectState {
    fn_1_58D38_EffectEntry *unk_00;
    fn_1_58D38_EffectEntry *unk_04;
    u8 pad_08[8];
    u32 unk_10;
} fn_1_58D38_EffectState;

extern void fn_1_62360(fn_1_58D38_EffectEntry *arg0);

void fn_1_58D38(void) {
    fn_1_58D38_EffectState *state;
    s32 count;
    fn_1_58D38_EffectEntry *entry;
    u32 max_count;

    state = (fn_1_58D38_EffectState *)&lbl_1_bss_6C848;
    if (state->unk_00 != 0) {
        fn_1_3BDC(9);

        entry = state->unk_00;
        count = 190;
        do {
            if (entry->unk_0C == 25 &&
                (s32)entry->unk_00 != 0 &&
                entry->unk_1A != (s16)0 &&
                (entry->unk_08 & ~0x7fffffff) == 0) {
                fn_1_62360(entry);
            }
            count--;
            entry++;
        } while (count > 0);

        entry = state->unk_04;
        count = 200;
        do {
            if (entry->unk_0C == 25 &&
                (s32)entry->unk_00 != 0 &&
                entry->unk_1A != (s16)0 &&
                (entry->unk_08 & ~0x7fffffff) == 0) {
                fn_1_62360(entry);
            }
            count--;
            entry++;
        } while (count > 0);

        count = fn_1_3C18(9);
        max_count = state->unk_10;
        if (count > max_count) {
            max_count = count;
        }
        state->unk_10 = max_count;
    }
}
/* fzgx:end fn_1_58D38 */

/* fzgx:begin fn_1_58E3C noprologue */
#include "types.h"
#include "rel/main_rel/effect.h"

extern s32 fn_1_3FC58(void);
extern void *memcpy(void *dest, const void *src, u32 size);

typedef struct {
    s8 unk_0;
    u8 pad_1;
    s16 unk_2;
    s16 unk_4;
    u8 pad_6[6];
    s16 unk_C;
    u8 pad_E[0xDA];
} EffectEntry;

s16 fn_1_58E3C(void *source) {
    s32 i;

    if (fn_1_3FC58() != 0) {
        return -1;
    }

    {
        EffectEntry *scan;
        scan = *(EffectEntry **)&lbl_1_bss_6C848;
        i = 0;
        for (; i < 0xbe; i++, scan++) {
            if (!scan->unk_0) {
                scan->unk_0 = 1;
                /* The shared exit preserves the counted search result. */
                goto slot_found;
            }
        }
        i = -1;
    }
slot_found:
    if (i < 0) {
        return -1;
    }
    {
        EffectEntry *entry;
        entry = *(EffectEntry **)&lbl_1_bss_6C848 + i;
    memcpy(entry, source, 0xe8);
    entry->unk_0 = 1;
    entry->unk_2 = i;
    ((void (**)(void *))lbl_1_data_1D1D8)[entry->unk_C](entry);
    entry->unk_4 = lbl_1_bss_6C850.unk_0;
    lbl_1_bss_6C850.unk_0++;
    if (lbl_1_bss_6C850.unk_0 < 0) {
        lbl_1_bss_6C850.unk_0 = 0;
    }
        return entry->unk_4;
    }
}
/* fzgx:end fn_1_58E3C */

/* fzgx:begin fn_1_58F50 */



typedef struct {
    u8 unk_0;
    u8 pad_1[1];
    s16 unk_2;
    s16 unk_4;
    u8 pad_6[6];
    s16 unk_C;
    u8 pad_E[0xDA];
} fn_1_58F50_EffectEntry;

/* Allocate an effect entry, initialize it, and return its sequence number. */
s16 fn_1_58F50(const void *source) {
    fn_1_58F50_EffectEntry *entry;
    s32 index;
    u8 *cursor;

    if (fn_1_3FC8C() != 0) {
        return -1;
    }
    if (fn_1_3FC58() != 0) {
        return -1;
    }

    cursor = *(u8 **)&lbl_1_bss_6C848;
    index = 0;
    for (; index < 0xbe;) {
        if (*(s8 *)cursor == 0) {
            *cursor = 1;
            goto found; /* irreducible split between allocation and failure */
        }
        index++;
        cursor += 0xe8;
    }
    index = -1;
found:
    if (index < 0) {
        return -1;
    }

    entry = (fn_1_58F50_EffectEntry *)(*(u8 **)&lbl_1_bss_6C848) + index;
    memcpy(entry, source, 0xe8);
    entry->unk_0 = 1;
    entry->unk_2 = index;
    ((void (*)(void *))(*(u32 *)((*(u8 (*)[276])&lbl_1_data_1D1D8) + (entry->unk_C << 2))))(entry);

    entry->unk_4 = lbl_1_bss_6C850.unk_0;
    lbl_1_bss_6C850.unk_0++;
    if (lbl_1_bss_6C850.unk_0 < 0) {
        lbl_1_bss_6C850.unk_0 = 0;
    }
    return entry->unk_4;
}
/* fzgx:end fn_1_58F50 */

/* fzgx:begin fn_1_59078 */
s16 fn_1_59078(Obj_1_bss_6C84C_Target *arg0) {
    Obj_1_bss_6C84C_Target *obj;
    s32 i;

    if (fn_1_3FC8C() != 0) {
        return -1;
    }
    if (fn_1_3FC58() != 0) {
        return -1;
    }

    obj = lbl_1_bss_6C84C;
    for (i = 0; i < 0xbe; i++, obj++) {
        if ((s8)obj->unk_0 == 0) {
            obj->unk_0 = 1;
            // Skip the exhaustion path when a free slot is found.
            goto slot_found;
        }
    }
    i = -1;
slot_found:
    if (i < 0) {
        return -1;
    }

    obj = lbl_1_bss_6C84C + i;
    memcpy(obj, arg0, 0xe8);
    obj->unk_0 = 1;
    obj->unk_2 = i;
    ((void (**)(Obj_1_bss_6C84C_Target *))lbl_1_data_1D1D8)[obj->unk_C](obj);
    obj->unk_4 = lbl_1_bss_6C850.unk_0;
    lbl_1_bss_6C850.unk_0++;
    if (lbl_1_bss_6C850.unk_0 < 0) {
        lbl_1_bss_6C850.unk_0 = 0;
    }
    return obj->unk_4;
}
/* fzgx:end fn_1_59078 */

/* fzgx:begin fn_1_59290 */
void fn_1_59290(void) {
    u8 buffer1[0xe8];
    u8 buffer2[0xe8];
    int count;
    Obj_1_bss_6C84C_Target *effect;
    Obj_1_bss_6C84C_Target *effects;

    effects = *(Obj_1_bss_6C84C_Target **)(void *)&lbl_1_bss_6C848;
    effect = effects;
    count = 0xbe;
    for (; count > 0; count--, effect++) {
        if ((s8)effect->unk_0 != 0) {
            if (effect->unk_C == 1) {
                fn_80008BEC(buffer1, 0, 0xe8);
                *(s16 *)(buffer1 + 0x4) = effect->unk_4;
                buffer1[0] = effect->unk_0;
                *(s16 *)(buffer1 + 0xc) = effect->unk_C;
                *(u32 *)(buffer1 + 0x38) = effect->unk_38;
                *(u32 *)(buffer1 + 0x34) = effect->unk_34;
                *(u16 *)(buffer1 + 0x1a) = effect->unk_1A;
                *(s16 *)(buffer1 + 0x18) = effect->unk_18;
                fn_80008BEC(effect, 0, 0xe8);
                fn_80008BA8(effect, buffer1, 0xe8);
            } else if (effect->unk_C != 4) {
                effect->unk_0 = 3;
                effect->unk_8 |= (u32)1 << 31;
            }
        }
    }

    effects = lbl_1_bss_6C84C;
    effect = effects;
    count = 0xc8;
    for (; count > 0; count--, effect++) {
        if ((s8)effect->unk_0 != 0) {
            if (effect->unk_C == 1) {
                fn_80008BEC(buffer2, 0, 0xe8);
                *(s16 *)(buffer2 + 0x4) = effect->unk_4;
                buffer2[0] = effect->unk_0;
                *(s16 *)(buffer2 + 0xc) = effect->unk_C;
                *(u32 *)(buffer2 + 0x38) = effect->unk_38;
                *(u32 *)(buffer2 + 0x34) = effect->unk_34;
                *(u16 *)(buffer2 + 0x1a) = effect->unk_1A;
                *(s16 *)(buffer2 + 0x18) = effect->unk_18;
                fn_80008BEC(effect, 0, 0xe8);
                fn_80008BA8(effect, buffer2, 0xe8);
            } else if (effect->unk_C != 4) {
                effect->unk_0 = 3;
                effect->unk_8 |= (u32)1 << 31;
            }
        }
    }
}
/* fzgx:end fn_1_59290 */

/* fzgx:begin fn_1_5942C */
// fn_1_5942C: wrapper that calls fn_1_680F8
void fn_1_5942C(void) {
    fn_1_680F8();
}
/* fzgx:end fn_1_5942C */

/* fzgx:begin fn_1_5944C */
void fn_1_5944C(void) {
    fn_1_68284();
}
/* fzgx:end fn_1_5944C */

/* fzgx:begin fn_1_5946C */
void fn_1_5946C(void) {
    fn_1_68B68();
}
/* fzgx:end fn_1_5946C */

/* fzgx:begin fn_1_5948C */
void fn_1_5948C(void) {
    fn_1_68248();
}
/* fzgx:end fn_1_5948C */

/* fzgx:begin fn_1_594AC */
void fn_1_594AC(void) {
    fn_1_69BBC();
}
/* fzgx:end fn_1_594AC */

/* fzgx:begin fn_1_594CC */
void fn_1_594CC(void) {
    fn_1_69BCC();
}
/* fzgx:end fn_1_594CC */

/* fzgx:begin fn_1_594EC */
// fn_1_594EC: empty in retail (single blr).
void fn_1_594EC(void) {
}
/* fzgx:end fn_1_594EC */

/* fzgx:begin fn_1_594F0 */
// fn_1_594F0: empty in retail (single blr).
void fn_1_594F0(void) {
}
/* fzgx:end fn_1_594F0 */

/* fzgx:begin fn_1_594F4 */
// fn_1_594F4: empty in retail (single blr).
void fn_1_594F4(void) {
}
/* fzgx:end fn_1_594F4 */

/* fzgx:begin fn_1_594F8 */
// fn_1_594F8: empty in retail (single blr).
void fn_1_594F8(void) {
}
/* fzgx:end fn_1_594F8 */

/* fzgx:begin fn_1_594FC */
// fn_1_594FC: empty in retail (single blr).
void fn_1_594FC(void) {
}
/* fzgx:end fn_1_594FC */

/* fzgx:begin fn_1_59500 */
// fn_1_59500: empty in retail (single blr).
void fn_1_59500(void) {
}
/* fzgx:end fn_1_59500 */

/* fzgx:begin fn_1_59504 */
// fn_1_59504: empty in retail (single blr).
void fn_1_59504(void) {
}
/* fzgx:end fn_1_59504 */

/* fzgx:begin fn_1_59508 */
// fn_1_59508: empty in retail (single blr).
void fn_1_59508(void) {
}
/* fzgx:end fn_1_59508 */

/* fzgx:begin fn_1_5950C */
// fn_1_5950C: empty in retail (single blr).
void fn_1_5950C(void) {
}
/* fzgx:end fn_1_5950C */

/* fzgx:begin fn_1_59510 */
// fn_1_59510: empty in retail (single blr).
void fn_1_59510(void) {
}
/* fzgx:end fn_1_59510 */

/* fzgx:begin fn_1_59514 */
extern u32 lbl_1_data_1D628;

void fn_1_59514(void *obj) {
    if (*(s32 *)((u8 *)obj + 0x10) == 0) {
        u32 s = lbl_1_data_1D628 * 0x41c64e6d + 0x3039;
        u32 r;
        lbl_1_data_1D628 = s;
        r = (s >> 16) & 0x7fff;
        *(s32 *)((u8 *)obj + 0x10) = (s32)(60.0f * (0.1f + (f32)r / 32767.0f));
    }

    {
        f32 t = fn_1_8652C(*(s16 *)((u8 *)obj + 0x18));
        u32 s = lbl_1_data_1D628 * 0x41c64e6d + 0x3039;
        u32 r;
        lbl_1_data_1D628 = s;
        r = (s >> 16) & 0x7fff;
        *(f32 *)((u8 *)obj + 0x94) = 0.05f * ((f32)r / 32767.0f);
        *(f32 *)((u8 *)obj + 0x98) = (f32)(0.07 + t / 20000.0f);
    }
}
/* fzgx:end fn_1_59514 */

/* fzgx:begin fn_1_59A70 */
// fn_1_59A70: empty in retail (single blr).
void fn_1_59A70(void) {
}
/* fzgx:end fn_1_59A70 */

/* fzgx:begin fn_1_59CC4 */
// fn_1_59CC4: empty in retail (single blr).
void fn_1_59CC4(void) {
}
/* fzgx:end fn_1_59CC4 */

/* fzgx:begin fn_1_5A8CC */
// fn_1_5A8CC: empty in retail (single blr).
void fn_1_5A8CC(void) {
}
/* fzgx:end fn_1_5A8CC */

/* fzgx:begin fn_1_5A8D0 */
typedef struct {
    u8 pad[0x10];
    s32 field_10;
} Fn1_5A8D0Data;

void fn_1_5A8D0(Fn1_5A8D0Data *data) {
    data->field_10 = 2;
}
/* fzgx:end fn_1_5A8D0 */

/* fzgx:begin fn_1_5ABC4 */
// fn_1_5ABC4: empty in retail (single blr).
void fn_1_5ABC4(void) {
}
/* fzgx:end fn_1_5ABC4 */

/* fzgx:begin fn_1_5ABC8 */
// fn_1_5ABC8: empty in retail (single blr).
void fn_1_5ABC8(void) {
}
/* fzgx:end fn_1_5ABC8 */

/* fzgx:begin fn_1_5B074 */
// fn_1_5B074: empty in retail (single blr).
void fn_1_5B074(void) {
}
/* fzgx:end fn_1_5B074 */

/* fzgx:begin fn_1_5B30C */
#include "types.h"

struct fn_1_5B30C_Arg0 {
    u8 pad_0[0x34];
    u32 unk_34;
};

extern s32 fn_1_54E34(void *, f32);
extern void lbl_8006D7B0(void);
extern void lbl_8006D9D8(void *);
extern void mathutil_mtxA_rotate_z(int);

void fn_1_5B30C(struct fn_1_5B30C_Arg0 *arg0) {
    u32 v0;
    u32 v1;
    f32 v2;
    u32 t3;
    v0 = arg0->unk_34;
    lbl_8006D9D8((void *)((u32)arg0 + 60));
    lbl_8006D7B0();
    lbl_8006E14C((*(f32 *)((u8 *)(u32)arg0 + 40) / *(f32 *)((u8 *)v0 + 20)));
    t3 = fn_1_54E34((void *)(v0 + 8), *(f32 *)((u8 *)(u32)arg0 + 40));
    v1 = t3;
    if ((s32)t3 != 0) {
    v1 = *(s16 *)((u8 *)(u32)arg0 + 88);
    mathutil_mtxA_rotate_z(v1);
    v2 = *(f32 *)((u8 *)(u32)arg0 + 28);
    fn_1_5621C(v2, *(f32 *)((u8 *)(u32)arg0 + 32), *(f32 *)((u8 *)(u32)arg0 + 36), *(f32 *)((u8 *)(u32)arg0 + 180));
    v1 = 1;
    fn_1_56000(v1, 3, 0);
    v1 = v0;
    fn_1_557C4((void *)v1);
    v2 = (*(f32 *)&lbl_1_rodata_2978);
    fn_1_5621C(v2, v2, v2, v2);
    v1 = 1;
    fn_1_56000(v1, 3, 1);
    }
}
/* fzgx:end fn_1_5B30C */

/* fzgx:begin fn_1_5B3CC */
// fn_1_5B3CC: empty in retail (single blr).
void fn_1_5B3CC(void) {
}
/* fzgx:end fn_1_5B3CC */

/* fzgx:begin fn_1_5B6F0 */
// fn_1_5B6F0: empty in retail (single blr).
void fn_1_5B6F0(void) {
}
/* fzgx:end fn_1_5B6F0 */

/* fzgx:begin fn_1_5B780 */
typedef struct Fn15B780 {
    u8 state;
    u8 _pad01[0x0f];
    int current;
    int maximum;
    u8 _pad18[0x94];
    s16 step;
    u8 _padAE[0x04];
    f32 result;
} Fn15B780;

void fn_1_5B780(Fn15B780 *effect) {
    effect->state = 2;
    if (effect->current <= effect->maximum) {
        effect->step += 2;
        if (effect->step >= 14) {
            effect->step = 14;
        }
    }
    effect->result = lbl_1_rodata_29A4 * (f32)effect->current;
}
/* fzgx:end fn_1_5B780 */

/* fzgx:begin fn_1_5BF6C */
// fn_1_5BF6C: empty in retail (single blr).
void fn_1_5BF6C(void) {
}
/* fzgx:end fn_1_5BF6C */

/* fzgx:begin fn_1_5BFF0 */
struct fn_1_5BFF0_Arg0 {
    u8 unk_0;
    u8 pad_1[0xF];
    u32 unk_10;
    u8 pad_14[0x98];
    s16 unk_AC;
    u8 pad_AE[0x6];
    f32 unk_B4;
};

void fn_1_5BFF0(struct fn_1_5BFF0_Arg0 *arg0) {
    arg0->unk_0 = 2;
    arg0->unk_AC += 2;
    if (arg0->unk_AC >= 15) {
    arg0->unk_AC = 15;
    }
    arg0->unk_B4 = (lbl_1_rodata_29A4 * (f32)(s32)arg0->unk_10);
}
/* fzgx:end fn_1_5BFF0 */

/* fzgx:begin fn_1_5C780 */
// fn_1_5C780: empty in retail (single blr).
void fn_1_5C780(void) {
}
/* fzgx:end fn_1_5C780 */

/* fzgx:begin fn_1_5D010 */
// fn_1_5D010: empty in retail (single blr).
void fn_1_5D010(void) {
}
/* fzgx:end fn_1_5D010 */

/* fzgx:begin fn_1_5D014 */
typedef struct Fn1_5D014Object {
    u8 pad[0xae];
    s16 field_ae;
} Fn1_5D014Object;

void fn_1_5D014(Fn1_5D014Object *obj) {
    obj->field_ae = 0;
}
/* fzgx:end fn_1_5D014 */

/* fzgx:begin fn_1_5D374 */
// fn_1_5D374: empty in retail (single blr).
void fn_1_5D374(void) {
}
/* fzgx:end fn_1_5D374 */

/* fzgx:begin fn_1_5D4FC */
// fn_1_5D4FC: empty in retail (single blr).
void fn_1_5D4FC(void) {
}
/* fzgx:end fn_1_5D4FC */

/* fzgx:begin fn_1_5D88C */
struct Fn15D88C {
    u8 _pad08[0x08];
    u32 flags;
    u8 _pad0c[0x1c];
    f32 value28;
    u8 _pad2c[0x08];
    u32 enabled;
    u8 _pad38[0x1c];
    u16 value54;
    u16 value56;
    u16 value58;
    u8 _pad5a[0x5a];
    f32 value_b4;
};

void fn_1_5D88C(struct Fn15D88C *self) {
    self->value_b4 = lbl_1_rodata_29AC[0];
    if (self->enabled != 0) {
        f32 value28;
        lbl_1_data_1D628 = lbl_1_data_1D628 * 1103515245 + 12345;
        value28 = lbl_1_rodata_2978[0];
        self->value54 = (u16)((lbl_1_data_1D628 >> 16) & 0x7fff);
        lbl_1_data_1D628 = lbl_1_data_1D628 * 1103515245 + 12345;
        self->value56 = (u16)((lbl_1_data_1D628 >> 16) & 0x7fff);
        lbl_1_data_1D628 = lbl_1_data_1D628 * 1103515245 + 12345;
        self->value58 = (u16)((lbl_1_data_1D628 >> 16) & 0x7fff);
        self->value28 = value28;
    }
    self->flags |= 0x40000000;
}
/* fzgx:end fn_1_5D88C */

/* fzgx:begin fn_1_5D918 */
// fn_1_5D918: empty in retail (single blr).
void fn_1_5D918(void) {
}
/* fzgx:end fn_1_5D918 */

/* fzgx:begin fn_1_5EB08 */
#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/effect.h"

typedef struct FnObj {
    u8 pad18[0x18];
    s16 value;
    u8 pad3c[0x22];
    f32 field3c;
} FnObj;

typedef struct FnLocal {
    u8 data[0x10];
} FnLocal;

typedef struct FnNode {
    u8 pad4[4];
    void (*callback)(void);
    FnObj *object;
} FnNode;

void fn_1_5EB08(FnObj *object) {
    FnLocal local;
    FnNode *node;
    FnNode *allocated;

    fn_1_862D4(object->value, &local);
    lbl_8006DCA4();
    if (fn_1_54E34(&object->field3c, lbl_1_rodata_2AF4[0])) {
        node = fn_1_5448C(&local);
        allocated = fn_1_548AC(0xc);
        if (allocated != 0) {
            allocated->callback = fn_1_5EB98;
            allocated->object = object;
            fn_1_5489C(node, allocated);
        }
    }
}
/* fzgx:end fn_1_5EB08 */

/* fzgx:begin fn_1_5F5C4 */
// fn_1_5F5C4: empty in retail (single blr).
void fn_1_5F5C4(void) {
}
/* fzgx:end fn_1_5F5C4 */

/* fzgx:begin fn_1_5FE24 */
// fn_1_5FE24: empty in retail (single blr).
void fn_1_5FE24(void) {
}
/* fzgx:end fn_1_5FE24 */

/* fzgx:begin fn_1_5FE28 */
// fn_1_5FE28: empty in retail (single blr).
void fn_1_5FE28(void) {
}
/* fzgx:end fn_1_5FE28 */

/* fzgx:begin fn_1_5FE2C */
// fn_1_5FE2C: empty in retail (single blr).
void fn_1_5FE2C(void) {
}
/* fzgx:end fn_1_5FE2C */

/* fzgx:begin fn_1_5FE30 */
#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/effect.h"

typedef struct {
    u8 unk[0x18];
    s16 value;
    u8 unk1A[0x0E];
    f32 rate;
    u8 unk2C[0x10];
    u8 field3C[1];
} fn_1_5FE30_FZeroObject;

typedef struct {
    u8 unk0[4];
    void (*callback)(void);
    fn_1_5FE30_FZeroObject *owner;
} FZeroEvent;

void fn_1_5FE30(fn_1_5FE30_FZeroObject *object) {
    u8 result[8];
    void *callback;
    FZeroEvent *event;

    fn_1_862D4(object->value, result);
    lbl_8006DCA4();
    if (fn_1_54E34(object->field3C, object->rate) != 0) {
        callback = fn_1_5448C(result);
        event = (FZeroEvent *)fn_1_548AC(12);
        if (event != 0) {
            event->callback = fn_1_5FEBC;
            event->owner = object;
            fn_1_5489C(callback, event);
        }
    }
}
/* fzgx:end fn_1_5FE30 */

/* fzgx:begin fn_1_5FEBC noprologue */
#include "types.h"

typedef struct {
    u8 unk00[0x18];
    s16 value18;
    u8 unk1A[2];
    f32 value1C;
    f32 value20;
    f32 value24;
    f32 value28;
    u8 unk2C[8];
    void *field34;
    u8 unk38[0x1c];
    s16 value54;
    s16 value56;
} EffectData;

typedef struct {
    u8 unk00[8];
    EffectData *data;
} EffectObject;

extern void fn_1_867CC(s16 value, void *result);
extern void lbl_8006D9D8(void *result);
extern void lbl_8006D7B0(void);
extern void mathutil_mtxA_rotate_y(s16 value);
extern void mathutil_mtxA_rotate_x(s16 value);
extern void lbl_8006DB74(void *result);
extern void fn_1_9F914(void *data, void *owner);
extern const f32 lbl_1_rodata_2AA0[21];
extern const f32 lbl_1_rodata_29AC[5];
extern void *memset(void *ptr, int value, u32 size);

void fn_1_5FEBC(EffectObject *object) {
    u8 result[12];
    u8 data[64];
    EffectData *effect;
    void *owner;
    f32 color_scale;
    f32 size;

    effect = object->data;
    fn_1_867CC(effect->value18, result);
    owner = effect->field34;
    lbl_8006D9D8(result);
    lbl_8006D7B0();
    mathutil_mtxA_rotate_y(effect->value56);
    mathutil_mtxA_rotate_x(effect->value54);
    memset(data, 0, 64);
    lbl_8006DB74(data + 8);
    size = lbl_1_rodata_2AA0[0];
    size = size * effect->value28;
    *(f32 *)(data + 0) = size;
    color_scale = lbl_1_rodata_29AC[0];
    data[60] = (u8)(s32)(color_scale * effect->value1C);
    data[61] = (u8)(s32)(color_scale * effect->value20);
    data[62] = (u8)(s32)(color_scale * effect->value24);
    data[63] = 0xff;
    *(f32 *)(data + 4) = size;
    fn_1_9F914(data, owner);
}
/* fzgx:end fn_1_5FEBC */

/* fzgx:begin fn_1_5FFAC */
// fn_1_5FFAC: empty in retail (single blr).
void fn_1_5FFAC(void) {
}
/* fzgx:end fn_1_5FFAC */

/* fzgx:begin fn_1_60170 */
typedef struct {
    u8 unk[0x38];
    void *field38;
} fn_1_60170_FZeroObject;

// Submit the effect data when this object has an associated field.
void fn_1_60170(fn_1_60170_FZeroObject *object) {
    if (object->field38 != 0) {
        fn_1_46B4((u32)lbl_801A6410, object->field38, lbl_1_data_1D62C, 0x1261);
    }
}
/* fzgx:end fn_1_60170 */

/* fzgx:begin fn_1_601B4 */
#include "types.h"
#include "rel/main_rel/effect.h"

typedef struct {
    u8 unk_0[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 unk_18[0x24];
    f32 unk_3c;
    f32 unk_40;
    f32 unk_44;
    f32 unk_48;
    f32 unk_4c;
    f32 unk_50;
    u8 unk_54[0x60];
    f32 unk_b4;
} EffectState;

extern u32 lbl_1_bss_6C86C;

void fn_1_601B4(EffectState *effect) {
    f32 factor;

    effect->unk_14--;
    if (effect->unk_14 > 0) {
        factor = lbl_1_rodata_29C0;
        effect->unk_48 *= factor;
        effect->unk_4c *= factor;
        effect->unk_50 *= factor;
        effect->unk_3c += effect->unk_48;
        effect->unk_40 += effect->unk_4c;
        effect->unk_44 += effect->unk_50;
        effect->unk_b4 = lbl_1_rodata_29F0;
    } else {
        s32 numerator = effect->unk_10;
        s32 denominator = lbl_1_bss_6C86C;

        effect->unk_b4 = (f32)numerator / (f32)denominator;
    }
}
/* fzgx:end fn_1_601B4 */

/* fzgx:begin fn_1_60C70 */
// fn_1_60C70: empty in retail (single blr).
void fn_1_60C70(void) {
}
/* fzgx:end fn_1_60C70 */

/* fzgx:begin fn_1_60C74 */
struct Effect {
    u8 _pad[0x28];
    f32 field_28;
};

void fn_1_60C74(struct Effect *effect) {
    effect->field_28 = lbl_1_rodata_2A5C[0];
}
/* fzgx:end fn_1_60C74 */

/* fzgx:begin fn_1_60C84 */
// fn_1_60C84: empty in retail (single blr).
void fn_1_60C84(void) {
}
/* fzgx:end fn_1_60C84 */

/* fzgx:begin fn_1_60F7C */
// fn_1_60F7C: empty in retail (single blr).
void fn_1_60F7C(void) {
}
/* fzgx:end fn_1_60F7C */

/* fzgx:begin fn_1_60F80 */
// fn_1_60F80: empty in retail (single blr).
void fn_1_60F80(void) {
}
/* fzgx:end fn_1_60F80 */

/* fzgx:begin fn_1_61760 */
struct Fn1_61760Object {
    u8 _pad38[0x38];
    void *effect_resource;
};

// Dispatches the object's effect resource when one is available.
void fn_1_61760(struct Fn1_61760Object *object) {
    if (object->effect_resource != 0) {
        fn_1_46B4((u32)lbl_801A6410, object->effect_resource, lbl_1_data_1D62C, 0x16c1);
    }
}
/* fzgx:end fn_1_61760 */

/* fzgx:begin fn_1_61C84 */
// fn_1_61C84: empty in retail (single blr).
void fn_1_61C84(void) {
}
/* fzgx:end fn_1_61C84 */

/* fzgx:begin fn_1_61C88 */
void fn_1_61C88(void) {
    fn_1_61D08();
}
/* fzgx:end fn_1_61C88 */

/* fzgx:begin fn_1_61CA8 */
void fn_1_61CA8(void) {
    fn_1_61EF4();
}
/* fzgx:end fn_1_61CA8 */

/* fzgx:begin fn_1_61CC8 */
void fn_1_61CC8(void) {
    fn_1_620C4();
}
/* fzgx:end fn_1_61CC8 */

/* fzgx:begin fn_1_61CE8 */
void fn_1_61CE8(void) {
    fn_1_61E60();
}
/* fzgx:end fn_1_61CE8 */

/* fzgx:begin fn_1_61E60 noprologue */
#include "types.h"

extern u8 lbl_1_data_1D62C[0x94];
extern void *lbl_801A6410;
extern void fn_1_46B4(u32 value, void *field, u8 *data, s32 code);
extern void fn_1_4730(void *arg0, void *arg1, int arg2, u8 *arg3, int arg4);

typedef struct {
    u8 pad20[0x20];
    void *unk_20;
} Fn1_61E60Node;

typedef struct {
    u8 pad38[0x38];
    Fn1_61E60Node *unk_38;
} Fn1_61E60Object;

// Releases the effect resources and clears the active effect references.
int fn_1_61E60(Fn1_61E60Object *object) {
    Fn1_61E60Node *node = object->unk_38;

    if (node != 0) {
        fn_1_4730(lbl_801A6410, node->unk_20, 1, lbl_1_data_1D62C, 0x17D5);
        node->unk_20 = 0;
        fn_1_46B4((u32)lbl_801A6410, object->unk_38, lbl_1_data_1D62C, 0x17D8);
        object->unk_38 = 0;
    }

    return 1;
}
/* fzgx:end fn_1_61E60 */

/* fzgx:begin fn_1_620C4 */
// fn_1_620C4: empty in retail (single blr).
void fn_1_620C4(void) {
}
/* fzgx:end fn_1_620C4 */

/* fzgx:begin fn_1_6312C */
// fn_1_6312C: empty in retail (single blr).
void fn_1_6312C(void) {
}
/* fzgx:end fn_1_6312C */

/* fzgx:begin fn_1_63130 */
struct fn_1_63130_obj {
    u8 unk_00[0xAE];
    s16 unk_AE;
};

void fn_1_63130(struct fn_1_63130_obj *obj) {
    obj->unk_AE = 0;
}
/* fzgx:end fn_1_63130 */

/* fzgx:begin fn_1_632D4 noprologue */
#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/effect.h"

extern f32 lbl_1_rodata_2AA0[21];
extern f32 lbl_1_rodata_29AC[5];
extern void lbl_8006DCA4(void *obj);
extern void lbl_8006E1B0(void *src, void *dst);
extern void lbl_8006D7DC(void *obj);
extern void mathutil_mtxA_rotate_z(s16 value);
extern void lbl_8006DB74(void *obj);
extern void fn_1_9F914(void *data, int value);

struct fn_1_632D4_obj {
    u8 unk_00[0x1C];
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
    u8 unk_2C[0x8];
    int unk_34;
    u8 unk_38[0x4];
    void *unk_3C;
    u8 unk_40[0x6E];
    s16 unk_AE;
};

struct fn_1_632D4_data {
    f32 unk_00;
    f32 unk_04;
    u8 unk_08[0x34];
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
};

void fn_1_632D4(struct fn_1_632D4_obj *obj) {
    struct fn_1_632D4_value { s32 a, b, c; } value;
    struct fn_1_632D4_data data;
    int id;
    s32 red;
    s32 green;
    s32 blue;
    f32 color_scale;
    f32 size;

    id = obj->unk_34;
    lbl_8006DCA4(obj);
    lbl_8006E1B0(&obj->unk_3C, &value);
    lbl_8006D7DC(&value);
    mathutil_mtxA_rotate_z(obj->unk_AE);
    memset(&data, 0, 0x40);
    lbl_8006DB74(&data.unk_08);

    size = lbl_1_rodata_2AA0[0];
    size = size * obj->unk_28;
    data.unk_00 = size;
    color_scale = lbl_1_rodata_29AC[0];
    red = color_scale * obj->unk_1C;
    data.red = red;
    green = color_scale * obj->unk_20;
    data.green = green;
    blue = color_scale * obj->unk_24;
    data.alpha = 0xff;
    data.unk_04 = size;
    data.blue = blue;

    fn_1_9F914(&data, id);
}
/* fzgx:end fn_1_632D4 */

/* fzgx:begin fn_1_633BC */
// fn_1_633BC: empty in retail (single blr).
void fn_1_633BC(void) {
}
/* fzgx:end fn_1_633BC */

/* fzgx:begin fn_1_63514 */
// fn_1_63514: empty in retail (single blr).
void fn_1_63514(void) {
}
/* fzgx:end fn_1_63514 */

/* fzgx:begin fn_1_63518 */
typedef struct Effect_63518_vec {
    u32 x;
    u32 y;
    u32 z;
} Effect_63518_vec;

typedef struct Effect_63518 {
    u8 unk00[0x14];
    u32 unk14;
    u8 unk18[0x20];
    Effect_63518_vec *unk38;
    Effect_63518_vec unk3c;
    u8 unk48[0x10];
    u16 unk58;
    u8 unk5a[0x06];
    Effect_63518_vec unk60;
    u8 unk6c[0x40];
    u16 unkac;
    u16 unkae;
    u16 unkb0;
} Effect_63518;

void fn_1_63518(Effect_63518 *effect) {
    Effect_63518_vec *dst;
    u32 i;

    effect->unk14 = 0;
    effect->unkac = 0;
    effect->unkae = 0;
    effect->unkb0 = 0;
    effect->unk58 = 0;

    effect->unk60 = effect->unk3c;
    dst = effect->unk38;

    for (i = 0; i < fn_1_58C4() * 8; i++) {
        *dst++ = effect->unk3c;
    }
}
/* fzgx:end fn_1_63518 */

/* fzgx:begin fn_1_63858 */
struct LocalData {
    u8 data[0x10];
};

struct Event {
    u8 data[4];
    void (*callback)(void);
    void *owner;
};

struct Object {
    u8 data[0x18];
    s16 value;
};

void fn_1_63858(struct Object *object) {
    struct LocalData local;
    struct Event *event;
    void *target;

    fn_1_862D4(object->value, &local);
    lbl_8006DCA4();
    if (fn_1_54E34(&local, lbl_1_rodata_2B2C[0]) != 0) {
        target = fn_1_5448C(&local);
        event = (struct Event *)fn_1_548AC(0xc);
        if (event != 0) {
            event->callback = fn_1_638E8;
            event->owner = object;
            fn_1_5489C(target, event);
        }
    }
}
/* fzgx:end fn_1_63858 */

/* fzgx:begin fn_1_64098 */
typedef struct Fn164098Object {
    u8 pad[0xae];
    u16 value;
} Fn164098Object;

void fn_1_64098(Fn164098Object *object) {
    object->value = 0;
}
/* fzgx:end fn_1_64098 */

/* fzgx:begin fn_1_642E8 */
typedef struct fn_1_642E8_EffectState {
    char bytes[0x14];
} fn_1_642E8_EffectState;

typedef struct fn_1_642E8_EffectObject {
    char pad0[0x28];
    f32 value;
    char pad2c[0x10];
    fn_1_642E8_EffectState state;
} fn_1_642E8_EffectObject;

typedef struct EffectNode {
    char pad0[4];
    void (*callback)(void);
    void *owner;
} EffectNode;

void fn_1_642E8(fn_1_642E8_EffectObject *self) {
    f32 value;
    void *state;
    EffectNode *node;

    value = self->value / lbl_1_rodata_2A70[0];
    lbl_8006DCA4();
    if (fn_1_54E34(&self->state, value)) {
        state = fn_1_5448C(&self->state);
        node = fn_1_548AC(0xc);
        if (node != 0) {
            node->callback = fn_1_64388;
            node->owner = self;
            fn_1_5489C(state, node);
        }
    }
}
/* fzgx:end fn_1_642E8 */

/* fzgx:begin fn_1_645C8 */
// fn_1_645C8: empty in retail (single blr).
void fn_1_645C8(void) {
}
/* fzgx:end fn_1_645C8 */

/* fzgx:begin fn_1_645CC */
// fn_1_645CC: empty in retail (single blr).
void fn_1_645CC(void) {
}
/* fzgx:end fn_1_645CC */

/* fzgx:begin fn_1_645D0 */
// fn_1_645D0: empty in retail (single blr).
void fn_1_645D0(void) {
}
/* fzgx:end fn_1_645D0 */

/* fzgx:begin fn_1_648D4 */
// fn_1_648D4: empty in retail (single blr).
void fn_1_648D4(void) {
}
/* fzgx:end fn_1_648D4 */

/* fzgx:begin fn_1_648D8 */
// fn_1_648D8: empty in retail (single blr).
void fn_1_648D8(void) {
}
/* fzgx:end fn_1_648D8 */

/* fzgx:begin fn_1_65268 */
typedef struct {
    u32 pad_00;
    void (*vtable)(void);
    void *owner;
} Event;

typedef struct {
    u8 pad_00[0x18];
    s16 value;
    u8 pad_1a[0xe];
    f32 amount;
    u8 pad_2c[0x10];
    u8 embedded[1];
} Object;

void fn_1_65268(Object *object) {
    u8 local[4];
    void *result;
    Event *event;

    fn_1_862D4(object->value, local);
    lbl_8006DCA4();
    if (fn_1_54E34(&object->embedded[0], object->amount) != 0) {
        result = fn_1_5448C(local);
        event = (Event *)fn_1_548AC(0xc);
        if (event != 0) {
            event->vtable = fn_1_652F4;
            event->owner = object;
            fn_1_5489C(result, event);
        }
    }
}
/* fzgx:end fn_1_65268 */

/* fzgx:begin fn_1_652F4 noprologue */
#include "types.h"
#include "rel/main_rel/effect.h"

extern void fn_1_867CC(s16 value, void *out);
extern void *fn_1_868C0(s8 value);
extern void *fn_1_86254(s16 value);
extern void lbl_8006D9D8(void *out);
extern void lbl_8006D95C(s16 value);
extern void mathutil_mtxA_rotate_x(s16 value);
extern void lbl_8006DB74(void *out);
extern void fn_1_9F914(void *data, void *owner);
extern f32 lbl_1_rodata_2AA0[21];
extern f32 lbl_1_rodata_29AC[5];

typedef struct {
    u8 pad_00[0x8];
    void *unk_08;
} Effect;
typedef struct {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1a[2];
    f32 unk_1c;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
    u8 pad_2c[0x28];
    s16 unk_54;
    s16 unk_56;
} EffectData;
typedef struct {
    u8 pad_00[0x120];
    void *unk_120;
} EffectRoot;
typedef struct {
    f32 value;
    f32 value2;
    u8 pad_08[0x34];
    u8 color[4];
} ParticleData;

#pragma opt_common_subs off
void fn_1_652F4(Effect *effect) {
    u8 temp[0xc];
    ParticleData data;
    EffectData *object;
    void *owner;
    register f32 color_scale;
    register f32 scale;
    void *manager;
    s16 level;

    object = effect->unk_08;
    fn_1_867CC(object->unk_18, temp);
    level = *(s16 *)((u8 *)fn_1_868C0((s8)object->unk_18) + 0x3ba);
    owner = fn_1_86254(object->unk_18);
    if (level >= 3 && *(s8 *)((u8 *)owner + 0x475) == -1) {
        return;
    }
    manager = ((EffectRoot *)lbl_1_bss_38458->unk_8)->unk_120;
    lbl_8006D9D8(temp);
    lbl_8006D95C(object->unk_56);
    mathutil_mtxA_rotate_x(object->unk_54);
    memset(&data, 0, 0x40);
    lbl_8006DB74((u8 *)&data + 8);

        scale = lbl_1_rodata_2AA0[0];
        data.value = scale * object->unk_28;
    color_scale = lbl_1_rodata_29AC[0];
    data.color[0] = (u8)(s32)(color_scale * object->unk_1c);
    data.color[1] = (u8)(s32)(color_scale * object->unk_20);
    data.color[2] = (u8)(s32)(color_scale * object->unk_24);
    data.color[3] = 0xff;
    data.value2 = data.value;
    fn_1_9F914(&data, manager);
}
#pragma opt_common_subs reset
/* fzgx:end fn_1_652F4 */

/* fzgx:begin fn_1_65420 */
// fn_1_65420: empty in retail (single blr).
void fn_1_65420(void) {
}
/* fzgx:end fn_1_65420 */

/* fzgx:begin fn_1_656C8 */
typedef struct {
    u32 unk_00;
    void (*unk_04)(void);
    void *unk_08;
} EffectEvent;

typedef struct {
    u8 unk_00[0x28];
    f32 unk_28;
    u8 unk_2c[0x10];
    u8 unk_3c[1];
} fn_1_656C8_EffectObject;

// Initializes the effect and queues an event when its embedded state is ready.
void fn_1_656C8(fn_1_656C8_EffectObject *object) {
    void *result;
    EffectEvent *event;

    lbl_8006DCA4();
    if (fn_1_54E34(&object->unk_3c, object->unk_28) != 0) {
        result = fn_1_5448C(&object->unk_3c);
        event = (EffectEvent *)fn_1_548AC(0xc);
        if (event != 0) {
            event->unk_04 = fn_1_65748;
            event->unk_08 = object;
            fn_1_5489C(result, event);
        }
    }
}
/* fzgx:end fn_1_656C8 */

/* fzgx:begin fn_1_65AAC */
// fn_1_65AAC: empty in retail (single blr).
void fn_1_65AAC(void) {
}
/* fzgx:end fn_1_65AAC */

/* fzgx:begin fn_1_65B58 */
// fn_1_65B58: empty in retail (single blr).
void fn_1_65B58(void) {
}
/* fzgx:end fn_1_65B58 */

/* fzgx:begin fn_1_65E58 */
typedef struct fn_1_65E58_Effect {
    u8 _pad_00[0x10];
    int field_10;
    u8 _pad_14[0x4];
    s16 field_18;
    u8 _pad_1a[0x9e];
} fn_1_65E58_Effect;

void fn_1_65E58(fn_1_65E58_Effect *effect) {
    effect->field_10 = 10;
    fn_1_8636C(effect->field_18, (u8 *)effect + 0xb8);
}
/* fzgx:end fn_1_65E58 */

/* fzgx:begin fn_1_65E88 */
// fn_1_65E88: empty in retail (single blr).
void fn_1_65E88(void) {
}
/* fzgx:end fn_1_65E88 */

/* fzgx:begin fn_1_662D4 */
// fn_1_662D4: empty in retail (single blr).
void fn_1_662D4(void) {
}
/* fzgx:end fn_1_662D4 */

/* fzgx:begin fn_1_67414 */
struct fn_1_67414_Arg0 {
    u8 pad_0[0x10];
    u32 unk_10;
    u8 pad_14[0xa0];
    f32 unk_b4;
};

void fn_1_67414(struct fn_1_67414_Arg0 *arg0) {
    // Volatile preserves the retail load-after-store ordering for the pooled value.
    volatile const f32 *value = (volatile const f32 *)&lbl_1_rodata_2954;
    arg0->unk_10 = 30;
    arg0->unk_b4 = *value;
}
/* fzgx:end fn_1_67414 */

/* fzgx:begin fn_1_6742C */
// fn_1_6742C: empty in retail (single blr).
void fn_1_6742C(void) {
}
/* fzgx:end fn_1_6742C */

/* fzgx:begin fn_1_6755C noprologue */
#include "types.h"
#include "rel/main_rel/effect.h"

extern void fn_1_8636C(s16, void *, u32);
extern void lbl_8006D9D8(void *);
extern void lbl_8006DFC4(void *);
extern void lbl_8006D95C(s32);
extern void mathutil_mtxA_rotate_x(s32);
extern void lbl_8006DB74(void *);
extern void fn_1_9F914(void *, u32);
extern void *memset(void *, int, u32);
extern f32 lbl_1_rodata_2AA0[21];
extern f32 lbl_1_rodata_29AC[5];

typedef struct {
    u8 pad_0[0x18];
    s16 unk_18;
    u8 pad_1a[2];
    f32 unk_1c;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
    u8 pad_2c[0x88];
    f32 unk_b4;
} FnObj_6755C;

typedef struct {
    u8 pad_0[0x120];
    u32 unk_120;
} Root_6755C;

void fn_1_6755C(FnObj_6755C *obj) {
    u8 temp[0x30];
    u8 data[0x40];
    f32 f1;
    f32 f0;
    f32 f3;
    f32 f2;
    Root_6755C *root;
    u32 manager;

    root = (Root_6755C *)(u32)lbl_1_bss_38458->unk_8;
    manager = root->unk_120;
    fn_1_8636C(obj->unk_18, temp, (u32)root);
    lbl_8006D9D8((u8 *)obj + 0x3c);
    lbl_8006DFC4(temp);
    lbl_8006D95C(0);
    mathutil_mtxA_rotate_x(0x4000);
    memset(data, 0, 0x40);
    lbl_8006DB74(data + 8);

    f3 = lbl_1_rodata_2AA0[0] * obj->unk_28;
    *(f32 *)(data + 0) = f3;
    f2 = lbl_1_rodata_29AC[0];
    f1 = obj->unk_b4;
    f0 = obj->unk_1c;
    f0 = f2 * f0;
    f0 = f0 * f1;
    data[0x3c] = (u8)f0;
    f0 = obj->unk_20;
    f0 = f2 * f0;
    f0 = f0 * f1;
    data[0x3d] = (u8)f0;
    f0 = obj->unk_24;
    f0 = f2 * f0;
    data[0x3f] = 0xff;
    *(f32 *)(data + 4) = f3;
    f0 = f0 * f1;
    data[0x3e] = (u8)f0;
    fn_1_9F914(data, manager);
}
/* fzgx:end fn_1_6755C */

/* fzgx:begin fn_1_6766C */
typedef struct {
    u8 padding[0xb4];
    f32 value;
} Fn6766CObject;

void fn_1_6766C(Fn6766CObject *object) {
    object->value = lbl_1_rodata_2978[0];
}
/* fzgx:end fn_1_6766C */

/* fzgx:begin fn_1_6767C */
// fn_1_6767C: empty in retail (single blr).
void fn_1_6767C(void) {
}
/* fzgx:end fn_1_6767C */

/* fzgx:begin fn_1_68054 */
typedef struct fn_1_68054_EffectObject {
    u8 pad0[0x28];
    f32 value;
    u8 pad1[0x10];
    u8 subobject;
} fn_1_68054_EffectObject;

typedef struct fn_1_68054_EffectEntry {
    u8 pad0[4];
    void (*callback)(void);
    fn_1_68054_EffectObject *owner;
} fn_1_68054_EffectEntry;

// Advances the effect and queues its completion callback when it finishes.
void fn_1_68054(fn_1_68054_EffectObject *effect) {
    f32 progress;
    void *source;
    fn_1_68054_EffectEntry *completion;

    progress = effect->value / lbl_1_rodata_2A70[0];
    lbl_8006DCA4();

    if (fn_1_54E34(&effect->subobject, progress) == 0) {
        return;
    }

    source = fn_1_5448C(&effect->subobject);
    completion = (fn_1_68054_EffectEntry *)fn_1_548AC(0xc);
    if (completion == 0) {
        return;
    }

    completion->callback = fn_1_64388;
    completion->owner = effect;
    fn_1_5489C(source, completion);
}
/* fzgx:end fn_1_68054 */

/* fzgx:begin fn_1_680F4 */
// fn_1_680F4: empty in retail (single blr).
void fn_1_680F4(void) {
}
/* fzgx:end fn_1_680F4 */
