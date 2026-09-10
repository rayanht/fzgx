#include "types.h"
extern u8 lbl_3_bss_8F200[];
extern void fn_1_FC414(void *, int);
extern u8 lbl_3_bss_A1778[12];

/* fzgx:begin fn_3_1180C */
struct Fn3State {
    u8 pad0[4];
    u32 value;
    u8 pad8[2];
    s16 field_a;
    u8 pad_c[0x18];
    s16 mode;
};

extern struct Fn3State lbl_3_bss_7EDD8;
extern s16 lbl_3_data_1A40[2];
extern s16 lbl_1_bss_96A;

extern void fn_1_4A00(int, int, u32);
extern void fn_1_FDFF4(void);
extern void fn_1_435C(u32);
extern void fn_1_426C(s16);

void fn_3_1180C(void) {
    if (lbl_3_bss_7EDD8.mode == 0xf) {
        fn_1_4A00(0, 0xf, lbl_3_bss_7EDD8.value);
    } else if (lbl_3_bss_7EDD8.mode == 0) {
        fn_1_FDFF4();
        if (lbl_3_data_1A40[0] != -1) {
            fn_1_435C(lbl_3_bss_7EDD8.value);
            fn_1_426C(lbl_3_bss_7EDD8.field_a);
            lbl_3_bss_7EDD8.field_a = -1;
            lbl_1_bss_96A = lbl_3_data_1A40[0];
            lbl_3_data_1A40[0] = -1;
        } else {
            lbl_3_data_1A40[0] = 0x5f;
        }
    }
}
/* fzgx:end fn_3_1180C */

/* fzgx:begin fn_3_11930 */
extern u16 lbl_3_bss_7EDD8[52];

struct PasteEntry {
    u8 pad[0x2c];
    int active;
};

int fn_3_11930(void) {
    u8 i;
    u8 * base;

    for (i = 0; i < 4; i++) {
        struct PasteEntry *entry = (struct PasteEntry *)(((u8 *)lbl_3_bss_7EDD8) + i * 4);
        if (entry->active != 0) {
            return 1;
        }
    }
    return 0;
}
/* fzgx:end fn_3_11930 */

/* fzgx:begin fn_3_11974 */
extern u16 lbl_3_bss_7EDD8[52];

void fn_3_11974(void) {
    u32 *fields = (u32 *)&lbl_3_bss_7EDD8;
    fields[11] = 0;
    fields[12] = 0;
    fields[13] = 0;
    fields[14] = 0;
}
/* fzgx:end fn_3_11974 */

/* fzgx:begin fn_3_11994 */
struct Sig_fn_8004E278_fn_8004E278_Arg0 {
    u32 unk_0;
};

extern void fn_80008BA8(struct Sig_fn_8004E278_fn_8004E278_Arg0 *, u32, u32);
extern void fn_80008BEC(struct Sig_fn_8004E278_fn_8004E278_Arg0 *, int, u32);


void fn_3_11994(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg_sp0) {
    s32 temp_r5;
    u8 var_r30;
    void *temp_r4;

    var_r30 = 0;
    while (var_r30 < 4U) {
        if (arg0 != (s32) var_r30) {
            temp_r5 = var_r30 * 0x2060;
            temp_r4 = (void *)(arg2 + temp_r5);
            if (arg1 == (s16) (*(s16 *)((u8 *)(temp_r4) + 0))) {
                if ((*(s32 *)((u8 *)(temp_r4) + 4)) & 0x80000000) {
                    fn_80008BA8((struct Sig_fn_8004E278_fn_8004E278_Arg0 *)(arg3 + temp_r5), (u32)(temp_r4), 0x2060U);
                }
            } else {
                fn_80008BEC((struct Sig_fn_8004E278_fn_8004E278_Arg0 *)(arg3 + temp_r5), 0, 0x2060U);
            }
        }
        var_r30 += 1;
            }
}
/* fzgx:end fn_3_11994 */

/* fzgx:begin fn_3_11F60 */
struct Fn3State {
    u32 value0;
    u32 value1;
};

extern struct Fn3State lbl_3_bss_7EDD8;
extern u8 lbl_3_bss_8F200[];
extern void fn_1_FC414(void *, int);

void fn_3_11F60(u32 value0, u32 value1) {
    lbl_3_bss_7EDD8.value1 = value1;
    lbl_3_bss_7EDD8.value0 = value0;
    fn_1_FC414(lbl_3_bss_8F200, 1);
}
/* fzgx:end fn_3_11F60 */

