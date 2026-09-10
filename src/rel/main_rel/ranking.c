#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/ranking.h"

extern u32 lbl_801A6410[];
extern void fn_1_46B4(u32, Obj_1_bss_8EF20_At0 *, u8 *, u32);
extern Obj_1_bss_8EF20_At0 *fn_1_4630(u32, u32, u8 *, u32);
extern void fn_1_451C(void);
extern void fn_1_A1340(void);
extern s16 lbl_1_bss_962;
extern s16 lbl_1_bss_96A;
extern void fn_1_A1360(void);
extern void fn_1_A1364(void);
extern u8 lbl_1_bss_8F420[8];
extern f32 lbl_1_rodata_D8C8[18];
extern void fn_80008BEC(void *dst, int value, int size);
extern void fn_1_1568C4(void *);
extern void fn_80008BA8(void *, void *, int);
extern void fn_1_1574E0(Obj_1_bss_8F428 *entry, u32 value);
extern void fn_8006B7B4(void *);
extern void fn_8006B870(void);
extern void fn_1_157950(void);
extern void fn_1_157FC8(void);
extern u32 fn_1_157920(void);
extern void fn_1_4060(void);
extern u32 lbl_1_bss_8F57C[3];
extern void fn_1_9AD88(void);
extern void fn_1_1594AC(int index, int flag);
extern void OSReport(const char *format, ...);
extern void fn_1_465D0(void *object, int value);
extern void fn_1_9AD54(void);

extern void fn_1_1568C4(void *entry);

extern u32 lbl_801A6410[];
extern void fn_1_46B4(u32, Obj_1_bss_8EF20_At0 *, u8 *, u32);
extern Obj_1_bss_8EF20_At0 *fn_1_4630(u32, u32, u8 *, u32);
extern void fn_1_1569E8(void *entry);

/* fzgx:begin fn_1_1554D0 */
// Rebuild the ranking object when the previous one has been consumed.
void fn_1_1554D0(void) {
    Obj_1_bss_8EF20_At0 *obj = lbl_1_bss_8EF20.unk_0;

    if (obj != 0) {
        fn_1_46B4(lbl_801A6410[0], obj, lbl_1_data_49B08, 0xD50);
        lbl_1_bss_8EF20.unk_0 = 0;
    }

    if (lbl_1_bss_8EF20.unk_0 == 0) {
        lbl_1_bss_8EF20.unk_0 =
            fn_1_4630(lbl_801A6410[0], 0x230, lbl_1_data_49B08, 0xD55);
    }
}
/* fzgx:end fn_1_1554D0 */

/* fzgx:begin fn_1_15555C */
void fn_1_15555C(void) {
    Obj_1_bss_8EF20_At0 *obj = lbl_1_bss_8EF20.unk_0;
    if (obj != 0) {
        fn_1_46B4(lbl_801A6410[0], obj, lbl_1_data_49B08, 0xD63);
        lbl_1_bss_8EF20.unk_0 = 0;
    }
}
/* fzgx:end fn_1_15555C */

/* fzgx:begin fn_1_155F7C */
u32 fn_1_155F7C(void) {
    return lbl_1_bss_8F3E0;
}
/* fzgx:end fn_1_155F7C */

/* fzgx:begin fn_1_155F8C */
u32 fn_1_155F8C(void) {
    return lbl_1_bss_8F3E4.unk_0;
}
/* fzgx:end fn_1_155F8C */

/* fzgx:begin fn_1_155F9C */
void fn_1_155F9C(u32 value) {
    lbl_1_bss_8F3E0 = value;
}
/* fzgx:end fn_1_155F9C */

/* fzgx:begin fn_1_155FA8 */
void fn_1_155FA8(u32 value) {
    lbl_1_bss_8F3E4.unk_0 = value;
}
/* fzgx:end fn_1_155FA8 */

/* fzgx:begin fn_1_156198 */
extern s32 fn_1_156218(u32 arg, void *out0, void *out1, void *out2);
extern u32 lbl_1_bss_8F3FC[9];

