#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/background.h"

extern u32 lbl_1_bss_6EA78;
extern u32 lbl_1_bss_6EA7C;
extern u32 lbl_801A6410;
extern void fn_1_46B4(u32, u32, void *, s32);
extern const f32 lbl_1_rodata_41FC;
extern u8 fn_1_86624(void);
extern void *fn_1_14F04(void);
extern f32 lbl_1_rodata_4244[7];
extern void fn_1_17920(s32, s32, f32);
extern void fn_1_85C58(s32, f32);
extern void lbl_8006DB74(void *);
extern void fn_1_9DDA8(u32, u32, u32);
extern void fn_1_9DFB8(u32, u32, u32, u32);
extern void GXPeekZ(u32, u32, void *);
extern void fn_80034200(u32);
extern void fn_8003432C(u32, u32, u32 *);

/* fzgx:begin fn_1_9D77C */
typedef struct {
    u32 flags;
    u8 _pad[0x34];
    void *link;
    u8 _tail[4];
} Fn1_9D77C_Item;

typedef struct {
    u8 _pad[4];
    u32 value;
} Fn1_9D77C_Link;

void fn_1_9D77C(Fn1_9D77C_Item *items, s32 count) {
    s32 i;
    u32 *first;
    u32 *second;

    first = (u32 *)lbl_1_bss_6EA78;
    second = (u32 *)lbl_1_bss_6EA7C;

    for (i = 0; i < 5; i++) {
        if (lbl_1_bss_6EA78 != 0 && first != 0 && *first != 0) {
            fn_1_46B4(lbl_801A6410, *first, lbl_1_data_2CB60, 0x922);
            *first = 0;
        }
        if (lbl_1_bss_6EA7C != 0 && second != 0 && *second != 0) {
            fn_1_46B4(lbl_801A6410, *second, lbl_1_data_2CB60, 0x923);
            *second = 0;
        }
        first++;
        second++;
    }

    i = 0;
    while (i < count) {
        if ((items->flags & 0x1000) != 0 &&
            items->link != 0 &&
            ((Fn1_9D77C_Link *)items->link)->value != 0) {
            fn_1_46B4(lbl_801A6410,
                       ((Fn1_9D77C_Link *)items->link)->value,
                       lbl_1_data_2CB60, 0x92b);
            ((Fn1_9D77C_Link *)items->link)->value = 0;
        }
        i++;
        items++;
    }

    if (lbl_1_bss_6EA78 != 0) {
        fn_1_46B4(lbl_801A6410, lbl_1_bss_6EA78, lbl_1_data_2CB60, 0x92e);
        lbl_1_bss_6EA78 = 0;
    }
    if (lbl_1_bss_6EA7C != 0) {
        fn_1_46B4(lbl_801A6410, lbl_1_bss_6EA7C, lbl_1_data_2CB60, 0x92f);
        lbl_1_bss_6EA7C = 0;
    }
}
/* fzgx:end fn_1_9D77C */

/* fzgx:begin fn_1_9D93C */
s32 fn_1_9D93C(s32 arg0, u32 *arg1) {
    if (arg0 == 0) {
        lbl_1_data_2A7E0.unk_80 = *arg1;
    } else {
        lbl_1_data_2A7E0.unk_7C = *arg1;
    }
    {
        s32 result;
        result = 0;
        if (lbl_1_data_2A7E0.unk_80 == 0 ||
            lbl_1_data_2A7E0.unk_7C == 0) {
            result = 1;
        }
        return result;
    }
}
/* fzgx:end fn_1_9D93C */

/* fzgx:begin fn_1_9D9E4 */
typedef struct {
    u8 pad[0x468];
    f32 value;
} Fn14F04Result;

