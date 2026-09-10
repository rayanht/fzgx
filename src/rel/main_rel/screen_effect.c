#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/screen_effect.h"

extern u32 lbl_1_bss_6C8DC[2];
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32 arg0, u32 arg1, void *arg2, u32 arg3);
extern void fn_1_727BC(u32 arg0, u32 arg1, void *arg2);
extern void fn_1_76A94(void *arg0, u32 arg1);
extern void fn_1_76DBC(void);
extern void fn_1_4E500(void);
extern void fn_1_4E638(int);
extern void fn_1_4E6F4(void);
extern void fn_80073778(void *arg0, int arg1);
extern s32 fn_1_A5D9C(void);
extern const f32 lbl_1_rodata_31AC;
extern u32 fn_80008E84(u32 arg);
extern void fn_1_77238(void);
extern void fn_1_772E0(void);
extern void fn_1_77384(void *arg);
extern void fn_80072864(int arg0);
extern void fn_800745A4(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern void fn_80074660(int arg0);
extern void fn_80073678(int arg0);
extern void fn_80073898(int arg0);
extern void fn_80074788(int arg0);
extern void fn_800738E0(int arg0, int arg1, int arg2);
extern void fn_80073D60(int arg0, int arg1, int arg2, int arg3, int arg4);
extern void fn_800734A8(int arg0, int arg1, int arg2, int arg3);
extern void fn_80072EDC(int arg0, int arg1);
extern f32 lbl_1_rodata_31B0[10];
extern const f64 lbl_1_rodata_31A0;
extern void lbl_8006D784(f32 *arg);
extern void fn_80073A58(int arg0, f32 *arg1, int arg2);
extern void fn_800739E0(int arg0, int arg1, int arg2);
extern void GXLoadTexMtxImm(f32 *arg0, int arg1, int arg2);
extern void fn_8006FDEC(void);
extern void fn_8006FEFC(void);
extern void fn_8006FD1C(void);
extern void fn_1_79810(void);
extern void fn_1_79948(void);
extern void fn_1_791B0(void);
extern void fn_1_9A1E8(void);
extern void fn_1_9A864(void);
extern u8 fn_1_7B074(void);
extern void fn_80071718(void *arg);
extern void fn_800711A8(void *arg);
extern void fn_1_14CB4(void);
extern void fn_1_FA84(void);
extern const f32 lbl_1_rodata_32CC;
extern void fn_1_79C88(void *arg0, s32 arg1, f32 arg2, s32 arg3);
extern void lbl_8006DBAC(void *arg0);
extern void lbl_8006E1B0(void *arg0, void *arg1);
extern void sprintf(char *dst, const char *format, ...);
extern void fn_1_465D0(char *text, int arg);
extern void fn_1_14D5C(void *object, int arg);
extern void fn_1_46EA8(int value);
extern void fn_1_12620(void *object);
extern void fn_1_46DC4(void *obj);

extern void fn_1_727BC();
extern void fn_8006FDEC(void);
extern void fn_80071718(void *);
extern void fn_800711A8(void *);
extern u32 fn_8003526C(u32, u32);
extern u32 fn_80074300(u32, u32, u32, u32);
extern u32 fn_80074438(u32, u32, u32, u32);

/* fzgx:begin fn_1_72648 */
void fn_1_72648(void) {
    if (lbl_1_bss_6C8DC[0] != 0) {
        fn_1_46B4(lbl_801A6410, lbl_1_bss_6C8DC[0], lbl_1_data_1DAC0, 0xf9);
        lbl_1_bss_6C8DC[0] = 0;
    }
}
/* fzgx:end fn_1_72648 */

/* fzgx:begin fn_1_7269C */
typedef struct {
    u8 pad_0[0xa0];
    u32 unk_A0;
    u8 pad_A4[0x24];
    u32 unk_C8;
} fn_1_7269C_ScreenEffectEntry;

void fn_1_7269C(u32 arg0, u32 arg1, void *arg2) {
    fn_1_7269C_ScreenEffectEntry *object;

    object = (fn_1_7269C_ScreenEffectEntry *)((u8 *)&lbl_1_bss_6C8EC + (arg0 & 0xff) * 0x10c);
    fn_1_727BC(arg0, arg1, arg2);
    ((fn_1_7269C_ScreenEffectEntry *)((u8 *)object + (arg1 & 0xff) * 4))->unk_A0 = (u32)arg2;
    ((fn_1_7269C_ScreenEffectEntry *)((u8 *)object + (arg1 & 0xff) * 4))->unk_C8 = 1;
    fn_1_76A94(object, arg1);
    fn_1_76DBC();
}
/* fzgx:end fn_1_7269C */

/* fzgx:begin fn_1_72714 */
// Initialize the effect system and return the requested slot subregion.
void *fn_1_72714(u8 slot, u32 subregion) {
    Obj_1_bss_6C8EC *entry;
    u32 offset;

    fn_1_727BC();
    entry = (Obj_1_bss_6C8EC *)((u8 *)&lbl_1_bss_6C8EC + slot * 0x10c);
    offset = (subregion & 0xff) * 0x20;
    return (u8 *)entry + offset;
}
/* fzgx:end fn_1_72714 */

/* fzgx:begin fn_1_72768 */
// Initialize the selected screen-effect slot with its requested value.
void fn_1_72768(u32 arg0, u32 arg1) {
    Obj_1_bss_6C8EC *entry;
    u32 index;

    fn_1_727BC(arg0, 0);
    index = (u8)arg0;
    entry = (Obj_1_bss_6C8EC *)((u8 *)&lbl_1_bss_6C8EC + index * 0x10c);
    entry->unk_104 = arg1;
}
/* fzgx:end fn_1_72768 */

/* fzgx:begin fn_1_72848 */
extern void fn_1_76650(void *);

void fn_1_72848(void) {
    u8 i;

    // Reset each screen-effect entry before clearing the active-effect flag.
    for (i = 0; i < 8; i++) {
        fn_1_76650((u8 *)&lbl_1_bss_6C8EC + i * 0x10c);
    }
    lbl_1_bss_6D14C.unk_0 = 0;
}
/* fzgx:end fn_1_72848 */

/* fzgx:begin fn_1_728B0 */
typedef struct {
    u8 pad_0[0xdc];
    s32 unk_DC;
    s32 unk_E0;
    u8 pad_E4[0x20];
    void (*unk_104)(void *);
} fn_1_728B0_ScreenEffectEntry;

extern void fn_1_72980(fn_1_728B0_ScreenEffectEntry *);
extern void *fn_1_729F8(fn_1_728B0_ScreenEffectEntry *);

void fn_1_728B0(void) {
    u8 i;
    u8 *base;
    fn_1_728B0_ScreenEffectEntry *obj;
    void *result;

    if (lbl_1_bss_6D14C.unk_0 == 0) {
        fn_1_4E500();
        fn_1_4E638(0);
        base = (u8 *)&lbl_1_bss_6C8EC;
        for (i = 0; i < 8; i++) {
            obj = (fn_1_728B0_ScreenEffectEntry *)(base + i * 0x10c);
            if (obj->unk_DC != 0) {
                if (obj->unk_DC == 0xe && obj->unk_E0 == 0) {
                    obj->unk_E0 = obj->unk_E0 + 1;
                } else {
                    fn_1_72980(obj);
                    result = fn_1_729F8(obj);
                    if (obj->unk_104 != 0) {
                        obj->unk_104(result);
                    }
                }
            }
        }
        fn_1_4E6F4();
    }
}
/* fzgx:end fn_1_728B0 */

/* fzgx:begin fn_1_72980 */
typedef struct {
    u8 pad_0[0xdc];
    u32 unk_dc;
} Fn_1_72980_Obj;

void fn_1_72980(Fn_1_72980_Obj *arg0) {
    int index;
    u8 *entry;
    int i;

    entry = (u8 *)arg0;
    i = 0;
    index = 0;
    while (i < ((u8 *)&lbl_1_data_1D9B8)[arg0->unk_dc * 6 + 5]) {
        fn_80073778(entry, index);
        index++;
        entry += 0x20;
        i++;
    }
}
/* fzgx:end fn_1_72980 */

/* fzgx:begin fn_1_761B8 */
struct fn_1_761B8_Arg0 {
    u8 pad_0[0xE0];
    u32 unk_E0;
};

extern const f32 lbl_1_rodata_31A8;
extern const f64 lbl_1_rodata_31D8[2];
extern void fn_1_76C60(void);

void fn_1_761B8(struct fn_1_761B8_Arg0 *arg0, u32 arg1) {
    u32 v0;
    f32 v1;
    v0 = (arg0->unk_E0 + arg1);
    arg0->unk_E0 = v0;
    v1 = (f32)(s32)arg0->unk_E0;
    if (v1 > lbl_1_rodata_31A8) {
        fn_1_76C60();
    }
}
/* fzgx:end fn_1_761B8 */

/* fzgx:begin fn_1_76448 */
#include "types.h"

struct fn_1_76448_Arg0 {
    u8 pad_0[0xA0];
    u32 unk_A0[1];
    u8 pad_A4[0x38];
    u32 unk_DC;
    u8 pad_E0[0x18];
    s16 unk_F8;
};

void fn_1_76448(struct fn_1_76448_Arg0 *arg0, u32 arg1) {
    u32 v0;
    s32 v1;
    u8 v2;
    u32 v3;
    v0 = (arg1 & 0xFF);
    v1 = (arg0->unk_DC * 6);
    v2 = *(u8 *)((u8 *)((u8 *)&lbl_1_data_1D9B8 + v1) + v0);
    v3 = (u32)((u8 *)&lbl_1_data_1D960 + (v2 << 3));
    fn_80074300((arg0->unk_F8 & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 250) & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 252) & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 254) & 0xFFFF));
    fn_80074438((*(s16 *)((u8 *)(u32)arg0 + 256) & 0xFFFF), (*(s16 *)((u8 *)(u32)arg0 + 258) & 0xFFFF), *(u32 *)((u8 *)v3 + 4), (*(u32 *)((u8 *)(u32)arg0 + 244) & 0xFF));
    fn_8003526C(arg0->unk_A0[v0], 0);
}
/* fzgx:end fn_1_76448 */