u32 *fn_1_156198(u32 arg0) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;
    u32 v6;
    struct { u32 a[14]; } loc_78;
    struct { u32 a[14]; } loc_40;
    struct { u32 a[14]; } loc_8;
    /* frame */
    u32 t0;
    t0 = fn_1_156218(arg0, (void *)&loc_78, (void *)&loc_40, (void *)&loc_8);
    v0 = t0;
    if ((s32)t0 == 0) {
        v0 = 0;
    } else {
        v1 = loc_78.a[2];
        v2 = loc_78.a[3];
        v3 = loc_78.a[4];
        v4 = loc_78.a[5];
        v5 = loc_78.a[6];
        v6 = loc_78.a[7];
        lbl_1_bss_8F3FC[0] = loc_78.a[0];
        lbl_1_bss_8F3FC[1] = loc_78.a[1];
        lbl_1_bss_8F3FC[2] = v1;
        lbl_1_bss_8F3FC[3] = v2;
        lbl_1_bss_8F3FC[4] = v3;
        lbl_1_bss_8F3FC[5] = v4;
        lbl_1_bss_8F3FC[6] = v5;
        lbl_1_bss_8F3FC[7] = v6;
        v0 = (u32)&lbl_1_bss_8F3FC;
    }
    return (u32 *)v0;
}
/* fzgx:end fn_1_156198 */

/* fzgx:begin fn_1_1564D0 */
void fn_1_1564D0(void) {
    fn_1_451C();
    fn_1_A1340();
    if (lbl_1_bss_962 != 0x7d) {
        lbl_1_bss_96A = 0x7d;
    }
}
/* fzgx:end fn_1_1564D0 */

/* fzgx:begin fn_1_156510 */
void fn_1_156510(void) {
    fn_1_A1360();
}
/* fzgx:end fn_1_156510 */

/* fzgx:begin fn_1_156530 */
// fn_1_156530: empty in retail (single blr).
void fn_1_156530(void) {
}
/* fzgx:end fn_1_156530 */

/* fzgx:begin fn_1_156534 */
void fn_1_156534(void) {
    fn_1_A1364();
}
/* fzgx:end fn_1_156534 */

/* fzgx:begin fn_1_156554 */
// fn_1_156554: empty in retail (single blr).
void fn_1_156554(void) {
}
/* fzgx:end fn_1_156554 */

/* fzgx:begin fn_1_156558 */
// fn_1_156558: empty in retail (single blr).
void fn_1_156558(void) {
}
/* fzgx:end fn_1_156558 */

/* fzgx:begin fn_1_15655C */
// fn_1_15655C: empty in retail (single blr).
void fn_1_15655C(void) {
}
/* fzgx:end fn_1_15655C */

/* fzgx:begin fn_1_156560 */
// fn_1_156560: empty in retail (single blr).
void fn_1_156560(void) {
}
/* fzgx:end fn_1_156560 */

/* fzgx:begin fn_1_156564 */
// fn_1_156564: empty in retail (single blr).
void fn_1_156564(void) {
}
/* fzgx:end fn_1_156564 */

/* fzgx:begin fn_1_156568 */
// fn_1_156568: empty in retail (single blr).
void fn_1_156568(void) {
}
/* fzgx:end fn_1_156568 */

/* fzgx:begin fn_1_15656C */
void fn_1_15656C(void) {
    lbl_1_bss_8F420[0] = 0;
}
/* fzgx:end fn_1_15656C */

/* fzgx:begin fn_1_15657C */
// fn_1_15657C: empty in retail (single blr).
void fn_1_15657C(void) {
}
/* fzgx:end fn_1_15657C */

/* fzgx:begin fn_1_156580 */
// fn_1_156580: empty in retail (single blr).
void fn_1_156580(void) {
}
/* fzgx:end fn_1_156580 */

/* fzgx:begin fn_1_156584 */
// fn_1_156584: empty in retail (single blr).
void fn_1_156584(void) {
}
/* fzgx:end fn_1_156584 */

/* fzgx:begin fn_1_156588 */
// fn_1_156588: empty in retail (single blr).
void fn_1_156588(void) {
}
/* fzgx:end fn_1_156588 */

/* fzgx:begin fn_1_15658C */
// fn_1_15658C: empty in retail (single blr).
void fn_1_15658C(void) {
}
/* fzgx:end fn_1_15658C */

/* fzgx:begin fn_1_156590 */
// fn_1_156590: empty in retail (single blr).
void fn_1_156590(void) {
}
/* fzgx:end fn_1_156590 */