void fn_1_9D9E4(void) {
    f32 value;
    s32 offset;
    s32 i;
    s32 count;
    Fn14F04Result *result;

    value = lbl_1_rodata_41FC;
    lbl_1_data_2A7E0.unk_74 = 1;
    if (*(s16 *)&lbl_1_bss_960 == 9) {
        lbl_1_data_2A7E0.unk_70 = fn_1_86624();
    } else {
        lbl_1_data_2A7E0.unk_70 = 0x1e;
    }

    if (lbl_1_bss_3BE0 != 0) {
        result = (Fn14F04Result *)fn_1_14F04();
        count = lbl_1_bss_3BE0->unk_8;
        if (count > 0) {
            count--;
        } else {
            count = 0;
        }
        fn_1_17920(count, 0, lbl_1_rodata_4244[0]);
        value = result->value;
    }

    i = 0;
    offset = 0;
    while (i < (s8)lbl_1_data_2A7E0.unk_70) {
        fn_1_85C58(i, value);
        lbl_8006DB74((u8 *)lbl_1_data_2A7E0.unk_78 + offset);
        offset += 0x30;
        i++;
    }
}
/* fzgx:end fn_1_9D9E4 */

/* fzgx:begin fn_1_9E14C */
void fn_1_9E14C(u32 arg0, u32 arg1) {
    fn_1_9DDA8(arg0, arg1, 0);
}
/* fzgx:end fn_1_9E14C */

/* fzgx:begin fn_1_9E170 */
void fn_1_9E170(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    fn_1_9DFB8(arg0, arg1, arg2, 0);
}
/* fzgx:end fn_1_9E170 */

/* fzgx:begin fn_1_9E194 */
void fn_1_9E194(u32 arg0, u32 arg1) {
    fn_1_9DDA8(arg0, arg1, 1);
}
/* fzgx:end fn_1_9E194 */

/* fzgx:begin fn_1_9E1B8 */
void fn_1_9E1B8(void) {
    lbl_1_bss_6EA80 = 0;
    lbl_1_bss_6EA84 = (u32)&lbl_1_bss_6EA80;
}
/* fzgx:end fn_1_9E1B8 */

/* fzgx:begin fn_1_9E1D0 */
typedef struct {
    s16 unk_0;
    s16 unk_2;
    u32 unk_4;
    u8 unk_8;
} Fn_1_9E1D0_Entry;

typedef struct Fn_1_9E1D0_Node {
    struct Fn_1_9E1D0_Node *unk_0;
    s32 unk_4;
    Fn_1_9E1D0_Entry *unk_8;
} Fn_1_9E1D0_Node;

void fn_1_9E1D0(void) {
    s32 count;
    Fn_1_9E1D0_Node *node;
    Fn_1_9E1D0_Entry *entry;
    u32 result;

    node = (Fn_1_9E1D0_Node *)lbl_1_bss_6EA80;
    while (node != 0) {
        entry = node->unk_8;
        count = node->unk_4;
        while (count > 0) {
            if (entry->unk_4 == 0) {
                GXPeekZ((u16)entry->unk_0, (u16)entry->unk_2, &entry->unk_4);
                fn_80034200(2);
                fn_8003432C((u16)entry->unk_0, (u16)entry->unk_2, &result);
                entry->unk_8 = (u8)(result >> 24);
            }
            count--;
            entry++;
        }
        node = node->unk_0;
    }
    lbl_1_bss_6EA80 = 0;
    lbl_1_bss_6EA84 = (u32)&lbl_1_bss_6EA80;
}
/* fzgx:end fn_1_9E1D0 */

/* fzgx:begin fn_1_9E598 */
typedef struct Node Node;
struct Node {
    Node *next;
};

// Append a node to the linked-list tail and terminate the new tail.
void fn_1_9E598(Node *node) {
    Node *tail;

    tail = *(Node **)&lbl_1_bss_6EA84;
    tail->next = node;
    node->next = 0;
    lbl_1_bss_6EA84 = (u32)node;
}
/* fzgx:end fn_1_9E598 */

/* fzgx:begin fn_1_9E5B8 */
// Removes a node from the background-node chain and updates its tail link.
void fn_1_9E5B8(Obj_1_bss_6EA80_Target *node) {
    u32 *link;

    link = (u32 *)&lbl_1_bss_6EA80;
    while (*link != 0 && *link != (u32)node) {
        link = (u32 *)*link;
    }
    if (*link == 0) {
        return;
    }
    *link = node->unk_0;
    if (lbl_1_bss_6EA84 == (u32)node) {
        lbl_1_bss_6EA84 = (u32)link;
    }
}
/* fzgx:end fn_1_9E5B8 */