/* fzgx:begin fn_1_76650 */
typedef struct fn_1_76650_ScreenEffect {
    u8 pad_00[0xa0];
    s32 field_a0;
    s32 field_a4;
    s32 field_a8;
    s32 field_ac;
    s32 field_b0;
    u8 pad_b4[0x14];
    s32 field_c8;
    s32 field_cc;
    s32 field_d0;
    s32 field_d4;
    s32 field_d8;
    s32 field_dc;
    s32 field_e0;
    f32 field_e4;
    s16 field_e8;
    s16 field_ea;
    s16 field_ec;
    s16 field_ee;
    s16 field_f0;
    s16 field_f2;
    s32 field_f4;
    s16 field_f8;
    s16 field_fa;
    s16 field_fc;
    s16 field_fe;
    s16 field_100;
    s16 field_102;
    s32 field_104;
    u8 field_108;
} fn_1_76650_ScreenEffect;

void fn_1_76650(fn_1_76650_ScreenEffect *effect) {
    s32 value;

    effect->field_f2 = 0;
    effect->field_f0 = 0;
    effect->field_ea = 0;
    effect->field_e8 = 0;
    effect->field_ec = 0x280;
    effect->field_ee = 0x1e0;
    effect->field_f4 = 0;
    effect->field_fa = 0;
    effect->field_f8 = 0;
    effect->field_100 = 0x280;
    effect->field_fc = 0x280;
    value = fn_1_A5D9C();
    effect->field_102 = value;
    effect->field_fe = value;
    effect->field_dc = 0;
    effect->field_e0 = 0;
    effect->field_e4 = lbl_1_rodata_31AC;
    effect->field_104 = 0;
    effect->field_108 = 0;
    effect->field_a0 = 0;
    effect->field_c8 = 0;
    effect->field_a4 = 0;
    effect->field_cc = 0;
    effect->field_a8 = 0;
    effect->field_d0 = 0;
    effect->field_ac = 0;
    effect->field_d4 = 0;
    effect->field_b0 = 0;
    effect->field_d8 = 0;
}
/* fzgx:end fn_1_76650 */

