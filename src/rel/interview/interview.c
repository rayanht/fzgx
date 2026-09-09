#include "types.h"

/* fzgx:begin fn_17_23C */
extern s32 lbl_17_bss_58[2];
extern s32 lbl_17_bss_24[4];
extern void fn_17_6C8(void);

void fn_17_23C(void) {
    if (lbl_17_bss_58[0] & 0x10000000) {
        if (lbl_17_bss_24[0] != 0) {
            lbl_17_bss_24[0]--;
        }
        if (lbl_17_bss_24[0] == 0) {
            lbl_17_bss_24[0] = 30;
            lbl_17_bss_58[0] &= ~0x10000000;
            fn_17_6C8();
        }
    }
}
/* fzgx:end fn_17_23C */

/* fzgx:begin fn_17_394 */
extern u8 lbl_17_data_63E30[32];
extern s16 lbl_1_bss_962;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

typedef void (*InterviewFunc)(void);

typedef struct InterviewEntry {
    u32 unk_0;
    InterviewFunc func;
    u32 value_8;
    u32 value_c;
} InterviewEntry;

void fn_17_394(void) {
    InterviewEntry *entry;
    s16 index;

    entry = (InterviewEntry *)lbl_17_data_63E30;
    index = lbl_1_bss_962;
    entry += index - 0xc5;
    lbl_1_bss_71688 = entry->value_8;
    lbl_1_bss_7168C = entry->value_c;
    entry->func();
}
/* fzgx:end fn_17_394 */

/* fzgx:begin fn_17_1794 */
// fn_17_1794: empty in retail (single blr).
void fn_17_1794(void) {
}
/* fzgx:end fn_17_1794 */

/* fzgx:begin fn_17_2D24 */
extern u32 lbl_17_bss_14;
extern u32 lbl_17_bss_18[2];
extern void fn_17_3270(u32, u32);

void fn_17_2D24(void) {
    fn_17_3270(lbl_17_bss_14, lbl_17_bss_18[0]);
}
/* fzgx:end fn_17_2D24 */

/* fzgx:begin fn_17_3270 */
typedef struct InterviewState {
    u32 first;
    u32 second;
} InterviewState;

extern InterviewState *lbl_1_bss_6EAD0;
extern u32 lbl_801A6410;

extern void fn_8004C698(u32 value);
extern void fn_80051E30(u32 value);
extern void fn_1_A0AA4(void);
extern void fn_17_416C(void);
extern void fn_17_4858(void);
extern void fn_17_49BC(void);
extern void fn_17_4FE0(void);
extern u32 lbl_17_bss_C;
extern u8 lbl_17_data_63E50[592];
extern void fn_1_46B4(u32, u32, void *, u32);
extern void fn_1_435C(void *);
extern void fn_1_41A8(void);
extern void fn_1_410A0(void);
extern void fn_17_602C(void);

void fn_17_3270(void *arg0, void *arg1) {
    fn_8004C698(lbl_1_bss_6EAD0->first);
    fn_8004C698(lbl_1_bss_6EAD0->second);
    fn_80051E30(lbl_1_bss_6EAD0->second);
    fn_1_A0AA4();
    fn_17_416C();
    fn_17_4858();
    fn_17_49BC();
    fn_17_4FE0();

    if (lbl_17_bss_C != 0) {
        fn_1_46B4(lbl_801A6410, lbl_17_bss_C, lbl_17_data_63E50, 0x81d);
        lbl_17_bss_C = 0;
    }

    fn_1_435C(arg0);
    fn_1_41A8();
    fn_1_435C(arg1);
    fn_1_41A8();
    fn_1_410A0();
    fn_17_602C();
}
/* fzgx:end fn_17_3270 */

/* fzgx:begin fn_17_4214 */
extern u32 lbl_17_rodata_1B8;

struct fn_17_4214_Arg0 {
    u8 pad_0[0x88];
    u32 unk_88;
    u8 pad_8C[0x14];
    u16 unk_A0;
};
struct fn_17_4214_Copy12 { u32 a[3]; };

