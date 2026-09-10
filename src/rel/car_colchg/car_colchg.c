#include "types.h"
#include "rel/car_colchg/globals.h"

extern void colchg_menu_disp(void);
void fn_1_426C(s16);
extern void colchg_ezsel_disp(void);
extern void colchg_save_disp(void);
extern u16 lbl_1_bss_968;
extern struct Struct_lbl_1_bss_D58 lbl_1_bss_D58;
s32 fn_1_4C10(void);
void fn_1_A8EB0(s32, s32);
s32 fn_1_7F49C(s16, s32, void *);
void fn_1_A8DD4(const char *, ...);
void fn_1_80058(s8, struct CarColchgEntry *);
void fn_1_80C18(u32, struct CarColchgEntry *, s32);
void fn_1_426C(s16);
s32 fn_1_4C10(void);
void fn_1_A8EB0(s32, s32);
s32 fn_1_7F49C(s16, s32, void *);
void fn_1_A8DD4(const char *, ...);
void fn_1_80058(s8, struct CarColchgEntry *);
void fn_1_80C18(u32, struct CarColchgEntry *, s32);
extern s16 lbl_1_bss_962;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;
extern struct Struct_lbl_1_bss_970 lbl_1_bss_970;
extern u16 lbl_1_bss_96A;
extern struct Entry *lbl_1_data_1FB6C[];
extern u32 lbl_801A6410;
void fn_1_7FA04(u32);
void fn_1_8D168(u32);
void fn_1_435C(u32);
void fn_1_41A8(void);
void fn_1_46B4(u32, u32, void *, s32);
void fn_1_6400(void);
u16 fn_1_3F8C(char *, void (*)(void), s32, s32);
void fn_1_4A00(s32, s32, u32);
extern void fn_9_1BCC(void);
extern void fn_9_1AC4(void);
extern u32 lbl_801A66A0;

/* fzgx:begin _epilog */
struct CarColchgState {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u8 entries[200];
};

/* Tear down the color-change state and release its two menu entries. */
void _epilog(void) {
    struct CarColchgState *state = (struct CarColchgState *)&lbl_9_bss_0;
    u8 *entry;
    s16 i;

    fn_1_7FA04(state->unk4);
    entry = state->entries;
    for (i = 0; i < 2; i++) {
        fn_1_8D168((u32)entry);
        entry += 100;
    }
    fn_1_435C(state->unkC);
    fn_1_41A8();
    fn_1_435C(state->unk10);
    fn_1_41A8();
    fn_1_46B4(lbl_801A6410, state->unk0, lbl_9_data_4, 0xDA);
    fn_1_6400();
    fn_1_46B4(lbl_801A6410, state->unk8, lbl_9_data_4, 0xDC);
}
/* fzgx:end _epilog */

/* fzgx:begin colchg_menu_init */
void colchg_menu_init(void) {
    // Set up the menu callback and activate the initial collision-color selection.
    fn_1_435C(lbl_9_bss_10);
    lbl_9_bss_DC = fn_1_3F8C(lbl_9_data_2C, colchg_menu_disp, 0, 8);
    fn_1_4A00(1, 15, lbl_9_bss_10);
}
/* fzgx:end colchg_menu_init */

/* fzgx:begin fn_9_454 */
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef int BOOL;
typedef unsigned long size_t;
struct Struct_lbl_1_bss_D58
{
  u8 pad0[8];
  volatile u16 unk8;  // volatile: decomp-permuter found retail keeps this access order; a revise pass should express it without volatile
  u8 padA[6];
  volatile u16 unk10;  // volatile: decomp-permuter found retail keeps this access order; a revise pass should express it without volatile
  volatile u16 unk12;  // volatile: decomp-permuter found retail keeps this access order; a revise pass should express it without volatile
};
struct Struct_lbl_1_bss_970
{
  u8 pad0[4];
  u8 unk4;
};
void fn_9_454(void)
{
  s32 value;
  s8 delta;
  if (fn_1_4C10() == 0)
  {
    delta = 0;
    if (((lbl_1_bss_D58.unk10 >> 3) & 1) || ((long) ((lbl_1_bss_D58.unk12 >> 3) & 1)))
    {
      delta = -1;
    }
    if (((lbl_1_bss_D58.unk10 >> 2) & 1) || ((lbl_1_bss_D58.unk12 >> 2) & 1))
    {
      delta++;
    }
    if (1)
    {
      value = lbl_1_bss_970.unk4 + delta;
      value = (lbl_1_bss_970.unk4 = (value > 0x73) ? (0x73) : ((value < 0x73) ? (0x73) : (value)));
      if ((lbl_1_bss_D58.unk8 >> 8) & 1)
      {
        lbl_1_bss_96A = value;
      }
      if ((lbl_1_bss_D58.unk8 >> 9) & 1)
      {
        lbl_1_bss_96A = 0x75;
      }
    }
  }
}
/* fzgx:end fn_9_454 */