/* fzgx:begin fn_1_76964 */
typedef struct {
    u8 pad_0[0xB4];
    u32 unk_B4[6];
    u8 pad_CC[0x10];
    u32 unk_DC;
    u8 pad_E0[0x20];
    s16 unk_100;
    s16 unk_102;
} Fn1_76964Obj;

typedef struct {
    u8 unk_0[5];
    u8 unk_5;
} Fn1_76964Record;

typedef u8 Sig_GXGetTexBufferSize_GXBool;
extern u32 GXGetTexBufferSize(u16, u16, u32, Sig_GXGetTexBufferSize_GXBool, u8);

void fn_1_76964(Fn1_76964Obj *obj) {
    int i;

    for (i = 0; i < ((Fn1_76964Record *)&lbl_1_data_1D9B8)[obj->unk_DC].unk_5; i++) {
        obj->unk_B4[i] = GXGetTexBufferSize(
            obj->unk_100,
            obj->unk_102,
            *(u32 *)((u8 *)&lbl_1_data_1D960 +
                     ((*(u8 *)((u8 *)&lbl_1_data_1D9B8 + obj->unk_DC * 6 + i)) << 3)),
            0,
            0);
    }
}
/* fzgx:end fn_1_76964 */

/* fzgx:begin fn_1_76BD0 */
void fn_1_76BD0(u8 index, u8 value) {
    Obj_1_bss_6C8EC *obj =
        (Obj_1_bss_6C8EC *)((u8 *)&lbl_1_bss_6C8EC + index * 0x10c);

    if ((s32)obj->unk_DC != 0) {
        obj->unk_108 = value;
    }
}
/* fzgx:end fn_1_76BD0 */

