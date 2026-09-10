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

extern void ADXT_Stop(u32 value);
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
    ADXT_Stop(lbl_1_bss_6EAD0->first);
    ADXT_Stop(lbl_1_bss_6EAD0->second);
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

/* fzgx:begin fn_17_48D0 */
extern u32 lbl_17_bss_14C;
extern u8 lbl_17_data_0[420];
extern u32 lbl_17_bss_150[4];

extern void fn_1_435C(u32);
extern void fn_1_3F8C(void *, void (*)(void), int, int);
extern void fn_1_789E8(void);
extern void fn_1_9A5CC(void);
extern void fn_1_7E9C4(void);
extern void fn_1_7EAE8(void);
extern void fn_1_78EBC(void);
extern void fn_1_9A7BC(void);
extern void fn_1_7ACDC(int);

void fn_17_48D0(void) {
    u8 *base = lbl_17_data_0 + 0x60000;

    fn_1_435C(lbl_17_bss_14C);
    fn_1_3F8C(base + 0x40ac, fn_1_789E8, 0, 0x15);
    fn_1_3F8C(base + 0x40b8, fn_1_9A5CC, 0, 0x17);
    fn_1_435C(lbl_17_bss_150[0]);
    fn_1_3F8C(base + 0x40c8, fn_1_7E9C4, 0, 4);
    fn_1_3F8C(base + 0x40d0, fn_1_7EAE8, 0, 0x1d);
    fn_1_3F8C(base + 0x40d8, fn_1_78EBC, 0, 7);
    fn_1_3F8C(base + 0x40e4, fn_1_9A7BC, 0, 10);
    fn_1_7ACDC(0x31);
}
/* fzgx:end fn_17_48D0 */

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

/* fzgx:begin fn_17_4E54 */
typedef struct InterviewState {
    u8 pad_000[0x8]; void *field_008; u8 pad_00c[0x20]; f32 angle_02c;
    u8 pad_030[0x2d8]; void *object_308;
} InterviewState;
typedef struct InterviewObject {
    u8 pad_000[0x328]; s8 kind_328; u8 pad_329[0x67]; u32 flags_390;
    u8 pad_394[0xc]; void *field_3a0; u8 pad_3a4[0x16]; s16 index_3ba;
} InterviewObject;
typedef struct InterviewValue { void *value_0; } InterviewValue;
typedef struct InterviewEntry { u8 pad_000[0x334]; InterviewValue *value_334; } InterviewEntry;
extern u8 lbl_17_bss_0;
extern f32 lbl_17_rodata_0[6];
extern u8 lbl_17_data_63E50[592];
extern u8 lbl_17_data_64150[76];
extern void lbl_8006DCA4(void);
extern void lbl_8006E0B4(f32, f32, f32);
extern void mathutil_mtxA_rotate_y(s32);
extern void lbl_8006E14C(f32);
extern void fn_1_55FC4(f32);
extern void fn_80072558(void);
extern void lbl_8006DB74(void *);
extern void fn_1_56000(s32, s32, s32);
extern void fn_1_55FF0(f32);
extern void fn_1_14E5E4(void *, f32, s16);
extern void OSPanic(void *, s32, void *, ...);
extern void fn_1_556B8(void *);
extern void lbl_8006DAEC(void);
extern void fn_1_87610(void *, void *);
extern void fn_1_875B4(void *, f32, void *, s8);
extern void lbl_8006DC20(void);
extern void lbl_8006DBAC(void *);
extern void fn_1_FCFA4(void *);