/* fzgx:begin fn_1_156594 */
// fn_1_156594: empty in retail (single blr).
void fn_1_156594(void) {
}
/* fzgx:end fn_1_156594 */

/* fzgx:begin fn_1_156598 */
// fn_1_156598: empty in retail (single blr).
void fn_1_156598(void) {
}
/* fzgx:end fn_1_156598 */

/* fzgx:begin fn_1_15659C */
typedef struct {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
    u8 unk_30;
    u8 pad_31[3];
    f32 unk_34;
    u8 pad_38[0x1c];
    u32 unk_54;
    u32 unk_58;
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
    u8 unk_80;
    u8 pad_81[3];
    f32 unk_84;
    u8 pad_88[0x18];
} RankingEntry;

extern f32 lbl_1_rodata_D8C8[18];
extern void fn_80008BEC(void *dst, int value, int size);

// Clears both ranking entries to their default sentinel values.
void fn_1_15659C(void) {
    RankingEntry *obj;
    f32 value;
    int i;

    fn_80008BEC(&lbl_1_bss_8F428, 0, 0x140);
    obj = (RankingEntry *)&lbl_1_bss_8F428;
    value = lbl_1_rodata_D8C8[0];
    for (i = 0; i < 2; i++) {
        obj->unk_4 = -1;
        obj->unk_C = -1;
        obj->unk_10 = -1;
        obj->unk_14 = -1;
        obj->unk_1C = -1;
        obj->unk_20 = -1;
        obj->unk_18 = -1;
        obj->unk_8 = -1;
        obj->unk_24 = -1;
        obj->unk_28 = -1;
        obj->unk_2C = -1;
        obj->unk_34 = value;
        obj->unk_30 = 0;
        obj->unk_54 = -1;
        obj->unk_5C = -1;
        obj->unk_60 = -1;
        obj->unk_64 = -1;
        obj->unk_6C = -1;
        obj->unk_70 = -1;
        obj->unk_68 = -1;
        obj->unk_58 = -1;
        obj->unk_74 = -1;
        obj->unk_78 = -1;
        obj->unk_7C = -1;
        obj->unk_84 = value;
        obj->unk_80 = 0;
        obj++;
    }
}
/* fzgx:end fn_1_15659C */

/* fzgx:begin fn_1_15665C */
typedef Obj_1_bss_8F428 RankingEntry;

// Initializes one ranking entry and registers it with the ranking system.
void fn_1_15665C(void *owner, s32 index) {
    RankingEntry *entry;

    entry = (RankingEntry *)((u8 *)&lbl_1_bss_8F428 + index * 0x50);
    fn_80008BEC(entry, 0, 0x50);
    entry->unk_0 = 0;
    entry->unk_4 = (u32)owner;
    entry->unk_8 = -1;
    entry->unk_C = -1;
    entry->unk_10 = -1;
    entry->unk_14 = -1;
    entry->unk_1C = -1;
    entry->unk_20 = -1;
    entry->unk_18 = -1;
    entry->unk_24 = -1;
    entry->unk_28 = -1;
    entry->unk_2C = -1;
    entry->unk_34 = lbl_1_rodata_D8C8[0];
    fn_1_1568C4(entry);
}
/* fzgx:end fn_1_15665C */

/* fzgx:begin fn_1_1566F8 */
// Updates the indexed ranking entry's value through the shared ranking helper.
void fn_1_1566F8(s32 index, void *arg) {
    fn_80008BA8(&lbl_1_bss_8F428.unk_34 + index * 0x14, arg, 0x1c);
}
/* fzgx:end fn_1_1566F8 */

/* fzgx:begin fn_1_156730 */
// Clears the indexed ranking entry's status and score markers.
void fn_1_156730(s32 index) {
    u32 *entry = &lbl_1_bss_8F428.unk_0 + index * 0x14;

    entry[0] = 0;
    entry[1] = -1;
}
/* fzgx:end fn_1_156730 */

/* fzgx:begin fn_1_156754 */
// Processes the indexed ranking entry unless its status marks it as unused.
void fn_1_156754(s32 index) {
    u32 *entry = &lbl_1_bss_8F428.unk_0 + index * 0x14;

    if (entry[1] + 0x10000 != 0xffff) {
        fn_1_1569E8(entry);
        fn_1_1568C4(entry);
    }
}
/* fzgx:end fn_1_156754 */