/* fzgx:begin fn_1_76BF8 */
extern void fn_1_76C60(void);

typedef struct {
    u8 pad_0[0xDC];
    s32 unk_DC;
    u8 pad_E0[0x2C];
} fn_1_76BF8_ScreenEffectEntry;

void fn_1_76BF8(void) {
    u8 i;
    fn_1_76BF8_ScreenEffectEntry *entry;

    entry = (fn_1_76BF8_ScreenEffectEntry *)&lbl_1_bss_6C8EC;
    for (i = 0; i < 8; i++) {
        entry = (fn_1_76BF8_ScreenEffectEntry *)((u8 *)&lbl_1_bss_6C8EC + i * 0x10C);
        if (entry->unk_DC != 0) {
            fn_1_76C60();
        }
    }
}
/* fzgx:end fn_1_76BF8 */

/* fzgx:begin fn_1_76C60 */
typedef struct {
    u8 pad_0[0xa0];
    u32 unk_a0[5];
    u32 unk_b4[5];
    s32 unk_c8[5];
    u32 unk_dc;
    u32 unk_e0;
    f32 unk_e4;
    u16 unk_e8;
    u16 unk_ea;
    u16 unk_ec;
    u16 unk_ee;
    u16 unk_f0;
    u16 unk_f2;
    u32 unk_f4;
    u16 unk_f8;
    u16 unk_fa;
    u16 unk_fc;
    u16 unk_fe;
    u16 unk_100;
    u16 unk_102;
    u32 unk_104;
    u8 unk_108;
} FnScreenEffect;

// Clears the active screen-effect state and resets its rendering parameters.
void fn_1_76C60(FnScreenEffect *arg) {
    u8 i;
    u16 value;

    lbl_1_bss_6C8E8 = fn_80008E84(lbl_1_bss_6C8E4);
    i = 0;
    while (i < ((u8 *)&lbl_1_data_1D9B8)[arg->unk_dc * 6 + 5]) {
        if (arg->unk_c8[i] == 0) {
            fn_1_46B4(lbl_801A6410, arg->unk_a0[i], lbl_1_data_1DAC0, 0x9a1);
            arg->unk_a0[i] = 0;
        }
        i++;
    }
    fn_80008E84(lbl_1_bss_6C8E8);
    arg->unk_f2 = 0;
    arg->unk_f0 = 0;
    arg->unk_ea = 0;
    arg->unk_e8 = 0;
    arg->unk_ec = 0x280;
    arg->unk_ee = 0x1e0;
    arg->unk_f4 = 0;
    arg->unk_fa = 0;
    arg->unk_f8 = 0;
    arg->unk_100 = 0x280;
    arg->unk_fc = 0x280;
    value = fn_1_A5D9C();
    arg->unk_102 = value;
    arg->unk_fe = value;
    arg->unk_dc = 0;
    arg->unk_e0 = 0;
    arg->unk_e4 = lbl_1_rodata_31AC;
    arg->unk_104 = 0;
    arg->unk_108 = 0;
    arg->unk_a0[0] = 0;
    arg->unk_c8[0] = 0;
    arg->unk_a0[1] = 0;
    arg->unk_c8[1] = 0;
    arg->unk_a0[2] = 0;
    arg->unk_c8[2] = 0;
    arg->unk_a0[3] = 0;
    arg->unk_c8[3] = 0;
    arg->unk_a0[4] = 0;
    arg->unk_c8[4] = 0;
    fn_1_76DBC();
}
/* fzgx:end fn_1_76C60 */