#pragma opt_propagation off
void fn_17_4E54(void) {
    f32 *constants = lbl_17_rodata_0;
    InterviewState *state = (InterviewState *)&lbl_17_bss_0;
    InterviewObject *object;
    InterviewEntry *entry;
    f32 angle = state->angle_02c;
    u8 matrix[0x30];
    s16 index;

    lbl_8006DCA4();
    lbl_8006E0B4(constants[8], constants[131], constants[132]);
    if (state->angle_02c > constants[39]) mathutil_mtxA_rotate_y(0x3000);
    else mathutil_mtxA_rotate_y(0x2000);
    lbl_8006E14C(angle);
    fn_1_55FC4(angle);
    fn_80072558();
    lbl_8006DB74(matrix);
    fn_1_56000(1, 3, 1);
    fn_1_55FF0(constants[6]);
    object = (InterviewObject *)state->object_308;
    if (object != 0) {
        index = object->index_3ba;
        if ((object->flags_390 & 0x04000000) != 0) {
            if (object->field_3a0 == 0) return;
            fn_1_14E5E4(object->field_3a0, constants[6], index);
        } else {
            if (object->kind_328 >= 0x29)
                OSPanic(lbl_17_data_63E50, 0xc20, lbl_17_data_64150);
            entry = (InterviewEntry *)((u8 *)state->object_308 + index * 0xc);
            fn_1_556B8(entry->value_334->value_0);
            lbl_8006DAEC();
            fn_1_87610(state->object_308, state->object_308);
            fn_1_875B4(state->object_308, constants[6],
                       state->object_308,
                       (s8)((InterviewObject *)state->object_308)->index_3ba);
            lbl_8006DC20();
        }
        lbl_8006DBAC(matrix);
        fn_1_FCFA4(state->field_008);
    }
    fn_1_56000(1, 3, 1);
}
#pragma opt_propagation reset
/* fzgx:end fn_17_4E54 */

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

/* fzgx:begin fn_17_67C4 */
extern u8 lbl_17_bss_0;
extern const f32 lbl_17_rodata_1C;

typedef struct InterviewObject InterviewObject;

typedef struct InterviewRef {
    u8 padding[4];
    InterviewObject *object;
} InterviewRef;

typedef struct InterviewState {
    u8 flags0[2];
    u8 flag2;
    u8 flag3;
    u8 padding[0xd4];
    InterviewRef ref;
} InterviewState;

struct InterviewObject {
    u8 padding[0x150];
    void *data;
};

typedef struct InterviewData {
    u8 padding[0x4c];
    f32 value_a;
    f32 value_b;
} InterviewData;

extern void fn_1_935E4(void *, void *, void *, f32);

#pragma opt_propagation off
void fn_17_67C4(void *arg) {
    InterviewState *state = (InterviewState *)&lbl_17_bss_0;
    InterviewObject *object;
    InterviewData *data;
    u32 ref;

    ref = (u32)state + 0xd8;
    object = *(InterviewObject **)(ref + 4);
    data = (InterviewData *)object->data;
    if (data->value_a == data->value_b) {
        fn_1_935E4(object, (u8 *)object + 0x148, arg, lbl_17_rodata_1C);
        if (state->flag2 != 0)
            state->flag2 = 0;
        if (state->flag3 != 0)
            state->flag3 = 0;
    }
}
#pragma opt_propagation reset
/* fzgx:end fn_17_67C4 */

/* fzgx:begin fn_17_6848 */
typedef struct InterviewObject InterviewObject;

struct InterviewObject {
    u8 pad0[0x88];
    void *field88;
    u8 pad8C[0x1c];
    f32 values[3];
    u8 padB4[0x94];
    u8 field148[1];
};

typedef struct InterviewGlobals {
    InterviewObject *object0;
    u8 pad4[4];
    InterviewObject *object8;
    InterviewObject *objectC;
} InterviewGlobals;

extern InterviewGlobals lbl_17_bss_D8;
extern u8 lbl_17_bss_1;
extern const f32 lbl_17_rodata_20;

extern u32 fn_1_12C710(void *arg0);
extern s16 fn_1_12CB04(u32 arg0);
extern void fn_1_935E4(InterviewObject *arg0, void *arg1, void *arg2, f32 arg3);