void fn_17_4214(struct fn_17_4214_Arg0 *arg0) {
    if ((s32)arg0->unk_88 != 4) { return; }
    *(struct fn_17_4214_Copy12 *)((u8 *)(u32)arg0 + 168) = *(struct fn_17_4214_Copy12 *)&lbl_17_rodata_1B8;
    arg0->unk_A0 = 12288;
}
/* fzgx:end fn_17_4214 */

/* fzgx:begin fn_17_4540 */
typedef struct {
    u8 pad[0x88];
    // Hardware-style shared state must be read exactly as published.
    volatile int value;
} InterviewState;

typedef struct {
    u8 pad[0xc];
    // Hardware-style shared state must be read exactly as published.
    volatile s16 value;
} InterviewData;

extern InterviewState *lbl_17_bss_D8;
extern InterviewData lbl_17_bss_60;

void fn_17_4540(void) {
    InterviewState *state = lbl_17_bss_D8;
    InterviewData *data = &lbl_17_bss_60;

    if (state->value != 7)
        return;
    if (data->value == 8)
        return;
}
/* fzgx:end fn_17_4540 */

/* fzgx:begin fn_17_4858 */
extern u32 lbl_17_bss_58[2];
extern u32 lbl_17_bss_198[95];
extern u8 lbl_17_data_63E50[592];
extern u32 lbl_801A6410;

extern void fn_1_8F494(void *arg0);
extern void fn_1_46B4(u32 arg0, u32 arg1, void *arg2, s32 arg3);

void fn_17_4858(void) {
    if ((lbl_17_bss_58[0] & 0x00400000) != 0 &&
        lbl_17_bss_198[0] != 0) {
        fn_1_8F494((void *)lbl_17_bss_198[0]);
        fn_1_46B4(lbl_801A6410, lbl_17_bss_198[0], lbl_17_data_63E50, 0xae9);
        lbl_17_bss_198[0] = 0;
    }
}
/* fzgx:end fn_17_4858 */

/* fzgx:begin fn_17_49B8 */
// fn_17_49B8: empty in retail (single blr).
void fn_17_49B8(void) {
}
/* fzgx:end fn_17_49B8 */

/* fzgx:begin fn_17_49BC */
extern void fn_1_79100(void);

void fn_17_49BC(void) {
    fn_1_79100();
}
/* fzgx:end fn_17_49BC */

/* fzgx:begin fn_17_4E50 */
// fn_17_4E50: empty in retail (single blr).
void fn_17_4E50(void) {
}
/* fzgx:end fn_17_4E50 */

/* fzgx:begin fn_17_4FE0 */
struct fn_17_4FE0_lbl_17_bss_0 {
    u8 pad_0[0x8];
    u32 unk_8;
    u8 pad_C[0x2FC];
    u32 unk_308;
    u32 unk_30C;
};
struct fn_17_4FE0_lbl_1_bss_6D82C {
    u32 unk_0;
};
struct fn_17_4FE0_lbl_801A6410 {
    u32 unk_0;
};

extern struct fn_17_4FE0_lbl_17_bss_0 lbl_17_bss_0;
extern struct fn_17_4FE0_lbl_1_bss_6D82C lbl_1_bss_6D82C;
extern struct fn_17_4FE0_lbl_801A6410 lbl_801A6410;
extern u32 fn_1_12A734(u32);
extern u32 fn_1_46B4(u32, u32, u32, u32);
extern u32 lbl_17_data_63E50;
extern void fn_1_14DBCC(void *);
extern void fn_1_7F934(void *);
extern void fn_1_FDFF4(void);
extern void fn_80071718(void *);

