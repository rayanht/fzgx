#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/sound.h"

extern void *lbl_801A6410;
extern void fn_1_44A4(void);
extern void *fn_80008E84(void *arg);
extern u32 fn_1_45D0(void *arg0, void *arg1, u32 *arg2, int arg3);
extern void fn_1_46B4(u32, void *, void *, u32);
extern s8 lbl_1_bss_6EAA6;
extern u8 lbl_1_bss_6EAA4;
extern void fn_80067974(void);
extern void fn_800280F0(void);
extern void fn_80026FE0(void);
extern u8 lbl_1_bss_6EAA8[8];
extern u8 lbl_1_bss_6EAB0;
extern void ARInit(u8 *arg0, int arg1);
extern void fn_80020530(void);
extern u8 lbl_1_bss_6F1E1;
extern void fn_1_A2DF4(s32, void *, s32);
extern void fn_1_A2E24(u32 arg0, u32 arg1, s32 arg2);
extern void fn_80008BEC(void *, s32, s32);
extern void fn_1_A0680(void);
extern void fn_80067898(u32);
extern void fn_800674FC(u16 arg0, u32 arg1, s16 arg2);
extern s32 camera_get_mode(void);
extern u8 lbl_1_bss_6F2D8[62];
extern void fn_80067344(s32, s32, u32, s32);
extern void fn_1_A5470(s32 value);
extern u32 fn_1_3F13C(void);
extern u32 fn_1_EB0B0(void);
extern s32 fn_1_F1B94(void);
extern u32 lbl_1_rodata_45D0[];
extern u32 lbl_1_rodata_4718[];
extern u32 lbl_1_rodata_4730[];
extern u32 lbl_1_rodata_47A8[];
extern u8 lbl_1_bss_6F41C[260];
extern s32 fn_1_86690(s32 value);
extern void *lbl_1_rodata_4820[41];
extern int fn_8004C658(u32 obj);
extern int fn_8004BBCC(u32 obj);
extern void ADXT_Pause(u32 obj, int arg);
extern int fn_1_3FC38(void);

