#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/avline.h"

extern u32 lbl_801A6410;
extern u32 fn_1_45D0(u32, u32, unsigned char *, u32);
extern void fn_1_46B4(u32, u32, void *, u32);
extern u8 lbl_1_data_1D62C[148];
extern void fn_1_9F870(void);
extern void fn_1_58158(void);

/* fzgx:begin fn_1_58114 */
void fn_1_58114(void) {
    lbl_1_bss_6C840 = fn_1_45D0(lbl_801A6410, 0x6590, lbl_1_data_1C68C, 0x39f);
}
/* fzgx:end fn_1_58114 */

/* fzgx:begin fn_1_58158 */
// fn_1_58158: loads global values and calls fn_1_46B4.
void fn_1_58158(void) {
    u32 v1 = lbl_801A6410;
    u32 v2 = lbl_1_bss_6C840;
    fn_1_46B4(v1, v2, &lbl_1_data_1C68C, 0x3a6);
}
/* fzgx:end fn_1_58158 */

/* fzgx:begin fn_1_5819C */
void fn_1_5819C(void) {
    lbl_1_bss_6C844 = 0;
}
/* fzgx:end fn_1_5819C */

/* fzgx:begin fn_1_584AC */
// fn_1_584AC: linear congruential generator.
u32 fn_1_584AC(void) {
    u32 state = lbl_1_data_1D628;
    u32 next = state * 0x41c64e6du + 0x3039u;
    lbl_1_data_1D628 = next;
    return (next >> 16) & 0x7FFFu;
}
/* fzgx:end fn_1_584AC */

/* fzgx:begin fn_1_58694 noprologue */
#include "types.h"

typedef struct AvlineVec3 {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} AvlineVec3;

typedef struct AvlineEntry {
    s8 unk_00;
    u8 _pad01[0x0b];
    s16 unk_0c;
    u8 _pad0e[0x02];
    s32 unk_10;
    u8 _pad14[0x28];
    AvlineVec3 unk_3c;
    u8 _pad48[0x18];
    AvlineVec3 unk_60;
    u8 _pad6c[0x7c];
} AvlineEntry;

typedef struct AvlineState {
    AvlineEntry *unk_00;
    AvlineEntry *unk_04;
    u8 _pad08[0x0c];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1c;
    s32 unk_20;
} AvlineState;

typedef void (*AvlineHandler)(AvlineEntry *);

extern AvlineState lbl_1_bss_6C848;
extern AvlineHandler lbl_1_data_1D514[];
extern AvlineHandler lbl_1_data_1D2EC[];
extern s16 fn_1_3F0C8(void);
extern void fn_1_3BDC(s32);
extern void fn_1_3C18(s32);

void fn_1_58694(void) {
    AvlineState *state = &lbl_1_bss_6C848;
    s32 count;
    AvlineEntry *entry;

    if (fn_1_3F0C8() != 0x28) {
        entry = state->unk_00;
        state->unk_14 = 0;
        state->unk_18 = 0;
        state->unk_1c = 0;
        state->unk_20 = 0;
        fn_1_3BDC(9);
        for (count = 0xbe; count > 0; count--) {
            if (entry->unk_00 != 0) {
                entry->unk_10 -= 1;
                if (entry->unk_10 == 0 || entry->unk_00 == 3) {
                    lbl_1_data_1D514[entry->unk_0c](entry);
                    entry->unk_00 = 0;
                } else {
                    entry->unk_60 = entry->unk_3c;
                    lbl_1_data_1D2EC[entry->unk_0c](entry);
                }
            }
            entry++;
        }
        entry = state->unk_04;
        for (count = 0xc8; count > 0; count--) {
            if (entry->unk_00 != 0) {
                entry->unk_10 -= 1;
                if (entry->unk_10 == 0 || entry->unk_00 == 3) {
                    lbl_1_data_1D514[entry->unk_0c](entry);
                    entry->unk_00 = 0;
                } else {
                    entry->unk_60 = entry->unk_3c;
                    lbl_1_data_1D2EC[entry->unk_0c](entry);
                }
            }
            entry++;
        }
        fn_1_3C18(9);
    }
}
/* fzgx:end fn_1_58694 */

/* fzgx:begin fn_1_58854 */
typedef struct {
    s8 unk_0;
    u8 pad_1[0xb];
    s16 unk_C;
} AvlineObj;

typedef void (*AvlineCallback)(void *);

void fn_1_58854(void) {
    s32 count;
    AvlineObj *obj;
    s32 index;
    AvlineCallback callback;

    fn_1_9F870();
    fn_1_58158();

    obj = *(AvlineObj **)&lbl_1_bss_6C848;
    count = 0xbe;
    index = 0;
    while (count > 0) {
        if (obj->unk_0 != 0) {
            callback = ((AvlineCallback *)lbl_1_data_1D514)[obj->unk_C];
            callback(obj);
            obj->unk_0 = index;
        }
        count--;
        obj = (AvlineObj *)((u8 *)obj + 0xe8);
    }

    obj = (AvlineObj *)lbl_1_bss_6C84C;
    count = 0xc8;
    index = 0;
    while (count > 0) {
        if (obj->unk_0 != 0) {
            callback = ((AvlineCallback *)lbl_1_data_1D514)[obj->unk_C];
            callback(obj);
            obj->unk_0 = index;
        }
        count--;
        obj = (AvlineObj *)((u8 *)obj + 0xe8);
    }

    fn_1_46B4(lbl_801A6410, *(u32 *)&lbl_1_bss_6C848,
              lbl_1_data_1D62C, 0x156);
    fn_1_46B4(lbl_801A6410, *(u32 *)&lbl_1_bss_6C84C,
              lbl_1_data_1D62C, 0x157);

    *(u32 *)&lbl_1_bss_6C848 = 0;
    lbl_1_bss_6C84C = 0;
}
/* fzgx:end fn_1_58854 */

/* fzgx:begin fn_1_591A0 */
typedef struct {
    s8 unk_0;
    u8 pad_1[0x7];
    u32 unk_8;
    s16 unk_C;
    u8 pad_E[0xDA];
} Fn591A0Obj;

void fn_1_591A0(s32 id) {
    {
        Fn591A0Obj *obj;
        void (**table)(void *);
        s32 count;
        s32 zero;

        obj = *(Fn591A0Obj **)&lbl_1_bss_6C848;
        table = (void (**)(void *))lbl_1_data_1D514;
        zero = 0;
        for (count = 0xbe; count > 0; count--) {
            if (obj->unk_0 && obj->unk_C == id) {
                table[obj->unk_C](obj);
                obj->unk_8 |= (u32)0x8000 << 16;
                obj->unk_0 = zero;
            }
            obj++;
        }
    }
    {
        s32 count;
        Fn591A0Obj *obj;
        void (**table)(void *);
        s32 zero;

        obj = (Fn591A0Obj *)lbl_1_bss_6C84C;
        table = (void (**)(void *))lbl_1_data_1D514;
        zero = 0;
        for (count = 0xc8; count > 0; count--) {
            if (obj->unk_0 && obj->unk_C == id) {
                table[obj->unk_C](obj);
                obj->unk_8 |= (u32)0x8000 << 16;
                obj->unk_0 = zero;
            }
            obj++;
        }
    }
}
/* fzgx:end fn_1_591A0 */