void fn_17_4FE0(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    struct fn_17_4FE0_lbl_17_bss_0 *p_lbl_17_bss_0;
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;
    u32 v6;
    u32 v7;
    s32 v8;
    u32 v9;
    u32 v10;
    u32 v11;
    u32 v12;
    u32 t0, t2, t4, t7;
    p_lbl_17_bss_0 = (struct fn_17_4FE0_lbl_17_bss_0 *)&lbl_17_bss_0;
    v0 = p_lbl_17_bss_0->unk_308;
    v1 = v0;
    v2 = arg1;
    v3 = arg3;
    v4 = arg2;
    if (v0 != 0) {
    v1 = *(u32 *)((u8 *)v1 + 804);
    if ((s32)v1 != -1) {
    t0 = fn_1_12A734(v1);
    v1 = t0;
    v1 = p_lbl_17_bss_0->unk_308;
    *(u32 *)((u8 *)v1 + 804) = -1;
    }
    v1 = p_lbl_17_bss_0->unk_308;
    fn_1_7F934((void *)v1);
    v3 = (u32)&lbl_801A6410;
    v2 = p_lbl_17_bss_0->unk_308;
    v4 = (u32)&lbl_17_data_63E50;
    v1 = *(u32 *)((u8 *)v3 + 0);
    v3 = 3134;
    t2 = fn_1_46B4(v1, v2, (u32)v4, v3);
    v1 = t2;
    p_lbl_17_bss_0->unk_308 = 0;
    }
    v5 = p_lbl_17_bss_0->unk_30C;
    v6 = v2;
    v7 = v5;
    v8 = v3;
    v9 = v4;
    if (v5 != 0) {
    fn_1_14DBCC((void *)v7);
    v8 = (u32)&lbl_801A6410;
    v6 = p_lbl_17_bss_0->unk_30C;
    v9 = (u32)&lbl_17_data_63E50;
    v7 = *(u32 *)((u8 *)v8 + 0);
    v8 = 3139;
    t4 = fn_1_46B4(v7, v6, (u32)v9, v8);
    v7 = t4;
    p_lbl_17_bss_0->unk_30C = 0;
    }
    v10 = lbl_1_bss_6D82C.unk_0;
    v11 = v10;
    if (v10 != 0) {
    fn_80071718((void *)v11);
    lbl_1_bss_6D82C.unk_0 = 0;
    }
    v12 = v11;
    if (p_lbl_17_bss_0->unk_8 != 0) {
    fn_1_FDFF4();
    v12 = lbl_801A6410.unk_0;
    t7 = fn_1_46B4(v12, p_lbl_17_bss_0->unk_8, (u32)&lbl_17_data_63E50, 3152);
    v12 = t7;
    }
}
/* fzgx:end fn_17_4FE0 */

/* fzgx:begin fn_17_5FA8 */
typedef struct InterviewState {
    u8 pad_00[0x84];
    s16 field_84;
    u8 pad_86[0x12];
    s16 field_98;
} InterviewState;

typedef struct InterviewGlobals {
    s32 field_00;
    u8 pad_04[0x10];
    InterviewState *field_14;
} InterviewGlobals;

extern InterviewGlobals lbl_17_bss_60;
extern u32 lbl_17_bss_58[2];
extern void fn_17_60B4(void);
extern void fn_1_154F1C(void);
extern void fn_17_8C7C(s32 arg0);

void fn_17_5FA8(void) {
    InterviewGlobals *globals = &lbl_17_bss_60;
    InterviewState *state = globals->field_14;

    fn_17_60B4();
    if (globals->field_00 >= state->field_84 + 0x14a &&
        (lbl_17_bss_58[0] & 0x00800000) != 0 &&
        globals->field_00 < state->field_98) {
        fn_1_154F1C();
        fn_17_8C7C(0x140);
    }
}
/* fzgx:end fn_17_5FA8 */

/* fzgx:begin fn_17_602C */
extern u8 lbl_17_bss_60[118];
extern u8 lbl_17_data_63E50[592];
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32, u32, void *, u32);

void fn_17_602C(void) {
    u32 value;

    value = *(u32 *)(lbl_17_bss_60 + 0x10);
    if (value != 0) {
        fn_1_46B4(lbl_801A6410, value, lbl_17_data_63E50, 0xed7);
    }
}
/* fzgx:end fn_17_602C */

/* fzgx:begin fn_17_6078 */
extern u8 lbl_17_bss_D8[34];
extern void fn_17_65F4(void);