extern void fn_1_A2DF4(s32, void *, s32);
extern void fn_80008BEC(void *, s32, s32);
extern s32 fn_1_86690(s32 value);
extern void fn_80067344(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
extern void fn_80067898(u32 value);
extern void *lbl_1_rodata_4820[41];

extern void *lbl_801A6410;
extern void *fn_80008E84();
extern void fn_1_44A4(void);

extern void *lbl_801A6410;
extern void fn_1_44A4(void);
extern void *fn_80008E84();
extern u32 fn_1_45D0(void *arg0, void *arg1, u32 *arg2, int arg3);
extern void fn_80063094(s32 arg0, void *arg1, s32 arg2);
extern void fn_80065D70(int);

/* fzgx:begin fn_1_9FE74 */
// Initialize the sound resource and register it with the sound system.
u32 fn_1_9FE74(void *arg) {
    u32 result;

    fn_1_44A4();
    lbl_1_bss_6EA9C = (u32)fn_80008E84();
    result = fn_1_45D0(lbl_801A6410, arg, &lbl_1_data_33F1C, 0x94);
    fn_80008E84((void *)lbl_1_bss_6EA9C);
    return result;
}
/* fzgx:end fn_1_9FE74 */

/* fzgx:begin fn_1_9FEE8 */
// Initialize the sound resource and register it with the sound manager.
void fn_1_9FEE8(void *arg) {
    fn_1_44A4();
    lbl_1_bss_6EA9C = (u32)fn_80008E84();
    fn_1_46B4((u32)lbl_801A6410, arg, &lbl_1_data_33F1C, 0x9c);
    fn_80008E84((void *)lbl_1_bss_6EA9C);
}
/* fzgx:end fn_1_9FEE8 */

/* fzgx:begin fn_1_9FF50 */
// fn_1_9FF50: empty in retail (single blr).
void fn_1_9FF50(void) {
}
/* fzgx:end fn_1_9FF50 */

/* fzgx:begin fn_1_9FF54 */
// fn_1_9FF54: empty in retail (single blr).
void fn_1_9FF54(void) {
}
/* fzgx:end fn_1_9FF54 */

/* fzgx:begin fn_1_9FF58 */
void fn_1_9FF58(void) {
    if (lbl_1_bss_6EAA6) {
        fn_80067974();
        fn_800280F0();
        fn_80026FE0();
    }
    lbl_1_bss_6EAA4 = 0;
}
/* fzgx:end fn_1_9FF58 */

/* fzgx:begin fn_1_9FF9C */
void fn_1_9FF9C(void) {
    ARInit(lbl_1_bss_6EAA8, 2);
    fn_80020530();
    lbl_1_bss_6EAB0 = 0;
}
/* fzgx:end fn_1_9FF9C */

/* fzgx:begin fn_1_A04AC */
void fn_1_A04AC(void) {
    lbl_1_bss_6F1E0 = 1;
    lbl_1_bss_6F1E1 = 1;
}
/* fzgx:end fn_1_A04AC */

/* fzgx:begin fn_1_A04C4 noprologue */
#include "types.h"

struct fn_1_A04C4_lbl_1_bss_6EA98 {
    u8 pad_0[0xD];
    u8 unk_D;
    u8 unk_E;
    u8 pad_F[0x9];
    u8 unk_18;
    u8 pad_19[0x3];
    u32 unk_1C;
    u16 unk_20;
    u8 pad_22[0x2];
    f32 unk_24;
    f32 unk_28;
    u8 unk_2C;
    u8 unk_2D;
    u8 pad_2E[0x2];
    u32 unk_30;
    u8 pad_34[0x4];
    u32 unk_38;
};

extern f32 lbl_1_rodata_42E0;
extern struct fn_1_A04C4_lbl_1_bss_6EA98 lbl_1_bss_6EA98;
extern u32 OSGetSoundMode(void);
extern u32 fn_1_44A4(void);
extern u32 fn_1_A2E24(u32, u32, u32);
extern u32 fn_80008BEC(u32, u32, u32);
extern u32 fn_80022014(u32);
extern u32 fn_80025D50(u32, u32);
extern u32 fn_8004B7D4(u32);
extern u32 fn_8004BBA4(u32, u32);
extern u32 ADXT_Stop(u32);
extern u32 fn_8004CAC8(u32);
extern u32 fn_8004CD70(u32, u32, u32);
extern u32 fn_8004E59C(u32);
extern u32 fn_8004EC34(u32);
extern u32 fn_80065890(void);
extern u32 fn_8006589C(u32);
extern u32 fn_800658A8(u32);
extern void fn_1_9FE74(void);
extern void fn_1_9FEE8(void);
extern void fn_1_9FF50(void);
extern void fn_1_9FF54(void);
extern void fn_1_9FF58(void);
extern void fn_1_A04AC(void);

void fn_1_A04C4(void) {
    struct fn_1_A04C4_lbl_1_bss_6EA98 *p_lbl_1_bss_6EA98;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 t1, t2, t15, t16, t17, t18, t19, t20;
    p_lbl_1_bss_6EA98 = (struct fn_1_A04C4_lbl_1_bss_6EA98 *)&lbl_1_bss_6EA98;
    p_lbl_1_bss_6EA98->unk_E = 0;
    fn_80025D50((u32)fn_1_9FE74, (u32)fn_1_9FEE8);
    t1 = fn_80022014((u32)fn_1_9FF58);
    t2 = fn_8004EC34(0);
    fn_8004E59C(0);
    fn_8004BBA4((u32)fn_1_9FF50, 0);
    p_lbl_1_bss_6EA98->unk_1C = 0;
    p_lbl_1_bss_6EA98->unk_20 = 0;
    p_lbl_1_bss_6EA98->unk_24 = lbl_1_rodata_42E0;
    p_lbl_1_bss_6EA98->unk_28 = lbl_1_rodata_42E0;
    p_lbl_1_bss_6EA98->unk_2C = 255;
    p_lbl_1_bss_6EA98->unk_2D = 0;
    fn_80008BEC((p_lbl_1_bss_6EA98->unk_30), 0, (0x30000 + -32768));
    fn_800658A8((u32)fn_1_A04AC);
    fn_8006589C((u32)fn_1_9FF54);
    fn_1_44A4();
    fn_80065890();
    ADXT_Stop(*(u32 *)((u8 *)p_lbl_1_bss_6EA98->unk_38 + 0));
    fn_8004CAC8(*(u32 *)((u8 *)p_lbl_1_bss_6EA98->unk_38 + 0));
    ADXT_Stop(*(u32 *)((u8 *)p_lbl_1_bss_6EA98->unk_38 + 4));
    fn_8004CAC8(*(u32 *)((u8 *)p_lbl_1_bss_6EA98->unk_38 + 4));
    fn_80008BEC(p_lbl_1_bss_6EA98->unk_38, 0, (0x90000 + 29856));
    t15 = fn_8004CD70(2, (p_lbl_1_bss_6EA98->unk_38 + 16), (0x50000 - 23992));
    v1 = p_lbl_1_bss_6EA98->unk_38;
    *(u32 *)((u8 *)v1 + 0) = t15;
    t16 = fn_8004CD70(2, ((p_lbl_1_bss_6EA98->unk_38 + 0x50000) - 23976), (0x50000 - 23992));
    v2 = p_lbl_1_bss_6EA98->unk_38;
    *(u32 *)((u8 *)v2 + 4) = t16;
    *(u32 *)((u8 *)p_lbl_1_bss_6EA98->unk_38 + 8) = 0;
    v3 = p_lbl_1_bss_6EA98->unk_38;
    *(u32 *)((u8 *)v3 + 12) = 0;
    t17 = OSGetSoundMode();
    v4 = t17;
    if (t17 == 0) {
    v4 = 0;
    t18 = fn_1_A2E24(v4, (0xA0000000 + 2304), 0);
    v4 = t18;
    v4 = 1;
    t19 = fn_8004B7D4(v4);
    v4 = t19;
    } else {
    v4 = 0;
    t20 = fn_1_A2E24(v4, (0xA0000000 + 2048), 0);
    v4 = t20;
    }
    p_lbl_1_bss_6EA98->unk_18 = 1;
    p_lbl_1_bss_6EA98->unk_D = 0;
}
/* fzgx:end fn_1_A04C4 */

/* fzgx:begin fn_1_A0C68 */
enum {
    ADDR_A6000000 = 0xA6000000,
    ADDR_A5100000 = 0xA5100000,
    ADDR_A0000300 = 0xA0000300,
    ADDR_A0000400 = 0xA0000400
};

typedef struct fn_1_A0C68_SoundState {
    u8 pad_2e[0x2e];
    u8 unk_2e;
    u8 pad_74c[0x74c - 0x2f];
    u8 unk_74c[0x50];
    u8 pad_7ac[0x7ac - 0x79c];
    u8 unk_7ac;
} fn_1_A0C68_SoundState;

// Initialize the sound resources once the sound system is enabled.
void fn_1_A0C68(void) {
    fn_1_A0C68_SoundState *state;
    s32 i;

    state = (fn_1_A0C68_SoundState *)&lbl_1_bss_6EA98;
    if (state->unk_2e != 0) {
        fn_1_A2DF4(0x10, (void *)ADDR_A6000000, 0);
        fn_1_A2DF4(0x10, (void *)ADDR_A5100000, 0);

        for (i = 1; i < 4; i++) {
            fn_1_A2E24(i, ADDR_A0000300, 0);
        }

        fn_1_A2E24(0x10, ADDR_A0000400, 0);
        fn_80008BEC(&state->unk_74c, 0, 0x50);
        state->unk_7ac = 0;
    }
}
/* fzgx:end fn_1_A0C68 */

/* fzgx:begin fn_1_A116C */
#include "types.h"

extern s16 lbl_1_bss_962;

void fn_1_A116C(void) {
    switch ((*(s16 *)&lbl_1_bss_960)) {
    case 2:
    case 8:
    case 9:
    case 12:
        fn_80065D70(1);
        break;
    case 1:
    case 5:
    case 13:
        fn_80065D70(2);
        break;
    case 4:
        if (lbl_1_bss_962 != 0x3D) {
            fn_80065D70(3);
        }
        break;
    case 14:
    case 16:
        fn_80065D70(3);
        break;
    }
}
/* fzgx:end fn_1_A116C */

/* fzgx:begin fn_1_A1340 */
void fn_1_A1340(void) {
    fn_1_A0680();
}
/* fzgx:end fn_1_A1340 */

/* fzgx:begin fn_1_A1360 */
// fn_1_A1360: empty in retail (single blr).
void fn_1_A1360(void) {
}
/* fzgx:end fn_1_A1360 */

/* fzgx:begin fn_1_A2D84 */
void fn_1_A2D84(u32 arg0) {
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 0x2D) {
        fn_80067898(arg0);
    }
}
/* fzgx:end fn_1_A2D84 */