/* fzgx:begin fn_9_534 */
// Initialize the car color-change state and apply the current selection.
void fn_9_534(void) {
    fn_1_435C(lbl_9_bss_10);
    fn_1_426C(lbl_9_bss_DC);
}
/* fzgx:end fn_9_534 */

/* fzgx:begin colchg_selcar_init noprologue */
#include "types.h"

extern struct colchg_selcar_init_lbl_9_bss_0 lbl_9_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 fn_9_1BCC(void);
extern u32 lbl_9_data_40;
extern void colchg_selcar_disp(void);

struct colchg_selcar_init_lbl_9_bss_0 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x8];
    u32 unk_10;
    u8 pad_14[0xC8];
    u16 unk_DC;
};

void colchg_selcar_init(void) {
    struct colchg_selcar_init_lbl_9_bss_0 *p_lbl_9_bss_0;
    u32 t2;
    p_lbl_9_bss_0 = (struct colchg_selcar_init_lbl_9_bss_0 *)&lbl_9_bss_0;
    fn_9_1BCC();
    fn_1_435C(p_lbl_9_bss_0->unk_10);
    t2 = fn_1_3F8C((u32)&lbl_9_data_40, (u32)colchg_selcar_disp, p_lbl_9_bss_0->unk_4, 8);
    p_lbl_9_bss_0->unk_DC = t2;
    fn_1_4A00(1, 15, p_lbl_9_bss_0->unk_10);
}
/* fzgx:end colchg_selcar_init */

/* fzgx:begin fn_9_6F0 */
// Apply the current car color-change configuration.
void fn_9_6F0(void) {
    fn_1_435C(lbl_9_bss_10);
    fn_1_426C(lbl_9_bss_DC);
}
/* fzgx:end fn_9_6F0 */

/* fzgx:begin fn_9_7DC */
#include "types.h"
#include "rel/car_colchg/globals.h"

struct InputState {
    u8 pad[8];
    u16 buttons;
    u8 pad2[6];
    u16 buttons2;
    u16 buttons3;
};

struct Entry {
    s16 id;
    s16 pad;
    s32 unk;
    void *data;
};

struct ColorState {
    s16 unk0;
    s16 selected_id;
    s16 selected;
};

void fn_9_7DC(void) {
    struct Entry *entries;
    s8 change;
    s16 count;
    s32 index;

    entries = lbl_1_data_1FB6C[((struct ColorState *)lbl_9_bss_8)->unk0];
    if (fn_1_4C10() == 0) {
        if ((((struct InputState *)&lbl_1_bss_D58)->buttons >> 8) & 1) {
            lbl_1_bss_96A = 0x77;
        }
        if ((((struct InputState *)&lbl_1_bss_D58)->buttons >> 9) & 1) {
            lbl_1_bss_96A = 0x73;
        }

        change = 0;
        // Direct polling preserves the button-edge reads.
        if ((((volatile struct InputState *)&lbl_1_bss_D58)->buttons2 & 1) ||
            // Direct polling preserves the second button-edge source.
            (((volatile struct InputState *)&lbl_1_bss_D58)->buttons3 & 1)) {
            change = -1;
        }
        // Direct polling preserves the button-edge reads.
        if (((((volatile struct InputState *)&lbl_1_bss_D58)->buttons2 >> 1) & 1) ||
            // Direct polling preserves the second button-edge source.
            ((((volatile struct InputState *)&lbl_1_bss_D58)->buttons3 >> 1) & 1)) {
            change++;
        }

        if (change != 0) {
            count = 0;
            while (lbl_1_data_1FB6C[((struct ColorState *)lbl_9_bss_8)->unk0][count].id != -1) {
                count++;
            }

            entries[((struct ColorState *)lbl_9_bss_8)->selected].data =
                (void *)lbl_9_bss_E0;
            index = ((struct ColorState *)lbl_9_bss_8)->selected + change;
            if (index > count - 1) {
                index = 0;
            } else if (index < 0) {
                index = count - 1;
            }
            ((struct ColorState *)lbl_9_bss_8)->selected = index;
            if (entries[((struct ColorState *)lbl_9_bss_8)->selected].id == -1) {
                index = ((struct ColorState *)lbl_9_bss_8)->selected - change;
                if (index > count - 1) {
                    index = 0;
                } else if (index < 0) {
                    index = count - 1;
                }
                ((struct ColorState *)lbl_9_bss_8)->selected = index;
            }
            ((struct ColorState *)lbl_9_bss_8)->selected_id =
                entries[((struct ColorState *)lbl_9_bss_8)->selected].id;
            lbl_9_bss_E0 =
                (u32)entries[((struct ColorState *)lbl_9_bss_8)->selected].data;
        }

        if (lbl_801A66A0 & 1) {
            entries[((struct ColorState *)lbl_9_bss_8)->selected].data = 0;
        } else {
            entries[((struct ColorState *)lbl_9_bss_8)->selected].data = (void *)-1;
        }
    }
}
/* fzgx:end fn_9_7DC */