/* fzgx:begin fn_1_1567A8 noprologue */
#include "types.h"

typedef struct {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x2c];
    f32 unk_34;
    u8 pad_38[0x14];
    u8 unk_4c;
} Entry;

extern Entry lbl_1_bss_8F428;
extern f32 lbl_1_rodata_D8C8[18];
extern void fn_1_1569E8(Entry *);
extern void fn_1_1568C4(Entry *);
extern void fn_1_156B18(Entry *);
extern void fn_1_1569A0(Entry *);
extern void fn_1_156C08(Entry *);
extern void fn_1_156D9C(Entry *);
extern void fn_1_157070(Entry *);
extern void fn_1_156F54(Entry *);
extern void fn_1_157200(Entry *);
extern void fn_1_157358(Entry *);
extern void fn_1_1576B4(Entry *);
extern void fn_1_157598(Entry *);

void fn_1_1567A8(s32 index) {
    Entry *entry;
    u32 value;
    f32 field_value;

    entry = &lbl_1_bss_8F428 + index;
    value = entry->unk_4;
    if (entry->unk_4 + 0x10000 != 0xffff) {
        field_value = entry->unk_34;
        if (lbl_1_rodata_D8C8[0] == field_value) {
            if (entry->unk_4 + 0x10000 == 0xffff) {
                return;
            } else {
                fn_1_1569E8(entry);
                fn_1_1568C4(entry);
                return;
            }
        } else if (entry->unk_4c & 0x80) {
            fn_1_156B18(entry);
            fn_1_1568C4(entry);
        } else {
            fn_1_1569A0(entry);
            fn_1_156C08(entry);
            fn_1_156D9C(entry);
            fn_1_157070(entry);
            fn_1_156F54(entry);
            fn_1_157200(entry);
            fn_1_157358(entry);
        }
        fn_1_1576B4(entry);
        fn_1_157598(entry);
    }
}
/* fzgx:end fn_1_1567A8 */

/* fzgx:begin fn_1_156884 */
// Refreshes an entry when its ranking value is not the invalid sentinel.
void fn_1_156884(s32 index) {
    Obj_1_bss_8F428 *entry;
    u32 value;

    entry = (Obj_1_bss_8F428 *)((u8 *)&lbl_1_bss_8F428 + index * 0x50);
    value = entry->unk_4;
    if (value + 0x10000 != 0xffff) {
        fn_1_1574E0(entry, value);
    }
}
/* fzgx:end fn_1_156884 */

/* fzgx:begin fn_1_1569A0 */
typedef struct {
    u32 flags;
    u8 _pad04[4];
    void *data;
} fn_1_1569A0_State;

void fn_1_1569A0(fn_1_1569A0_State *state) {
    if (state->flags & 1) {
        fn_8006B7B4(state->data);
        state->flags &= ~1;
    }
}
/* fzgx:end fn_1_1569A0 */

/* fzgx:begin fn_1_1569E8 */
typedef struct {
    u32 flags;
    u8 _pad04[8];
    void *data0;
    void *data1;
    void *data2;
    s32 value;
    void *data3;
    void *data4;
    u8 _pad24[4];
    void *data5;
    void *data6;
} fn_1_1569E8_State;

/* Releases pending ranking resources and resets their status flags. */
void fn_1_1569E8(void *entry) {
    fn_1_1569E8_State *state = (fn_1_1569E8_State *)entry;

    if (state->flags & 4) {
        fn_8006B7B4(state->data1);
        state->flags &= ~4;
    }
    if (state->flags & 2) {
        fn_8006B7B4(state->data0);
        state->flags &= ~2;
    }
    if (state->flags & 8) {
        fn_8006B7B4(state->data2);
        state->flags &= ~8;
    }
    if (state->flags & 0x20) {
        fn_8006B7B4(state->data3);
        state->flags &= ~0x20;
    }
    if (state->flags & 0x40) {
        fn_8006B7B4(state->data4);
        state->flags &= ~0x40;
    }
    if ((u32)(state->value + 0x10000) != 0xffff) {
        fn_8006B870();
        state->value = -1;
    }
    state->flags &= ~0x10;
    if (state->flags & 0x80) {
        fn_8006B7B4(state->data5);
        state->flags &= ~0x80;
    }
    if (state->flags & 0x100) {
        fn_8006B7B4(state->data6);
        state->flags &= ~0x100;
    }
}
/* fzgx:end fn_1_1569E8 */