/* fzgx:begin fn_1_A2DC4 */
void fn_1_A2DC4(u32 arg0) {
    if (lbl_1_bss_6F1DC <= 0x2D) {
        fn_80067898(arg0);
    }
}
/* fzgx:end fn_1_A2DC4 */

/* fzgx:begin fn_1_A2DF4 */
// Forwards the sound event while sound processing is enabled.
void fn_1_A2DF4(s32 arg0, void *arg1, s32 arg2) {
    if (lbl_1_bss_6EAC6.unk_0 != 0) {
        fn_80063094(arg0, arg1, arg2);
    }
}
/* fzgx:end fn_1_A2DF4 */

/* fzgx:begin fn_1_A2E24 */
// Notifies the sound system when sound processing is enabled.
void fn_1_A2E24(u32 arg0, u32 arg1, s32 arg2) {
    if (lbl_1_bss_6EAC6.unk_0 != 0) {
        fn_800674FC(arg0, arg1, arg2);
    }
}
/* fzgx:end fn_1_A2E24 */

/* fzgx:begin fn_1_A2E5C noprologue */
#include "types.h"

typedef struct {
    u8 unk_0[0x740];
    u8 unk_740;
    u8 unk_741[3];
    u32 unk_744;
    u8 unk_748[4];
    u8 unk_74C[0xE0];
    u8 unk_82C;
} SoundState;