/* fzgx:begin fn_3_11FA0 */
extern u32 lbl_3_bss_7EDD8[26];

void fn_3_11FA0(void) {
    lbl_3_bss_7EDD8[0] = 0;
    lbl_3_bss_7EDD8[1] = 0;
}
/* fzgx:end fn_3_11FA0 */

/* fzgx:begin fn_3_11FB4 */
extern u8 lbl_3_bss_7EDD8[0x68];
extern u32 lbl_3_bss_7EDC0[3];

void fn_3_11FB4(u8 value_47, u8 value_46, u32 value_7EDC0) {
    lbl_3_bss_7EDD8[0x47] = value_47;
    lbl_3_bss_7EDC0[0] = value_7EDC0;
    lbl_3_bss_7EDD8[0x46] = value_46;
}
/* fzgx:end fn_3_11FB4 */

/* fzgx:begin fn_3_1304C */
// fn_3_1304C: empty in retail (single blr).
void fn_3_1304C(void) {
}
/* fzgx:end fn_3_1304C */

/* fzgx:begin fn_3_13050 */
// fn_3_13050: empty in retail (single blr).
void fn_3_13050(void) {
}
/* fzgx:end fn_3_13050 */

/* fzgx:begin fn_3_13054 */
// fn_3_13054: empty in retail (single blr).
void fn_3_13054(void) {
}
/* fzgx:end fn_3_13054 */

/* fzgx:begin fn_3_13058 */
// fn_3_13058: empty in retail (single blr).
void fn_3_13058(void) {
}
/* fzgx:end fn_3_13058 */

/* fzgx:begin fn_3_1305C */
// fn_3_1305C: empty in retail (single blr).
void fn_3_1305C(void) {
}
/* fzgx:end fn_3_1305C */

/* fzgx:begin fn_3_13060 */
// fn_3_13060: empty in retail (single blr).
void fn_3_13060(void) {
}
/* fzgx:end fn_3_13060 */

/* fzgx:begin fn_3_13064 */
// fn_3_13064: empty in retail (single blr).
void fn_3_13064(void) {
}
/* fzgx:end fn_3_13064 */

/* fzgx:begin fn_3_13068 */
// fn_3_13068: empty in retail (single blr).
void fn_3_13068(void) {
}
/* fzgx:end fn_3_13068 */

/* fzgx:begin fn_3_1306C */
// fn_3_1306C: empty in retail (single blr).
void fn_3_1306C(void) {
}
/* fzgx:end fn_3_1306C */

/* fzgx:begin fn_3_13070 */
// fn_3_13070: empty in retail (single blr).
void fn_3_13070(void) {
}
/* fzgx:end fn_3_13070 */

/* fzgx:begin fn_3_13074 */
// fn_3_13074: empty in retail (single blr).
void fn_3_13074(void) {
}
/* fzgx:end fn_3_13074 */

/* fzgx:begin fn_3_13078 */
// fn_3_13078: empty in retail (single blr).
void fn_3_13078(void) {
}
/* fzgx:end fn_3_13078 */

/* fzgx:begin fn_3_1307C */
u8 fn_3_1307C(void) {
    return lbl_3_bss_A1778[0];
}
/* fzgx:end fn_3_1307C */

/* fzgx:begin fn_3_1308C */
typedef struct {
    u8 pad0[4];
    u32 unk4;
    u8 pad8[0xc];
    u32 unk14;
    u32 unk18;
    u32 unk1c;
} Fn3BssA1768;

extern Fn3BssA1768 lbl_3_bss_A1768;

void fn_3_1308C(u32 arg0, u32 arg1, u32 arg2) {
    lbl_3_bss_A1768.unk14 = arg1;
    lbl_3_bss_A1768.unk18 = arg2;
    lbl_3_bss_A1768.unk4 = arg0;
    lbl_3_bss_A1768.unk1c = arg0;
}
/* fzgx:end fn_3_1308C */

/* fzgx:begin fn_3_130A8 */
typedef struct {
    u32 value0;
    u8 pad[0x10];
    u32 value14;
    u32 value18;
    u32 value1c;
} CustomizeState;

extern u32 lbl_3_bss_A1768;

void fn_3_130A8(void) {
    CustomizeState *state = (CustomizeState *)&lbl_3_bss_A1768;

    state->value14 = 0;
    state->value18 = 0;
    state->value0 = 0;
    state->value1c = 0;
}
/* fzgx:end fn_3_130A8 */