void fn_17_6848(void *arg0, u8 arg1, f32 arg2) {
    f32 value = arg2;
    InterviewObject *object = lbl_17_bss_D8.object0;
    s16 mode;
    u32 state;

    state = fn_1_12C710(object->field88);
    lbl_17_bss_1 = arg1;
    mode = fn_1_12CB04(state);

    switch (mode) {
    case 2:
        fn_1_935E4(object, object->field148, arg0, value);
        fn_1_935E4(lbl_17_bss_D8.object8, (u8 *)lbl_17_bss_D8.object8 + 0x148, arg0, value);
        fn_1_935E4(lbl_17_bss_D8.objectC, (u8 *)lbl_17_bss_D8.objectC + 0x148, arg0, value);
        object->values[0] = lbl_17_rodata_20;
        object->values[1] = lbl_17_rodata_20;
        object->values[2] = lbl_17_rodata_20;
        {
            InterviewObject *o8 = lbl_17_bss_D8.object8;
            o8->values[0] = lbl_17_rodata_20;
            o8->values[1] = lbl_17_rodata_20;
            o8->values[2] = lbl_17_rodata_20;
        }
        {
            InterviewObject *oC = lbl_17_bss_D8.objectC;
            oC->values[0] = lbl_17_rodata_20;
            oC->values[1] = lbl_17_rodata_20;
            oC->values[2] = lbl_17_rodata_20;
        }
        break;
    case 1:
        fn_1_935E4(object, object->field148, arg0, value);
        fn_1_935E4(lbl_17_bss_D8.object8, (u8 *)lbl_17_bss_D8.object8 + 0x148, arg0, value);
        object->values[0] = lbl_17_rodata_20;
        object->values[1] = lbl_17_rodata_20;
        object->values[2] = lbl_17_rodata_20;
        {
            InterviewObject *o8b = lbl_17_bss_D8.object8;
            o8b->values[0] = lbl_17_rodata_20;
            o8b->values[1] = lbl_17_rodata_20;
            o8b->values[2] = lbl_17_rodata_20;
        }
        break;
    case 0:
        fn_1_935E4(object, object->field148, arg0, value);
        object->values[0] = lbl_17_rodata_20;
        object->values[1] = lbl_17_rodata_20;
        object->values[2] = lbl_17_rodata_20;
        break;
    default:
        break;
    }
}
/* fzgx:end fn_17_6848 */

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

/* fzgx:begin fn_17_71DC */
extern f32 lbl_17_bss_160[4];
extern u8 lbl_17_bss_314[64];
extern const f32 lbl_17_rodata_20;
extern u32 lbl_17_rodata_25C[50];

extern void fn_1_7BCCC(f32 *value);
extern void fn_80035680(u8 *value, f32 a, f32 b, f32 c);
extern void fn_80035690(u8 *value, f32 a, f32 b, f32 c);
extern void fn_80035420(u8 *value, int index, f32 value2);
extern void fn_800356AC(u8 *value, u32 *data);
extern void GXInitLightDistAttn(u8 *value, int index, f32 a, f32 b);
extern void fn_1_7BB80(u8 *value, int index);
extern void fn_1_7BD6C(int value);

void fn_17_71DC(void) {
    u32 data;

    fn_1_7BCCC(lbl_17_bss_160);
    fn_80035680(lbl_17_bss_314, lbl_17_bss_160[0], lbl_17_bss_160[1], lbl_17_bss_160[2]);
    fn_80035690(lbl_17_bss_314, lbl_17_bss_160[0], lbl_17_bss_160[1], lbl_17_bss_160[2]);
    fn_80035420(lbl_17_bss_314, 0, lbl_17_rodata_20);
    data = lbl_17_rodata_25C[0];
    fn_800356AC(lbl_17_bss_314, &data);
    GXInitLightDistAttn(lbl_17_bss_314, 0, 0.0f, 0.0f);
    fn_1_7BB80(lbl_17_bss_314, 1);
    fn_1_7BD6C(1);
}
/* fzgx:end fn_17_71DC */

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