typedef struct {
    u8 unk_0[0x3A0];
    void *unk_3A0;
} SoundObject;

typedef struct {
    u8 unk_0[0x6C0];
    s16 unk_6C0;
} SoundData;

extern SoundState lbl_1_bss_6EA98;

extern s32 fn_1_3F864(void);
extern s8 fn_1_86690(s8 arg0);
extern SoundObject *fn_1_86854(s8 arg0);
extern void fn_1_14E9E4(s16 arg0, void *arg1);
extern void fn_80067344(u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern void fn_80067898(u32 arg0);

extern u32 lbl_1_rodata_451C[5];
extern u32 lbl_1_rodata_4478[41];

void fn_1_A2E5C(s32 arg0, s32 arg1) {
    SoundState *state = &lbl_1_bss_6EA98;
    s16 local[8];
    u8 *entry;
    s8 i;

    if (fn_1_3F864() != 0) {
        entry = &state->unk_74C[0];
        i = 0;
        while (i < (s8)state->unk_82C) {
            if (arg0 == entry[1] && entry[2] != 0) {
                fn_80067344(1, 0x10, 0xB0270000, entry[2]);
                if (arg1 != 0) {
                    if (state->unk_740 == 0 && state->unk_744 <= 0x2D) {
                        fn_80067898(0xA9090B00);
                    }
                } else if (fn_1_86690(arg0) > 0x28) {
                    SoundData *data;
                    u32 snd;
                    s16 half;
                    data = (SoundData *)fn_1_86854(fn_1_86690(arg0))->unk_3A0;
                    fn_1_14E9E4(data->unk_6C0, local);
                    half = (s16)(local[4] >> 1);
                    snd = lbl_1_rodata_451C[half];
                    if (state->unk_740 == 0 && state->unk_744 <= 0x2D) {
                        fn_80067898(snd);
                    }
                } else {
                    u32 snd = lbl_1_rodata_4478[fn_1_86690(arg0)];
                    if (state->unk_740 == 0 && state->unk_744 <= 0x2D) {
                        fn_80067898(snd);
                    }
                }
            }
            entry += 0x14;
            i++;
        }
    }
}
/* fzgx:end fn_1_A2E5C */

/* fzgx:begin fn_1_A3C78 noprologue */
#include "types.h"
#include "rel/main_rel/sound.h"

extern s32 fn_1_3F864(s32 arg0, s32 arg1);
extern u32 fn_1_864E8(s32 arg0);
extern void fn_80067344(s32 arg0, s32 arg1, u32 arg2, u32 arg3);
extern void fn_80067898(u32 arg0);

void fn_1_A3C78(s32 arg0, s32 arg1) {
    u8 *base;
    u8 *entry;

    base = (u8 *)&lbl_1_bss_6EA98;
    if (fn_1_3F864(arg0, arg1) != 0) {
        switch (arg1) {
        case 0:
            if ((fn_1_864E8(arg0) & 0x280) == 0) {
                entry = base + 0x74C;
                arg1 = 0;
                while (arg1 < *(s8 *)(base + 0x82C)) {
                    if (arg0 == *(u8 *)(entry + 1) && *(u8 *)(entry + 2) != 0) {
                        fn_80067344(1, 0x10, 0xB0270000, *(u8 *)(entry + 2));
                        if (base[0x740] == 0 && *(u32 *)(base + 0x744) <= 0x2D) {
                            fn_80067898(0xA9090F00);
                        }
                    }
                    entry += 0x14;
                    arg1++;
                }
            }
            break;
        }
    }
}
/* fzgx:end fn_1_A3C78 */

/* fzgx:begin fn_1_A4BC8 noprologue */
#include "types.h"

extern u32 fn_1_864E8(int);
extern void *fn_1_86254(int);
extern u32 fn_80067898(u32);
extern u8 lbl_1_bss_6F1D8;
extern u32 lbl_1_bss_6F1DC;

typedef struct {
    u8 pad[0x10C];
    s32 field_10C;
    s32 field_110;
} FnA4BC8State;

void fn_1_A4BC8(void *arg0, void *arg1, FnA4BC8State *state) {
    u32 flags;

    flags = fn_1_864E8((int)arg0);
    fn_1_86254((int)arg0);

    if (!(flags & 0x00010880)) {
        if (state->field_10C && state->field_110 &&
            !lbl_1_bss_6F1D8 && lbl_1_bss_6F1DC <= 0x2D) {
            fn_80067898(0xA9061800);
        }

        if ((flags & 0x00040000) &&
            !lbl_1_bss_6F1D8 && lbl_1_bss_6F1DC <= 0x2D) {
            fn_80067898(0xA9092000);
        }
    }
}
/* fzgx:end fn_1_A4BC8 */

/* fzgx:begin fn_1_A4C9C */
void fn_1_A4C9C(s32 index, u8 value) {
    s16 mode;

    mode = camera_get_mode();
    if (value == lbl_1_bss_6F2D8[index * 2]) {
        return;
    }

    fn_80067344(1, 2, 0xB0270000, 0x7F);

    switch (value) {
    case 2:
        fn_1_A5470(mode);
        lbl_1_bss_6F2D8[index * 2] = value;
        break;
    case 1:
        lbl_1_bss_6F2D8[index * 2] = value;
        break;
    case 3:
        if ((fn_1_3F13C() & 0xFF) == 2 && fn_1_EB0B0() != 0) {
            if (fn_1_F1B94() == 1) {
                if (lbl_1_bss_6F1DC <= 0x2D) {
                    fn_80067898(0xA9064E00);
                }
                lbl_1_bss_6F2D8[index * 2] = value;
            } else if (fn_1_F1B94() == 3) {
                if (lbl_1_bss_6F1DC <= 0x2D) {
                    fn_80067898(0xA9064F00);
                }
                lbl_1_bss_6F2D8[index * 2] = value;
            }
        } else {
            if (lbl_1_bss_6F1DC <= 0x2D) {
                fn_80067898(0xA9062200);
            }
            lbl_1_bss_6F2D8[index * 2] = value;
        }
        break;
    }
}
/* fzgx:end fn_1_A4C9C */

/* fzgx:begin fn_1_A4DF4 noprologue */
#include "types.h"

extern u32 fn_80067898(u32);
extern u32 lbl_1_bss_6F1DC;
extern u8 lbl_1_bss_6F1D8;

void fn_1_A4DF4(void) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 45) {
    v0 = 0xA9090000;
    v0 += 4608;
    fn_80067898(v0);
    }
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 45) {
    v1 = 0xA9090000;
    v1 += 5632;
    fn_80067898(v1);
    }
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 45) {
    v2 = 0xA9090000;
    v2 += 7168;
    fn_80067898(v2);
    }
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 45) {
    v3 = 0xA9090000;
    v3 += 9216;
    fn_80067898(v3);
    }
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 45) {
    v4 = 0xA9090000;
    v4 += 11776;
    fn_80067898(v4);
    }
    if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 45) {
    v5 = 0xA9090000;
    v5 += 3328;
    fn_80067898(v5);
    }
}
/* fzgx:end fn_1_A4DF4 */