/* fzgx:begin fn_1_156B18 */
typedef struct {
    u32 flags;
    u8 _pad04[8];
    void *data0;
    void *data1;
    void *data2;
    s32 value;
    void *data3;
    void *data4;
} fn_1_156B18_State;

void fn_1_156B18(fn_1_156B18_State *state) {
    if (state->flags & 4) {
        fn_8006B7B4(state->data1);
        state->flags &= ~4;
    }
    if (state->flags & 2) {
        fn_8006B7B4(state->data0);
        state->flags &= ~2;
    }
    if (state->flags & 8) {
        fn_8006B7B4(state->data2);
        state->flags &= ~8;
    }
    if (state->flags & 32) {
        fn_8006B7B4(state->data3);
        state->flags &= ~32;
    }
    if (state->flags & 64) {
        fn_8006B7B4(state->data4);
        state->flags &= ~64;
    }
    if ((u32)(state->value + 0x10000) != 0xffff) {
        fn_8006B870();
        state->value = -1;
    }
    state->flags &= ~0x10;
}
/* fzgx:end fn_1_156B18 */

/* fzgx:begin fn_1_1577D0 noprologue */
#include "types.h"

extern f32 lbl_1_rodata_D920;
extern struct fn_1_1577D0_lbl_1_bss_8F568 lbl_1_bss_8F568;
extern u32 lbl_1_data_4C788;

struct fn_1_1577D0_lbl_1_bss_8F568 {
    u8 unk_0;
    u8 pad_1[0x3];
    f32 unk_4;
    f32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
};

f32 fn_1_1577D0(u32 arg0, u32 arg1, f32 arg2) {
    lbl_1_bss_8F568.unk_0 = arg0;
    lbl_1_bss_8F568.unk_4 = lbl_1_rodata_D920;
    lbl_1_bss_8F568.unk_8 = arg2;
    lbl_1_bss_8F568.unk_C = *(u32 *)((u8 *)&lbl_1_data_4C788 + ((s8)arg1 << 2));
    lbl_1_bss_8F568.unk_10 = 1;
    lbl_1_bss_8F568.unk_14 = 0;
    lbl_1_bss_8F568.unk_18 = 600;
    return arg2;
}
/* fzgx:end fn_1_1577D0 */

/* fzgx:begin fn_1_1578C4 noprologue */
#include "types.h"

extern u32 fn_1_157920(void);
extern u32 fn_1_157950(void);
extern u32 fn_1_157FC8(void);
extern u32 fn_1_4060(void);
extern u8 lbl_1_bss_8F568;

void fn_1_1578C4(void) {
    s8 v0;
    u32 t2;
    v0 = (s8)lbl_1_bss_8F568;
    switch (v0) {
    case 0:
    fn_1_157950();
    break;
    case 1:
    fn_1_157FC8();
    }
    t2 = fn_1_157920();
    if ((s32)t2 == 0) {
    fn_1_4060();
    }
}
/* fzgx:end fn_1_1578C4 */

/* fzgx:begin fn_1_157920 */
// Return the current ranking value.
u32 fn_1_157920(void) {
    return lbl_1_bss_8F578;
}
/* fzgx:end fn_1_157920 */

/* fzgx:begin fn_1_157930 */
u32 fn_1_157930(void) {
    return lbl_1_bss_8F57C[0];
}
/* fzgx:end fn_1_157930 */

/* fzgx:begin fn_1_157940 */
void fn_1_157940(void) {
    lbl_1_bss_8F578 = 0;
}
/* fzgx:end fn_1_157940 */

/* fzgx:begin fn_1_1586A8 */
// fn_1_1586A8: empty in retail (single blr).
void fn_1_1586A8(void) {
}
/* fzgx:end fn_1_1586A8 */

/* fzgx:begin fn_1_158980 */
// fn_1_158980: empty in retail (single blr).
void fn_1_158980(void) {
}
/* fzgx:end fn_1_158980 */

/* fzgx:begin fn_1_15903C */
// fn_1_15903C: empty in retail (single blr).
void fn_1_15903C(void) {
}
/* fzgx:end fn_1_15903C */

