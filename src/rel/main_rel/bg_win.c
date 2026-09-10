#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/bg_win.h"

extern u32 lbl_1_bss_8FD60[2];
extern int fn_1_15BCDC(void *);
extern void fn_1_4060(void);

extern u32 lbl_1_bss_8FE80[8];

extern void *fn_1_435C(void *);
extern void fn_1_15E220(u8 *value);
extern void fn_1_3F8C(void *, void *, u8 *, s32);
extern u32 lbl_1_bss_8FEA0;
extern u8 lbl_1_bss_8FE7C;

/* fzgx:begin fn_1_15BE38 */
typedef struct {
    u32 count;
    void **items;
} ItemList;

u32 fn_1_15BE38(void) {
    u32 offset;
    u32 index;

    offset = 0;
    index = 0;
    while (index < (*(ItemList **)&lbl_1_bss_8FD60)->count) {
        if (fn_1_15BCDC((*(ItemList **)&lbl_1_bss_8FD60)->items[offset >> 2]) != 0) {
            return index & 0xffff;
        }
        offset += 4;
        index++;
    }
    return 0xffff;
}
/* fzgx:end fn_1_15BE38 */

/* fzgx:begin fn_1_15C35C */
s32 fn_1_15C35C(s32 a, s32 b, s32 c, s32 d) {
    return a * b - c + d;
}
/* fzgx:end fn_1_15C35C */

/* fzgx:begin fn_1_15E1D0 noprologue */
#include "types.h"

struct fn_1_15E1D0_lbl_1_bss_8FDA8_0_E52 {
    u8 pad_0[0x30];
    f32 unk_30;
};
struct fn_1_15E1D0_lbl_1_bss_8FDA8 {
    struct fn_1_15E1D0_lbl_1_bss_8FDA8_0_E52 unk_0[1];
};

extern struct fn_1_15E1D0_lbl_1_bss_8FDA8 lbl_1_bss_8FDA8;

f32 fn_1_15E1D0(u32 arg0) {
    return lbl_1_bss_8FDA8.unk_0[arg0].unk_30;
}
/* fzgx:end fn_1_15E1D0 */

/* fzgx:begin fn_1_15E1E8 */
void fn_1_15E1E8(u8 *value) {
    u8 state = *value;

    if (state == 0) {
        fn_1_4060();
    } else {
        *value = state - 1;
    }
}
/* fzgx:end fn_1_15E1E8 */

/* fzgx:begin fn_1_15E220 */
void fn_1_15E220(u8 *value) {
    u8 state = *value;

    if (state == 0) {
        fn_1_4060();
    } else if (state != 0xff) {
        *value = state - 1;
    }
}
/* fzgx:end fn_1_15E220 */

/* fzgx:begin fn_1_15E260 */
// Marks the indexed background-window entry as active.
void fn_1_15E260(s32 index) {
    (&lbl_1_bss_8FDA8.unk_0)[index * 0x34] |= 4;
}
/* fzgx:end fn_1_15E260 */

/* fzgx:begin fn_1_15E330 */
extern void *fn_1_435C(void *arg);
extern void fn_1_15E1E8(u8 *arg);
extern void fn_1_3F8C(void *arg0, void *arg1, u8 *arg2, s32 arg3);

void fn_1_15E330(s32 index, u32 value, void *arg) {
    if (lbl_1_bss_3C30.unk_13F4 - (&lbl_1_bss_8FDA8.unk_8)[index * 0x34] < 4) {
        void *result;

        (&lbl_1_bss_8FDA8.unk_0)[index * 0x34] |= 8;
        (&lbl_1_bss_8FDA8.unk_C)[index * 13] = value;
        result = fn_1_435C(arg);
        fn_1_3F8C(lbl_1_data_4C980, fn_1_15E1E8,
                  &(&lbl_1_bss_8FDA8.unk_9)[index * 0x34], 13);
        (&lbl_1_bss_8FDA8.unk_9)[index * 0x34] = 0x3c;
        fn_1_435C(result);
    }
}
/* fzgx:end fn_1_15E330 */

/* fzgx:begin fn_1_15E3E0 */
// Records the selected window index and updates its value when the index is valid.
void fn_1_15E3E0(s32 index, u32 value) {
    s32 slot = (lbl_1_bss_3C30.unk_13F4 - 1) % 4;

    lbl_1_bss_8FE80[slot] = index;
    if (index != -1) {
        (&lbl_1_bss_8FDA8.unk_C)[index * 13] = value;
    }
}
/* fzgx:end fn_1_15E3E0 */

/* fzgx:begin fn_1_15E434 */
void fn_1_15E434(u32 value) {
    lbl_1_bss_8FE7C = 1;
    lbl_1_bss_8FEA0 = value;
}
/* fzgx:end fn_1_15E434 */

/* fzgx:begin fn_1_15E540 */
// Initializes a background-window entry once, then marks it ready for reuse.
void fn_1_15E540(s32 index, void *arg) {
    if (!((&lbl_1_bss_8FDA8.unk_0)[index * 0x34] & 1)) {
        void *value = fn_1_435C(arg);

        fn_1_3F8C(lbl_1_data_4C994, fn_1_15E220,
                  &lbl_1_bss_8FDA8.unk_1 + index * 0x34, 13);
        (&lbl_1_bss_8FDA8.unk_1)[index * 0x34] = 0xff;
        fn_1_435C(value);
        (&lbl_1_bss_8FDA8.unk_0)[index * 0x34] |= 1;
    }
}
/* fzgx:end fn_1_15E540 */

/* fzgx:begin fn_1_15E5E4 */
extern void *fn_1_435C(void *);
extern void fn_1_15E220(u8 *value);
extern void fn_1_3F8C(void *, void *, u8 *, s32);

// Initializes a background-window entry once, then marks it ready for reuse.
void fn_1_15E5E4(s32 index, void *arg) {
    Obj_1_bss_8FDA8 *obj;
    s32 offset = index * 0x34;

    obj = (Obj_1_bss_8FDA8 *)((u8 *)&lbl_1_bss_8FDA8 + offset);

    if (!(obj->unk_0 & 2)) {
        void *value = fn_1_435C(arg);

        fn_1_3F8C(lbl_1_data_4C994, fn_1_15E220, &obj->unk_2, 13);
        (&lbl_1_bss_8FDA8.unk_2)[offset] = 0xff;
        fn_1_435C(value);
        obj->unk_0 |= 2;
    }
}
/* fzgx:end fn_1_15E5E4 */

/* fzgx:begin fn_1_15F618 */
void *fn_1_15F618(s32 index) {
    return (u8 *)&lbl_1_bss_8FDA8 + index * 0x34;
}
/* fzgx:end fn_1_15F618 */