/* fzgx:begin fn_1_A4F18 */
void fn_1_A4F18(s32 value) {
    u8 *state = (u8 *)&lbl_1_bss_6EA98;

    if (state[0x7A0] != (u8)value) {
        fn_80067344(1, 0x10, 0xB0270000, 0x7F);

        switch ((u8)value) {
        case 3:
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9091A00);
            }
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9060000);
            }
            break;
        case 2:
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9091A00);
            }
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9060100);
            }
            break;
        case 1:
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9091A00);
            }
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9060200);
            }
            break;
        case 0:
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9091A00);
            }
            if (!state[0x740] && *(u32 *)(state + 0x744) <= 0x2D) {
                fn_80067898(0xA9060300);
            }
            break;
        }
    }

    state[0x7A0] = value;
}
/* fzgx:end fn_1_A4F18 */

/* fzgx:begin fn_1_A50C8 */
void fn_1_A50C8(s32 index) {
    u32 value;

    if (index > 0x28) {
        value = 0xA9100700;
    } else {
        value = lbl_1_rodata_45D0[index * 2];
    }

    fn_80067344(2, 0xF, 0xB0270000, 0x7F);

    if (!lbl_1_bss_6F1D8 && lbl_1_bss_6F1DC <= 0x2D) {
        fn_80067898(value);
    }
}
/* fzgx:end fn_1_A50C8 */