typedef struct {
    u8 pad[0x88];
    int state;
} InterviewState;

void fn_17_6078(void) {
    InterviewState *state = *(InterviewState **)lbl_17_bss_D8;

    switch (state->state) {
    case 0x1c:
        fn_17_65F4();
        break;
    default:
        break;
    }
}
/* fzgx:end fn_17_6078 */

/* fzgx:begin fn_17_60B4 */
typedef struct InterviewState {
    s32 value;
    u8 unk04[8];
    s16 status;
    u8 unk0E[6];
    void *data;
} InterviewState;

typedef struct InterviewData {
    u8 unk00[0x84];
    s16 lower_bound;
    u8 unk86[0x12];
    s16 upper_bound;
} InterviewData;

typedef struct InterviewManager {
    u8 unk00[0x18];
    u32 flags;
} InterviewManager;

extern InterviewState lbl_17_bss_60;
extern InterviewManager *lbl_17_bss_D8;
extern void fn_17_613C(void);

void fn_17_60B4(void) {
    InterviewState *state = &lbl_17_bss_60;
    InterviewData *data = state->data;

    if (state->status == 9 &&
        state->value >= data->lower_bound &&
        state->value < data->upper_bound) {
        lbl_17_bss_D8->flags |= 0x08000000;
        fn_17_613C();
    } else {
        lbl_17_bss_D8->flags &= ~0x08000000;
    }
}
/* fzgx:end fn_17_60B4 */

/* fzgx:begin fn_17_7020 */
typedef struct InterviewObject {
    u8 pad0[0x14];
    struct InterviewText *text;
} InterviewObject;

typedef struct InterviewText {
    u8 pad0[0x9A];
    u8 text[1];
} InterviewText;

extern u8 lbl_17_data_64458[4];
extern u8 lbl_17_bss_D8[34];

extern void fn_1_97204(void *arg0, u8 *arg1);

void fn_17_7020(InterviewObject *object) {
    InterviewText *text;
    u8 *value;

    text = object->text;
    if (text->text[0] == 0) {
        value = lbl_17_data_64458;
    } else {
        u8 *cursor;

        cursor = text->text;
        while (*cursor != 0x3C && *cursor != 0) {
            cursor++;
        }
        *cursor = 0;
        value = text->text;
    }
    fn_1_97204(*(void **)(lbl_17_bss_D8 + 4), value);
}
/* fzgx:end fn_17_7020 */

/* fzgx:begin fn_17_71C0 */
typedef struct InterviewState {
    u8 pad[4];
    u32 flags;
} InterviewState;

void fn_17_71C0(InterviewState *self) {
    self->flags &= ~2;
    self->flags &= 1;
}
/* fzgx:end fn_17_71C0 */

/* fzgx:begin fn_17_72BC */
// fn_17_72BC: empty in retail (single blr).
void fn_17_72BC(void) {
}
/* fzgx:end fn_17_72BC */

/* fzgx:begin fn_17_74C0 */
extern u8 lbl_17_bss_D8[34];
extern void fn_17_7728(void *);

typedef struct InterviewChild {
    u8 pad_00[0x42];
    s16 value_42;
    s16 value_44;
} InterviewChild;

typedef struct InterviewState {
    u8 pad_00[0x88];
    s32 value_88;
} InterviewState;

typedef struct Interview {
    u8 pad_00[0x0c];
    s16 value_0c;
    u8 pad_0e[0x4a];
    s16 value_58;
} Interview;

void fn_17_74C0(Interview *interview) {
    InterviewState *state = *(InterviewState **)lbl_17_bss_D8;
    InterviewChild *child = (InterviewChild *)((u8 *)interview + 0x18);

    interview->value_58 = 0;
    child->value_42 = interview->value_0c;
    child->value_44 = state->value_88;
    fn_17_7728(child);
}
/* fzgx:end fn_17_74C0 */

/* fzgx:begin fn_17_87C0 */
extern f32 lbl_17_rodata_0[];
extern u32 lbl_1_rodata_26F8[];