/* fzgx:begin fn_9_A18 */
struct Entry {
    u32 unk0;
    u32 unk4;
    u32 unk8;
};

struct CarColchgState {
    u8 pad0[8];
    s16 *selection;
    u32 padC;
    u32 value10;
    u8 pad14[0xC8];
    s16 valueDC;
    u32 valueE0;
};

void fn_9_A18(void) {
    struct CarColchgState *state = (struct CarColchgState *)&lbl_9_bss_0;
    struct Entry *entry;

    entry = lbl_1_data_1FB6C[*state->selection];
    fn_1_435C(state->value10);
    fn_1_426C(state->valueDC);
    entry[state->selection[2]].unk8 = state->valueE0;
}
/* fzgx:end fn_9_A18 */

/* fzgx:begin colchg_chgcol_init noprologue */
#include "types.h"

extern struct colchg_chgcol_init_lbl_9_bss_0 lbl_9_bss_0;
extern u32 fn_1_3F8C(u32, u32, u32, u32);
extern u32 fn_1_435C(u32);
extern u32 fn_1_4A00(u32, u32, u32);
extern u32 lbl_9_data_68;
extern void colchg_chgcol_disp(void);

struct colchg_chgcol_init_lbl_9_bss_0 {
    u8 pad_0[0x4];
    u32 unk_4;
    u8 pad_8[0x8];
    u32 unk_10;
    u8 pad_14[0xC8];
    u16 unk_DC;
};

void colchg_chgcol_init(void) {
    struct colchg_chgcol_init_lbl_9_bss_0 *p_lbl_9_bss_0;
    u32 t1;
    p_lbl_9_bss_0 = (struct colchg_chgcol_init_lbl_9_bss_0 *)&lbl_9_bss_0;
    fn_1_435C(p_lbl_9_bss_0->unk_10);
    t1 = fn_1_3F8C((u32)&lbl_9_data_68, (u32)colchg_chgcol_disp, p_lbl_9_bss_0->unk_4, 8);
    p_lbl_9_bss_0->unk_DC = t1;
    fn_1_4A00(1, 15, p_lbl_9_bss_0->unk_10);
}
/* fzgx:end colchg_chgcol_init */

/* fzgx:begin fn_9_DC0 */
// Refresh the collision-change state from the current global settings.
void fn_9_DC0(void) {
    fn_1_435C(lbl_9_bss_10);
    fn_1_426C(lbl_9_bss_DC);
}
/* fzgx:end fn_9_DC0 */

/* fzgx:begin colchg_ezsel_init */
// Register the easy-selection display callback and retain its menu handle.
void colchg_ezsel_init(void) {
    fn_1_435C(lbl_9_bss_10);
    lbl_9_bss_DC = fn_1_3F8C(lbl_9_data_9C, colchg_ezsel_disp, 0, 8);
}
/* fzgx:end colchg_ezsel_init */

/* fzgx:begin fn_9_E4C noprologue */
#include "types.h"
#include "rel/car_colchg/globals.h"

struct ColchgState {
    u8 pad[8];
    u16 flags;
    u8 pad_a[6];
    volatile u16 input_a; // Input state may be updated between reads.
    volatile u16 input_b; // Input state may be updated between reads.
};