/* fzgx:begin fn_1_A514C */
extern u32 lbl_1_rodata_45D0[82];
extern u8 lbl_1_bss_6F1D8;
extern u32 lbl_1_bss_6F1DC;

extern void fn_80067344(s32, s32, u32, s32);
extern void fn_80067898(u32);

void fn_1_A514C(s32 index) {
    u32 offset;
    u32 value;

    if (index <= 0x28) {
        value = lbl_1_rodata_45D0[index * 2 + 1];
        fn_80067344(2, 0xf, 0xb0270000, 0x7f);
        if (lbl_1_bss_6F1D8 == 0 && lbl_1_bss_6F1DC <= 0x2d) {
            fn_80067898(value);
        }
    }
}
/* fzgx:end fn_1_A514C */

/* fzgx:begin fn_1_A51C8 */
void fn_1_A51C8(s16 index) {
    u32 value;

    if (index <= 6) {
        value = lbl_1_rodata_4718[index];
        fn_80067344(2, 0xF, 0xB0270000, 0x7F);

        if (!lbl_1_bss_6F1D8 && lbl_1_bss_6F1DC <= 0x2D) {
            fn_80067898(value);
        }
    }
}
/* fzgx:end fn_1_A51C8 */

/* fzgx:begin fn_1_A5244 */
void fn_1_A5244(u8 index) {
    u32 value;

    if (index <= 0x1D) {
        value = lbl_1_rodata_4730[index];
        fn_80067344(1, 2, 0xB0270000, 0x7F);

        if (lbl_1_bss_6F1DC <= 0x2D) {
            fn_80067898(value);
        }
    }
}
/* fzgx:end fn_1_A5244 */

