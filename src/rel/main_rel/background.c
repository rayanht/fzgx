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

/* fzgx:begin fn_1_9CF78 */
extern s32 fn_8006FC1C(const char *, const char *);
extern s32 fn_8006FC5C(const char *, const char *, s32);
extern s32 strlen(const char *);

typedef u32 (*FilterCallback)(u32, void *);

typedef struct {
    s32 type;
    const char *str;
} TblEntry;

typedef struct {
    s32 count;
    u32 unk4;
    TblEntry *entries;
} TblGroup;

void fn_1_9CF78(void *arg0, FilterCallback arg1) {
    s32 n;
    u32 idx;
    TblEntry *e;
    TblGroup ***p;
    s32 slen;
    TblEntry *q;
    const char *s;
    s32 ok;
    TblGroup *g;
    s32 res;

    p = (TblGroup ***)&lbl_1_data_2CC30;
    ok = 1;
    while (*p != 0) {
        g = **p;
        if (g == 0) {
            p++;
            continue;
        }
        e = g->entries;
        n = g->count;
        for (; n > 0; n--, e++) {
            s = e->str;
            slen = strlen(s);
            q = (TblEntry *)arg0;
            for (idx = 0; q->str != 0; idx++, q++) {
                switch (q->type) {
                case 0:
                    res = fn_8006FC5C(s, q->str, strlen(q->str));
                    break;
                case 1:
                    res = fn_8006FC1C(s, q->str);
                    break;
                case 2: {
                    s32 len = strlen(q->str);
                    if (len > slen) {
                        res = 0;
                    } else {
                        res = fn_8006FC5C(s + (slen - len), q->str, len);
                    }
                    break;
                }
                default:
                    res = 0;
                    break;
                }
                if (res != 0) {
                    ok = arg1(idx, e);
                }
                if (ok == 0) {
                    break;
                }
            }
            if (ok == 0) {
                break;
            }
        }
        if (ok == 0) {
            break;
        }
        p++;
    }
}
/* fzgx:end fn_1_9CF78 */

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

/* fzgx:begin fn_1_9E514 */
extern f32 lbl_1_rodata_42C0[4];
extern void fn_80038BFC(f32 *);
extern u32 __cvt_fp2unsigned(f32);

typedef struct {
    u8 unk_00[0x14];
    f32 unk_14;
    f32 unk_18;
} Fn_1_9E514_Data;

s32 fn_1_9E514(f32 arg0) {
    Fn_1_9E514_Data data;
    f32 *table = (f32 *)&lbl_1_rodata_42C0;
    f32 prod;
    f32 value;

    fn_80038BFC((f32 *)&data);
    prod = data.unk_14 * arg0;
    value = data.unk_18 + prod;
    value /= arg0;
    value = (table[1] - value) * table[3];
    if (value < table[2]) {
        return 0;
    }
    return __cvt_fp2unsigned(value);
}
/* fzgx:end fn_1_9E514 */

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

/* fzgx:begin fn_1_9EDE8 noprologue */
#include "dolphin/hw_regs.h"
#include "types.h"
#include "dolphin/types.h"

extern volatile const f32 lbl_1_rodata_42D0; /* Reload before each ordered FIFO write. */
extern volatile const f32 lbl_1_rodata_42D4; /* Reload before each ordered FIFO write. */
extern u32 lbl_801A6D00;
extern s32 fn_1_54E34(void *, f32);
extern void fn_800724C8(void);
extern void fn_8007245C(u32);
extern void lbl_8006DAEC(void);
extern void lbl_8006D758(void);
extern u32 GXLoadPosMtxImm(u32, u32);
extern void lbl_8006DB30(void);
extern void fn_800736C0(u32, void *);
extern u32 fn_8003462C(u32, u32, u32);
extern void lbl_8006DFC4(u32);
extern void lbl_8006E1D8(u32, f32, f32, f32);

extern vu32 __DIRegs[];

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct {
    u8 pad_00[0x14];
    f32 unk_14;
    u8 pad_18[0x0C];
    f32 unk_24;
    u8 pad_28[0x0C];
    f32 unk_34;
    u32 unk_38;
    u32 unk_3c;
} Obj_1_9EDE8;

/* fzgx-allow: A1 GX FIFO write port; retail materialises it as lis 0xcc01/stfs -0x8000 */
#define FIFO(v) (*(volatile f32 *)(GX_FIFO_BASE + 0x0) = (v)) /* Hardware access must remain ordered. */

void fn_1_9EDE8(Obj_1_9EDE8 *arg0) {
    Vec3 pos;
    u32 z;
    Vec3 vtx[4];
    struct { f32 value; } radius;
    struct { f32 value; } neg;

    pos.x = arg0->unk_14;
    pos.y = arg0->unk_24;
    pos.z = arg0->unk_34;
    if (arg0->unk_38 & 2) {
        radius.value = *(f32 *)((u8 *)arg0 + 4);
    } else {
        radius.value = *(f32 *)arg0;
    }
    if (!(arg0->unk_38 & 4) && fn_1_54E34(&pos, radius.value) == 0) {
        arg0->unk_38 |= 1;
        return;
    }
    arg0->unk_38 &= ~1;
    fn_800724C8();
    fn_8007245C(0x2200);
    lbl_8006DAEC();
    lbl_8006D758();
    GXLoadPosMtxImm(lbl_801A6D00, 0);
    lbl_8006DB30();
    z = arg0->unk_3c;
    fn_800736C0(0, &z);
    fn_8003462C(0x90, 0, 8);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    fn_8003462C(0x80, 0, 4);
    radius.value = *(f32 *)arg0;
    neg.value = -radius.value;
    lbl_8006DAEC();
    lbl_8006DFC4((u32)((u8 *)arg0 + 8));
    lbl_8006E1D8((u32)&vtx[0], neg.value, neg.value, lbl_1_rodata_42D0);
    lbl_8006E1D8((u32)&vtx[1], radius.value, neg.value, lbl_1_rodata_42D0);
    lbl_8006E1D8((u32)&vtx[2], radius.value, radius.value, lbl_1_rodata_42D0);
    lbl_8006E1D8((u32)&vtx[3], neg.value, radius.value, lbl_1_rodata_42D0);
    lbl_8006DB30();
    FIFO(vtx[0].x);
    FIFO(vtx[0].y);
    FIFO(vtx[0].z);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D0);
    FIFO(vtx[1].x);
    FIFO(vtx[1].y);
    FIFO(vtx[1].z);
    FIFO(lbl_1_rodata_42D4);
    FIFO(lbl_1_rodata_42D0);
    FIFO(vtx[2].x);
    FIFO(vtx[2].y);
    FIFO(vtx[2].z);
    FIFO(lbl_1_rodata_42D4);
    FIFO(lbl_1_rodata_42D4);
    FIFO(vtx[3].x);
    FIFO(vtx[3].y);
    FIFO(vtx[3].z);
    FIFO(lbl_1_rodata_42D0);
    FIFO(lbl_1_rodata_42D4);
}
/* fzgx:end fn_1_9EDE8 */