/* fzgx:begin fn_1_76DBC */
// fn_1_76DBC: empty in retail (single blr).
void fn_1_76DBC(void) {
}
/* fzgx:end fn_1_76DBC */

/* fzgx:begin fn_1_77200 */
void fn_1_77200(void *arg) {
    fn_1_77238();
    fn_1_772E0();
    fn_1_77384(arg);
}
/* fzgx:end fn_1_77200 */

/* fzgx:begin fn_1_77238 */
void fn_1_77238(void) {
    fn_80072864(2);
    fn_800745A4(0, 1, 4, 30, 0, 125);
    fn_80074660(1);
    fn_80073678(1);
    fn_80073898(1);
    fn_80074788(0);
    fn_800738E0(0, 0, 1);
    fn_80073D60(0, 0, 1, 0, 1);
    fn_800734A8(0, 0, 0, 255);
    fn_80072EDC(0, 3);
}
/* fzgx:end fn_1_77238 */

/* fzgx:begin fn_1_772E0 */
void fn_1_772E0(void) {
    f32 first[16];
    f32 second[8];
    f32 values[6];

    lbl_8006D784(&first[4]);
    values[0] = lbl_1_rodata_31B0[0] * first[4];
    values[1] = lbl_1_rodata_31B0[0] * first[5];
    values[2] = *(const f32 *)&lbl_1_rodata_31A0;
    values[3] = lbl_1_rodata_31B0[0] * first[8];
    values[4] = lbl_1_rodata_31B0[0] * first[9];
    values[5] = *(const f32 *)&lbl_1_rodata_31A0;
    fn_80073A58(1, values, 1);
    fn_800739E0(0, 0, 0);
    lbl_8006D784(second);
    GXLoadTexMtxImm(second, 30, 1);
}
/* fzgx:end fn_1_772E0 */

/* fzgx:begin fn_1_7879C */
extern const f32 lbl_1_rodata_323C;
extern const f64 lbl_1_rodata_31D8;

u8 fn_1_7879C(u32 arg0) {
    s32 v0;

    v0 = (s32)(lbl_1_rodata_323C * (f32)(s32)((arg0 - 0x1000000) + 2048));
    return (u8)(v0 < 0 ? 0 : (v0 <= 255 ? v0 : 0xff));
}
/* fzgx:end fn_1_7879C */

/* fzgx:begin fn_1_78950 */
// Reset the screen effect state and refresh its processing stages twice.
void fn_1_78950(void) {
    int i;

    lbl_1_bss_6D14C.unk_0 = 1;
    for (i = 0; i < 2; i++) {
        fn_8006FDEC();
        fn_8006FEFC();
        fn_8006FD1C();
    }
}
/* fzgx:end fn_1_78950 */

/* fzgx:begin fn_1_7899C */
// Reset the screen-effect state before the next effect begins.
void fn_1_7899C(void) {
    lbl_1_bss_6D14C.unk_0 = 0;
}
/* fzgx:end fn_1_7899C */

/* fzgx:begin fn_1_789AC */
void fn_1_789AC(void) {
    fn_1_79810();
    fn_1_79948();
    fn_1_791B0();
    fn_1_9A1E8();
    lbl_1_data_1DFA4.unk_4 = 0;
}
/* fzgx:end fn_1_789AC */

/* fzgx:begin fn_1_79100 */
// Release the active screen-effect resources and reset the effect state.
void fn_1_79100(void) {
    fn_1_9A864();

    if (!fn_1_7B074()) {
        if (lbl_1_bss_6D770 != 0 || lbl_1_bss_6D774 != 0) {
            fn_8006FDEC();
        }

        if (lbl_1_bss_6D770 != 0) {
            fn_80071718((void *)lbl_1_bss_6D770);
            lbl_1_bss_6D770 = 0;
        }

        if (lbl_1_bss_6D774 != 0) {
            fn_800711A8((void *)lbl_1_bss_6D774);
            lbl_1_bss_6D774 = 0;
        }
    }

    fn_1_14CB4();
    fn_1_FA84();
    lbl_1_data_1DFA4.unk_8 = -1;
}
/* fzgx:end fn_1_79100 */

/* fzgx:begin fn_1_79810 */
typedef struct {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    s16 unk_C;
    s16 unk_E;
    s16 unk_10;
    u8 pad_12[0x6];
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    u8 pad_24[0xd0];
    void *unk_F4;
    u8 pad_F8[0xc];
    u32 unk_104;
} ScreenEffectSource;