/* fzgx:begin fn_1_A52B0 */
void fn_1_A52B0(s32 index) {
    u32 value;

    if ((u8)index > 0x1E) {
        return;
    }

    value = lbl_1_rodata_47A8[(u8)index - 1];

    fn_80067344(1, 0xF, 0xB0270000, 0x7F);

    if (!lbl_1_bss_6F1D8 && lbl_1_bss_6F1DC <= 0x2D) {
        fn_80067898(value);
    }
}
/* fzgx:end fn_1_A52B0 */

/* fzgx:begin fn_1_A5330 */
void fn_1_A5330(u8 value, s16 index) {
    lbl_1_bss_6F41C[index] = value;
}
/* fzgx:end fn_1_A5330 */

/* fzgx:begin fn_1_A5344 */
#include "types.h"


extern void fn_80067898(u32 value);

#pragma opt_dead_assignments off
void fn_1_A5344(u8 value, s16 index) {
    u8 *table;
    s32 i;

    table = (*(u8 (*)[])&lbl_1_bss_6EA98) + 0x984;
    if (table[index] > value) {
        for (i = 0; i < (s32)(table[index] - value); i++) {
            if ((value - i) % 10 == 0 &&
                (*(u8 (*)[])&lbl_1_bss_6EA98)[0x740] == 0 &&
                *(u32 *)((*(u8 (*)[])&lbl_1_bss_6EA98) + 0x744) <= 0x2d) {
                fn_80067898(0xa9010300);
            }
        }
    } else if (table[index] < value) {
        for (i = 0; i < (s32)(value - table[index]); i++) {
            if ((value - i) % 10 == 0 &&
                (*(u8 (*)[])&lbl_1_bss_6EA98)[0x740] == 0 &&
                *(u32 *)((*(u8 (*)[])&lbl_1_bss_6EA98) + 0x744) <= 0x2d) {
                fn_80067898(0xa9010300);
            }
        }
    }

    table[index] = value;
}
#pragma opt_dead_assignments reset
/* fzgx:end fn_1_A5344 */

/* fzgx:begin fn_1_A5470 */
// Starts the requested sound and suppresses playback when the channel limit is reached.
void fn_1_A5470(s32 value) {
    s32 sound_id;
    u32 sound_resource;

    if (value == -1) {
        return;
    }

    sound_id = (s8)value;
    sound_id = fn_1_86690(sound_id);
    sound_resource = (u32)lbl_1_rodata_4820[(s8)sound_id];

    fn_80067344(1, 0x10, 0xB0270000, 0x7F);
    if (sound_resource != 0 && lbl_1_bss_6F1D8 == 0 &&
        lbl_1_bss_6F1DC <= 0x2D) {
        fn_80067898(sound_resource);
    }
}
/* fzgx:end fn_1_A5470 */

/* fzgx:begin fn_1_A54FC noprologue */
#include "types.h"

typedef struct SoundData {
    u8 pad_000[0x740];
    u8 unk_740;
    u8 pad_741[3];
    u32 unk_744;
    u8 pad_748[0x5c];
    u32 unk_7a4;
    u8 pad_7a8[0xd8];
    s16 unk_880;
} SoundData;

extern SoundData lbl_1_bss_6EA98;
extern void fn_80067898(u32 value);