/* fzgx:begin fn_1_159040 */
void fn_1_159040(void) {
    fn_1_9AD88();
}
/* fzgx:end fn_1_159040 */

/* fzgx:begin fn_1_159060 */
// fn_1_159060: empty in retail (single blr).
void fn_1_159060(void) {
}
/* fzgx:end fn_1_159060 */

/* fzgx:begin fn_1_159064 */
// fn_1_159064: returns a constant.
int fn_1_159064(void) {
    return 0;
}
/* fzgx:end fn_1_159064 */

/* fzgx:begin fn_1_159440 */
typedef struct {
    u8 pad_0[0x30];
    u32 unk_30;
    u32 unk_34;
    u8 pad_38[0x4];
} fn_1_159440_RankingEntry;

// Preserve the current ranking entry before refreshing its state.
void fn_1_159440(int index, int flag) {
    fn_1_159440_RankingEntry *entry;

    entry = &((fn_1_159440_RankingEntry *)&lbl_1_data_4C810)[index];
    entry->unk_34 = entry->unk_30;
    fn_1_1594AC(index, flag);
}
/* fzgx:end fn_1_159440 */

/* fzgx:begin fn_1_159478 */
typedef struct {
    u8 pad[0x34];
    u32 unk_34;
    u8 tail[4];
} Entry159478;

void fn_1_159478(int index, int unused, int value) {
    ((Entry159478 *)&lbl_1_data_4C810)[index].unk_34 = value;
    fn_1_1594AC(index, unused);
}
/* fzgx:end fn_1_159478 */

/* fzgx:begin fn_1_1594AC */
void fn_1_1594AC(int index, int flag) {
    Obj_1_data_4C810 *entry;
    s16 value;
    int offset;

    // Activate the selected ranking entry and publish its referenced indices.
    entry = (Obj_1_data_4C810 *)((u8 *)&lbl_1_data_4C810 + index * 0x3c);
    if (entry->unk_2C >= 0x10) {
        OSReport((const char *)lbl_1_data_4C900);
    }

    if (flag != 0) {
        fn_1_465D0((void *)entry->unk_0, 6);
    } else {
        fn_1_465D0((void *)entry->unk_0, 5);
    }

    offset = 0;
    for (;;) {
        value = *(s16 *)((u8 *)entry->unk_4 + offset);
        if (value == -1) {
            break;
        }
        ((int *)lbl_1_bss_8F588)[value] = index;
        offset += 2;
    }

    fn_80008BEC((u8 *)entry + 8, 0, 0x20);
    entry->unk_28 = 1;
    entry->unk_2A = 0;
    entry->unk_38 = flag;
}
/* fzgx:end fn_1_1594AC */

/* fzgx:begin fn_1_15AC00 */
// Return the address of the ranking state byte at offset 0x3f.
u8 *fn_1_15AC00(void) {
    return &lbl_1_bss_8F878.unk_3F;
}
/* fzgx:end fn_1_15AC00 */

/* fzgx:begin fn_1_15B3E8 */
// Return the current ranking state byte.
u8 fn_1_15B3E8(void) {
    return lbl_1_bss_8F878.unk_3A;
}
/* fzgx:end fn_1_15B3E8 */

/* fzgx:begin fn_1_15B3F8 */
// Return the ranking state byte at offset 0x3b.
u8 fn_1_15B3F8(void) {
    return lbl_1_bss_8F878.unk_3B;
}
/* fzgx:end fn_1_15B3F8 */

/* fzgx:begin fn_1_15B408 */
// Returns the current ranking state.
u8 fn_1_15B408(void) {
    return lbl_1_bss_8F878.unk_3C;
}
/* fzgx:end fn_1_15B408 */

/* fzgx:begin fn_1_15B418 */
u8 *fn_1_15B418(void) {
    return &lbl_1_bss_8F878.unk_18;
}
/* fzgx:end fn_1_15B418 */

/* fzgx:begin fn_1_15B428 */
// fn_1_15B428: empty in retail (single blr).
void fn_1_15B428(void) {
}
/* fzgx:end fn_1_15B428 */

/* fzgx:begin fn_1_15B4F8 */
// fn_1_15B4F8: empty in retail (single blr).
void fn_1_15B4F8(void) {
}
/* fzgx:end fn_1_15B4F8 */