extern void fn_80008BEC(void *arg0, s32 arg1, u32 arg2);
extern void lbl_8006D758(void);
extern void lbl_8006DB74(void *arg);
extern void lbl_8006E0C8(void *arg);

void fn_1_79810(void) {
    u32 source_flags;
    Obj_1_bss_3BE4 *dst;
    ScreenEffectSource *src;
    s32 i;

    i = 0;
    dst = *(Obj_1_bss_3BE4 **)&lbl_1_bss_3BE4;
    src = (ScreenEffectSource *)lbl_1_bss_3BE0->unk_1C;
    while (i < (s32)lbl_1_bss_3BE0->unk_18) {
        source_flags = dst->unk_9C;
        fn_80008BEC(dst, 0, 0xa0);
        dst->unk_9C = source_flags;
        dst->unk_8 = src->unk_0;
        dst->unk_C = src->unk_4;
        dst->unk_10 = src->unk_8;
        dst->unk_14 = src->unk_0 - src->unk_18;
        dst->unk_18 = src->unk_4 - src->unk_1C;
        dst->unk_1C = src->unk_8 - src->unk_20;
        dst->unk_20 = src->unk_C;
        dst->unk_22 = src->unk_E;
        dst->unk_24 = src->unk_10;
        dst->unk_26 = src->unk_C;
        dst->unk_28 = src->unk_E;
        dst->unk_2A = src->unk_10;
        lbl_8006D758();
        lbl_8006DB74((u8 *)dst + 0x2c);
        lbl_8006E0C8((u8 *)src + 0x18);
        lbl_8006DB74((u8 *)dst + 0x5c);
        if (src->unk_F4 != 0) {
            dst->unk_98 = *(f32 *)((u8 *)src->unk_F4 + 0xc);
        }
        source_flags = src->unk_104;
        dst->unk_0 |= source_flags;
        i++;
        src = (ScreenEffectSource *)((u8 *)src + 0x4b0);
        dst = (Obj_1_bss_3BE4 *)((u8 *)dst + 0xa0);
    }
}
/* fzgx:end fn_1_79810 */

/* fzgx:begin fn_1_7A648 */
void fn_1_7A648(void *arg0) {
    fn_1_79C88(arg0, 0, lbl_1_rodata_32CC, 0);
}
/* fzgx:end fn_1_7A648 */

/* fzgx:begin fn_1_7A67C */
typedef struct {
    u32 flags;
    s32 count;
    void *entries;
} EffectTable;

typedef struct {
    u8 unk00[0x8];
    void *value;
    u32 unk0c;
} EffectEntry;

void *fn_1_7A67C(EffectTable *table) {
    s32 index;
    EffectEntry *entry;

    index = table->count - 1;
    if ((table->flags & 1) != 0) {
        index--;
    }
    if ((table->flags & 0x40) != 0) {
        index -= 2;
    }
    entry = (EffectEntry *)table->entries;
    entry += index;
    return entry->value;
}
/* fzgx:end fn_1_7A67C */

/* fzgx:begin fn_1_7A9B8 */
typedef struct {
    u8 pad_0[0xf4];
    void *resource;
    u8 pad_f8[0x4b0 - 0xf8];
} fn_1_7A9B8_ScreenEffect;

typedef struct {
    u8 pad_0[0x2c];
    u8 reset_data[0x60];
    u8 load_data[0x14];
} fn_1_7A9B8_ScreenEffectEntry;

// Resets the active screen-effect entries and releases each attached resource.
void fn_1_7A9B8(void) {
    fn_1_7A9B8_ScreenEffectEntry *entry;
    fn_1_7A9B8_ScreenEffect *effect;
    s32 i;

    i = 0;
    entry = (fn_1_7A9B8_ScreenEffectEntry *)lbl_1_bss_3BE4.unk_0;
    effect = (fn_1_7A9B8_ScreenEffect *)lbl_1_bss_3BE0->unk_1C;
    while (i < (s32)lbl_1_bss_3BE0->unk_18) {
        if (effect->resource != 0) {
            lbl_8006DBAC(&entry->reset_data);
            lbl_8006E1B0(effect->resource, &entry->load_data);
        }
        i++;
        entry++;
        effect++;
    }
}
/* fzgx:end fn_1_7A9B8 */