extern struct ColchgState lbl_1_bss_D58;
extern u16 lbl_1_bss_96A;
s32 fn_1_4C10(void);

void fn_9_E4C(void) {
    struct ColchgState *state;
    s8 change;

    if (fn_1_4C10() == 0) {
        state = &lbl_1_bss_D58;
        if ((state->flags >> 9) & 1) {
            lbl_1_bss_96A = 0x72;
        }
        change = 0;
        if ((lbl_1_bss_D58.input_a & 1) || (lbl_1_bss_D58.input_b & 1)) {
            change = -1;
        }
        if (((lbl_1_bss_D58.input_a >> 1) & 1) ||
            ((lbl_1_bss_D58.input_b >> 1) & 1)) {
            change++;
        }
        if (change != 0) {
            s32 result;
            s32 value;
            value = *(s16 *)lbl_9_bss_8 + change;
            if (value > 40) {
                value = 0;
            } else {
                value = value < 0 ? 40 : value;
            }
            *(s16 *)lbl_9_bss_8 = value;
        }
        if ((state->flags >> 8) & 1) {
            lbl_1_bss_96A = 0x76;
        }
    }
}
/* fzgx:end fn_9_E4C */

/* fzgx:begin fn_9_F38 */
// Initialize the color-change subsystem and apply its current configuration.
void fn_9_F38(void) {
    fn_1_435C(lbl_9_bss_10);
    fn_1_426C(lbl_9_bss_DC);
}
/* fzgx:end fn_9_F38 */

/* fzgx:begin colchg_save_init */
// Register the save-screen callback and reset the color-change save state.
void colchg_save_init(void) {
    fn_1_435C(lbl_9_bss_10);
    lbl_9_bss_DC = fn_1_3F8C(lbl_9_data_B0, colchg_save_disp, 0, 8);
    lbl_1_bss_968 = 10;
}
/* fzgx:end colchg_save_init */

/* fzgx:begin fn_9_FD0 */
struct Struct_lbl_1_bss_D58 {
    u8 pad[8];
    u16 unk8;
};

void fn_9_FD0(void) {
    if (fn_1_4C10() == 0) {
        if ((lbl_1_bss_D58.unk8 >> 9) & 1) {
            lbl_1_bss_968 = 0xA;
        }
    }
}
/* fzgx:end fn_9_FD0 */

/* fzgx:begin fn_9_1018 */
// Initializes the color-change subsystem from its configured state.
void fn_9_1018(void) {
    fn_1_435C(lbl_9_bss_10);
    fn_1_426C(lbl_9_bss_DC);
}
/* fzgx:end fn_9_1018 */

/* fzgx:begin fn_9_1054 */
// Sets up the color-change display callback and selects the default palette.
void fn_9_1054(void) {
    u16 display_mode;

    fn_9_1BCC();
    fn_1_435C(lbl_9_bss_10);
    display_mode = fn_1_3F8C((char *)lbl_9_data_C4, fn_9_1AC4, 0, 8);
    lbl_9_bss_DC = display_mode;
    fn_1_4A00(1, 15, lbl_9_bss_10);
}
/* fzgx:end fn_9_1054 */

/* fzgx:begin fn_9_10BC */
typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef int BOOL;
typedef unsigned long size_t;
struct Struct_lbl_1_bss_D58
{
  u8 pad[8];
  u16 unk8;
};
inline u16 *inline_fn(u16 *arg0)
{
  return arg0;
}

void fn_9_10BC(void)
{
  u16 value;
  u16 *new_var;
  u16 *p;
  if (fn_1_4C10() == 0)
  {
    p = &lbl_1_bss_96A;
    value = 0x73;
    *p = value;
    new_var = inline_fn(p);
    if ((lbl_1_bss_D58.unk8 >> 9) & 1)
    {
      *new_var = 0x72;
    }
    if (((lbl_1_bss_D58.unk8 >> 8) & 1) != 0U)
    {
      lbl_1_bss_96A = 0x76;
    }
  }
}
/* fzgx:end fn_9_10BC */

/* fzgx:begin fn_9_1124 */
void fn_9_1124(void)
{
    // Apply the active color-change state before refreshing the selection display.
    fn_1_435C(lbl_9_bss_10);
    fn_1_426C(lbl_9_bss_DC);
}
/* fzgx:end fn_9_1124 */