/* fzgx:begin fn_1_15B4FC */
void fn_1_15B4FC(void) {
    fn_1_9AD54();
}
/* fzgx:end fn_1_15B4FC */

/* fzgx:begin fn_1_15B51C */
// fn_1_15B51C: empty in retail (single blr).
void fn_1_15B51C(void) {
}
/* fzgx:end fn_1_15B51C */

/* fzgx:begin fn_1_15B520 */
void fn_1_15B520(void) {
    fn_1_9AD88();
}
/* fzgx:end fn_1_15B520 */

/* fzgx:begin fn_1_15B540 */
// fn_1_15B540: empty in retail (single blr).
void fn_1_15B540(void) {
}
/* fzgx:end fn_1_15B540 */

/* fzgx:begin fn_1_15B544 */
typedef struct {
    u32 flags;
    u8 pad_04[0x3c];
} fn_1_15B544_RankingEntry;

// Set the high flag on each ranking entry managed by the singleton.
void fn_1_15B544(void) {
    s16 i;
    fn_1_15B544_RankingEntry *entry;

    i = 0;
    entry = (fn_1_15B544_RankingEntry *)lbl_1_bss_3BE0->unk_54;
    while (i < (s32)lbl_1_bss_3BE0->unk_48) {
        entry->flags |= 0x80000000u;
        i++;
        entry = (fn_1_15B544_RankingEntry *)((u8 *)entry + 0x40);
    }
}
/* fzgx:end fn_1_15B544 */

/* fzgx:begin fn_1_15B588 */
// Clears the high bit of each ranking entry flag.
void fn_1_15B588(void) {
    u8 *entry;
    s16 i;
    Obj_1_data_2A7E0_At3C *obj;

    obj = lbl_1_data_2A7E0.unk_3C;
    entry = (u8 *)obj;
    i = 0;
    while (i < obj->unk_5E) {
        u32 *value = *(u32 **)(entry + 0xc4);

        entry += 4;
        i++;
        *value &= 0x7fffffff;
    }
}
/* fzgx:end fn_1_15B588 */

/* fzgx:begin fn_1_15B5CC */
void fn_1_15B5CC(void) {
    u8 *entry;
    s16 i;
    Obj_1_data_2A7E0_At3C *obj;

    obj = lbl_1_data_2A7E0.unk_3C;
    entry = (u8 *)obj;
    i = 0;
    while (i < obj->unk_5D) {
        u32 *value = *(u32 **)(entry + 0x74);

        entry += 4;
        i++;
        *value &= 0x7fffffff;
    }
}
/* fzgx:end fn_1_15B5CC */

/* fzgx:begin fn_1_15B610 */
void fn_1_15B610(void) {
    u8 *entry;
    s16 i;
    Obj_1_data_2A7E0_At3C *obj;

    obj = lbl_1_data_2A7E0.unk_3C;
    entry = (u8 *)obj;
    i = 0;
    while (i < *((u8 *)obj + 0x5d)) {
        u32 *value = *(u32 **)(entry + 0x74);

        entry += 4;
        i++;
        *value |= 0x80000000u;
    }
}
/* fzgx:end fn_1_15B610 */

/* fzgx:begin fn_1_15B654 */
void fn_1_15B654(void) {
    u8 *entry;
    s16 i;
    Obj_1_data_2A7E0_At3C *obj;

    obj = lbl_1_data_2A7E0.unk_3C;
    entry = (u8 *)obj;
    i = 0;
    while (i < obj->unk_5C) {
        u32 *value = *(u32 **)(entry + 0x60);

        entry += 4;
        i++;
        *value |= 0x80000000u;
    }
}
/* fzgx:end fn_1_15B654 */

/* fzgx:begin fn_1_15B698 */
u32 fn_1_15B698(s32 kind, u32 *value) {
    Obj_1_data_2A7E0_At3C *obj;

    obj = lbl_1_data_2A7E0.unk_3C;
    switch (kind) {
    case 3:
        obj->unk_114 = *value;
        break;
    case 1:
        obj->unk_120 = *value;
        break;
    case 2:
        obj->unk_124 = *value;
        break;
    case 4:
        obj->unk_118 = *value;
        break;
    case 0:
        obj->unk_11C = *value;
        break;
    default:
        break;
    }
    return 1;
}
/* fzgx:end fn_1_15B698 */