/* fzgx:begin fn_1_7B054 */
// Return the current screen effect value.
s16 fn_1_7B054(void) {
    return lbl_1_data_1DFA4.unk_8;
}
/* fzgx:end fn_1_7B054 */

/* fzgx:begin fn_1_7B064 */
u32 fn_1_7B064(void) {
    return lbl_1_bss_6D774;
}
/* fzgx:end fn_1_7B064 */

/* fzgx:begin fn_1_7B074 */
u8 fn_1_7B074(void) {
    return lbl_1_bss_6D600.unk_0;
}
/* fzgx:end fn_1_7B074 */

/* fzgx:begin fn_1_7B084 */
void fn_1_7B084(void *object, int value) {
    char text_a[32];
    char text_b[32];
    const char *data = (const char *)&lbl_1_data_1DCF0;

    sprintf(text_a, data + 0x7d0, data + 0x7e0, object);
    sprintf(text_b, data + 0x7e8, data + 0x7e0, object);
    if (value == 0) {
        fn_1_465D0(text_a, 1);
        fn_1_465D0(text_b, 1);
        fn_1_14D5C(object, 0);
    } else {
        fn_1_465D0(text_a, 2);
        fn_1_465D0(text_b, 2);
        fn_1_14D5C(object, 1);
    }
    fn_1_46EA8(value);
    fn_1_12620(object);
    sprintf(text_a, data + 0x7f8, object);
    fn_1_465D0(text_a, 1);
    fn_1_46EA8(0);
}
/* fzgx:end fn_1_7B084 */

/* fzgx:begin fn_1_7B184 */
void fn_1_7B184(void *arg) {
    char buf_48[0x20];
    char buf_28[0x20];
    char buf_08[0x20];
    u8 *base = (u8 *)&lbl_1_data_1DCF0;

    sprintf(buf_48, (const char *)(base + 0x7d0), (const char *)(base + 0x7e0), arg);
    sprintf(buf_28, (const char *)(base + 0x7e8), (const char *)(base + 0x7e0), arg);
    sprintf(buf_08, (const char *)(base + 0x810), arg);

    fn_1_46DC4(buf_48);
    fn_1_46DC4(buf_28);
    fn_1_46DC4(buf_08);
}
/* fzgx:end fn_1_7B184 */

/* fzgx:begin fn_1_7B218 noprologue */
#include "types.h"
#include "rel/main_rel/screen_effect.h"

typedef struct {
    u8 pad_0[0x7e0];
    char unk_7e0[0x4c];
    char unk_82c[0x14];
    char unk_840[0x20];
} ScreenEffectData;

extern u16 fn_1_12EF24(s16 value, s16 index);
extern void sprintf(char *dst, const char *format, const char *text, ...);
extern void fn_1_465D0(char *text, s32 mode);

void fn_1_7B218(s32 enabled) {
    char text_a[0x20];
    char text_b[0x20];
    s32 i;
    s16 index;
    ScreenEffectData *data = (ScreenEffectData *)&lbl_1_data_1DCF0;

    i = 0;
    do {
        index = fn_1_12EF24(lbl_1_bss_8B3A0.unk_8C, i);
        if (index >= 0) {
            sprintf(text_a, data->unk_82c, data->unk_7e0, index);
            sprintf(text_b, data->unk_840, data->unk_7e0, index);
            if (enabled == 0) {
                fn_1_465D0(text_a, 1);
                fn_1_465D0(text_b, 1);
            } else {
                fn_1_465D0(text_a, 2);
                fn_1_465D0(text_b, 2);
            }
        }
        i++;
    } while (i < 6);
}
/* fzgx:end fn_1_7B218 */

/* fzgx:begin fn_1_7B4C0 */
// Releases active screen effects and resets the effect state.
void fn_1_7B4C0(void) {
    if (lbl_1_bss_6D770 != 0 || lbl_1_bss_6D774 != 0) {
        fn_8006FDEC();
    }

    if (lbl_1_bss_6D770 != 0) {
        fn_80071718((void *)lbl_1_bss_6D770);
        lbl_1_bss_6D770 = 0;
    }

    if (lbl_1_bss_6D774 != 0) {
        fn_800711A8((void *)lbl_1_bss_6D774);
        lbl_1_bss_6D774 = 0;
    }

    lbl_1_data_1DFA4.unk_8 = -1;
}
/* fzgx:end fn_1_7B4C0 */