extern u8 fn_1_B7C00(void);
extern void fn_1_4F734(void*);

typedef struct {
    u32 word04;
    f32 float08;
    f32 float0c;
    f32 float10;
    u32 word14[7];
    f32 float30;
    u32 word34;
    u32 word38[9];
} InterviewParams;

void fn_17_87C0(f32 value) {
    f32* rodata = lbl_17_rodata_0;
    InterviewParams params;

    if (!fn_1_B7C00()) {
        params = *(InterviewParams*)lbl_1_rodata_26F8;
        params.word04 = 0x00008c03;
        params.float08 = rodata[168];
        params.float0c = rodata[169];
        params.float10 = rodata[108];
        params.float30 = value;
        params.word34 = 5;
        fn_1_4F734(&params.word04);
    }
}
/* fzgx:end fn_17_87C0 */

/* fzgx:begin fn_17_8D28 */
#include "font.h"

typedef struct {
    u32 words[22];
} Sig_fn_1_51914_fn_1_51914_state;


struct fn_17_8D28_Copy88 { u32 a[22]; };
struct fn_17_8D28_lbl_17_rodata_0 {
    u8 pad_0[0x20];
    f32 unk_20;
    u8 pad_24[0x84];
    f32 unk_A8;
    u8 pad_AC[0x104];
    f32 unk_1B0;
    u8 pad_1B4[0x124];
    f32 unk_2D8;
    f32 unk_2DC;
    f32 unk_2E0;
};

extern int fn_1_4F734(FontDrawPacket *);
extern struct fn_17_8D28_lbl_17_rodata_0 lbl_17_rodata_0;
extern u32 fn_17_8E68(u32, u32);
extern u32 lbl_1_rodata_26F8;
extern void fn_1_51914(const Sig_fn_1_51914_fn_1_51914_state *);
extern void fn_1_51990(void *);

void fn_17_8D28(void) {
    struct fn_17_8D28_lbl_17_rodata_0 *p_lbl_17_rodata_0;
    f32 v1;
    f32 v0;
    f32 v3;
    f32 v2;
    struct fn_17_8D28_Copy88 loc_8;
    /* frame */
    p_lbl_17_rodata_0 = (struct fn_17_8D28_lbl_17_rodata_0 *)&lbl_17_rodata_0;
    loc_8 = *(struct fn_17_8D28_Copy88 *)&lbl_1_rodata_26F8;
    loc_8.a[0] = (0x10000 - 29689);
    fn_1_51914((const Sig_fn_1_51914_fn_1_51914_state *)&loc_8);
    loc_8 = *(struct fn_17_8D28_Copy88 *)&lbl_1_rodata_26F8;
    v0 = p_lbl_17_rodata_0->unk_20;
    v1 = p_lbl_17_rodata_0->unk_2D8;
    loc_8.a[0] = (0x10000 - 29694);
    *(f32 *)((u8 *)&loc_8 + 4) = v0;
    *(f32 *)((u8 *)&loc_8 + 8) = v1;
    *(f32 *)((u8 *)&loc_8 + 12) = p_lbl_17_rodata_0->unk_A8;
    loc_8.a[12] = 5;
    fn_1_51990((void *)&loc_8);
    fn_1_4F734((FontDrawPacket *)&loc_8);
    loc_8 = *(struct fn_17_8D28_Copy88 *)&lbl_1_rodata_26F8;
    v2 = p_lbl_17_rodata_0->unk_2DC;
    v3 = p_lbl_17_rodata_0->unk_2E0;
    loc_8.a[0] = (0x10000 - 29695);
    *(f32 *)((u8 *)&loc_8 + 4) = v2;
    *(f32 *)((u8 *)&loc_8 + 8) = v3;
    *(f32 *)((u8 *)&loc_8 + 12) = p_lbl_17_rodata_0->unk_1B0;
    loc_8.a[12] = 5;
    fn_1_4F734((FontDrawPacket *)&loc_8);
    fn_17_8E68(28, 64);
}
/* fzgx:end fn_17_8D28 */