/* fzgx:begin colchg_ezsel_disp */
void colchg_ezsel_disp(void) {
    u8 buffer[0x20];
    s32 value;

    fn_1_A8EB0(0x14, 0x14);
    value = fn_1_7F49C(*(s16 *)lbl_9_bss_8, 0, buffer);
    fn_1_A8DD4(lbl_9_data_18C, *(s16 *)lbl_9_bss_8, 0x29, value);
}
/* fzgx:end colchg_ezsel_disp */

/* fzgx:begin colchg_save_disp */
void colchg_save_disp(void) {
    fn_1_A8EB0(0x14, 0x14);
    fn_1_A8DD4(lbl_9_data_19C);
}
/* fzgx:end colchg_save_disp */

/* fzgx:begin fn_9_1AC4 */
void fn_9_1AC4(void) {
    fn_1_A8EB0(0x14, 0xa);
    fn_1_A8DD4(lbl_9_data_1A4);
}
/* fzgx:end fn_9_1AC4 */

/* fzgx:begin fn_9_1AFC */
extern const f32 lbl_9_rodata_0;

extern void lbl_8006DCA4(void);
extern void lbl_8006E1D8(void *, f32, f32, f32);
extern void fn_1_7BCCC(void *);
extern void fn_80035680(void *, f32, f32, f32);
extern void fn_80035690(void *, f32, f32, f32);
extern void fn_80035420(void *, f32, s32);
extern void fn_800356AC(void *, void *);
extern void GXInitLightDistAttn(void *, s32, f32, f32);
extern void fn_1_7BB80(void *, s32);
extern void fn_1_7BD6C(s32);
extern void fn_80074CF4(f32, f32, f32);

struct Fn_9_1AFCVec3 {
    f32 x;
    f32 y;
    f32 z;
};

struct Fn_9_1AFCBigVec3 {
    f32 x;
    f32 y;
    f32 z;
    u8 pad[0x34];
};

void fn_9_1AFC(void) {
    u32 value;
    struct Fn_9_1AFCBigVec3 b;
    struct Fn_9_1AFCVec3 a;
    const u8 *pool;
    u8 pad[0x30];

    pool = (const u8 *)&lbl_9_rodata_0;
    lbl_8006DCA4();
    lbl_8006E1D8(&a, *(const f32 *)(pool + 0x54), *(const f32 *)(pool + 0x54), *(const f32 *)(pool + 0x54));
    fn_1_7BCCC(&a);
    fn_80035680(&b, a.x, a.y, a.z);
    fn_80035690(&b, a.x, a.y, a.z);
    fn_80035420(&b, *(const f32 *)pool, 0);
    value = *(const u32 *)(pool + 0x50);
    fn_800356AC(&b, &value);
    GXInitLightDistAttn(&b, 0, *(const f32 *)pool, *(const f32 *)pool);
    fn_1_7BB80(&b, 1);
    fn_1_7BD6C(1);
    fn_80074CF4(*(const f32 *)(pool + 0x58), *(const f32 *)(pool + 0x58), *(const f32 *)(pool + 0x58));
}
/* fzgx:end fn_9_1AFC */

/* fzgx:begin fn_9_1BCC */
struct CarColchgEntry {
    s16 unk0;
    u16 unk2;
    u32 unk4;
    u8 pad8[24];
};

void fn_9_1BCC(void) {
    struct CarColchgEntry entries[0x29];
    s8 i;

    for (i = 0; i < 0x29; i++) {
        fn_1_80058(i, &entries[i]);
        entries[i].unk4 = 1;
        entries[i].unk0 = i;
    }
    fn_1_80C18(lbl_9_bss_4, entries, 0x29);
}
/* fzgx:end fn_9_1BCC */

/* fzgx:begin fn_9_1C54 */
struct CarColchgEntry {
    u8 pad[0x20];
    void (*func)(void);
    u32 value24;
    u32 value28;
};

// Select the color-change entry for the current car and invoke its handler.
void fn_9_1C54(void) {
    struct CarColchgEntry *entry;
    s16 index;

    entry = (struct CarColchgEntry *)&lbl_9_data_1B8;
    index = lbl_1_bss_962;
    entry += index - 0x71;

    lbl_1_bss_71688 = entry->value24;
    lbl_1_bss_7168C = entry->value28;
    entry->func();
}
/* fzgx:end fn_9_1C54 */