void fn_1_A54FC(void) {
    u32 flags;

    if ((lbl_1_bss_6EA98.unk_7a4 & 1) == 0 ||
        lbl_1_bss_6EA98.unk_740 != 0) {
        return;
    }

    lbl_1_bss_6EA98.unk_880++;
    if (lbl_1_bss_6EA98.unk_880 == 0x78) {
        if (lbl_1_bss_6EA98.unk_740 == 0 &&
            lbl_1_bss_6EA98.unk_744 <= 0x2d) {
            fn_80067898(0xA9065100);
        }
        flags = lbl_1_bss_6EA98.unk_7a4;
        lbl_1_bss_6EA98.unk_880 = 0;
        lbl_1_bss_6EA98.unk_7a4 = flags & ~1;
    }
}
/* fzgx:end fn_1_A54FC */

/* fzgx:begin fn_1_A5590 */
// fn_1_A5590: empty in retail (single blr).
void fn_1_A5590(void) {
}
/* fzgx:end fn_1_A5590 */

/* fzgx:begin fn_1_A5848 */
u8 fn_1_A5848(void) {
    return lbl_1_bss_6F1E0;
}
/* fzgx:end fn_1_A5848 */

/* fzgx:begin fn_1_A5858 */
void fn_1_A5858(u8 value) {
    lbl_1_bss_6F1E0 = value;
}
/* fzgx:end fn_1_A5858 */

/* fzgx:begin fn_1_A5864 */
void fn_1_A5864(void) {
    if (lbl_1_bss_6EAD0.unk_0 != 0) {
        if (lbl_1_bss_6EAD0.unk_0->unk_0 != 0 &&
            fn_8004C658(lbl_1_bss_6EAD0.unk_0->unk_0) == 3) {
            if (fn_8004BBCC(lbl_1_bss_6EAD0.unk_0->unk_0) == 0) {
                ADXT_Pause(lbl_1_bss_6EAD0.unk_0->unk_0, 1);
            }
        }

        if (lbl_1_bss_6EAD0.unk_0->unk_4 != 0 &&
            fn_8004C658(lbl_1_bss_6EAD0.unk_0->unk_4) == 3) {
            if (fn_8004BBCC(lbl_1_bss_6EAD0.unk_0->unk_4) == 0) {
                ADXT_Pause(lbl_1_bss_6EAD0.unk_0->unk_4, 1);
            }
        }

        if (fn_1_3FC38() != 0) {
            if (lbl_1_bss_6EAC6.unk_0 != 0) {
                fn_800674FC(0x10, 0xA0000300, 0);
            }
            if (lbl_1_bss_6EAC6.unk_0 != 0) {
                fn_800674FC(0x10, 0xA0000400, 0);
            }
            if (lbl_1_bss_6EAC6.unk_0 != 0) {
                fn_800674FC(0, 0xA0020000, 0);
            }
        }
    }
}
/* fzgx:end fn_1_A5864 */

/* fzgx:begin fn_1_A59AC */
// Updates active sound handles and emits the sound-system notification when enabled.
void fn_1_A59AC(void) {
    u8 *sound = (u8 *)&lbl_1_bss_6EA98;

    if (*(u32 *)(sound + 0x38) != 0) {
        if (*(u32 *)(*(u32 *)(sound + 0x38)) != 0 &&
            fn_8004C658(*(u32 *)(*(u32 *)(sound + 0x38))) == 3 &&
            fn_8004BBCC(*(u32 *)(*(u32 *)(sound + 0x38))) != 0) {
            ADXT_Pause(*(u32 *)(*(u32 *)(sound + 0x38)), 0);
        }

        if (fn_1_3FC38() == 0 || *(u8 *)(sound + 0x749) == 0) {
            if (*(u32 *)(*(u32 *)(sound + 0x38) + 4) != 0 &&
                fn_8004C658(*(u32 *)(*(u32 *)(sound + 0x38) + 4)) == 3 &&
                fn_8004BBCC(*(u32 *)(*(u32 *)(sound + 0x38) + 4)) != 0) {
                ADXT_Pause(*(u32 *)(*(u32 *)(sound + 0x38) + 4), 0);
            }
        }

        if (fn_1_3FC38() != 0 && *(u8 *)(sound + 0x2e) != 0) {
            fn_800674FC(0, 0xA0030000, 0);
        }
    }
}
/* fzgx:end fn_1_A59AC */
