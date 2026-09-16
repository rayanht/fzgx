#include "types.h"

struct fn_80020B3C_Node;

struct fn_80020B3C_Node {
    struct fn_80020B3C_Node *next;
    struct fn_80020B3C_Node *prev;
    u32 unk_8;
    u32 index;
    u32 unk_10;
    u32 unk_14;
    u8 pad_18[0x8];
    u32 unk_20;
    u8 pad_24[0x122];
    u16 unk_146;
};

struct fn_80020B3C_lbl_8015D100 {
    struct fn_80020B3C_Node *head[32];
    struct fn_80020B3C_Node *tail[32];
};

extern struct fn_80020B3C_lbl_8015D100 lbl_8015D100;
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);
extern void fn_80022E68(struct fn_80020B3C_Node *);

static inline struct fn_80020B3C_Node * *fn_80020B3C_array_read(struct fn_80020B3C_Node * *array) { return array; }
#pragma opt_common_subs off
u32 fn_80020B3C(u32 arg0, u32 arg1, u32 arg2) {
    struct fn_80020B3C_Node *node;
    struct fn_80020B3C_lbl_8015D100 *p;
    struct fn_80020B3C_Node *a;
    struct fn_80020B3C_Node *r;
    struct fn_80020B3C_Node **hp;
    struct fn_80020B3C_Node **tp;
    struct fn_80020B3C_Node *b;
    struct fn_80020B3C_Node **slot;
    u32 idx;
    u32 i;
    BOOL irq;

    idx = arg0;
    p = &lbl_8015D100;
    irq = OSDisableInterrupts();
    r = fn_80020B3C_array_read(p->head)[0];
    if (r != 0) {
        p->head[0] = r->next;
    }
    node = r;
    if (node == 0) {
        hp = &p->head[1];
        tp = &p->tail[1];
        for (i = 1; i < idx; i++) {
            a = *hp;
            r = 0;
            if (a != 0) {
                b = *tp;
                if (a == b) {
                    r = a;
                    *tp = 0;
                    *hp = 0;
                } else if (b != 0) {
                    r = b;
                    *tp = b->prev;
                    (*tp)->next = 0;
                }
            }
            node = r;
            if (r != 0) {
                if (r->unk_146 == 1) {
                    r->unk_20 = 1;
                }
                if (r->unk_10 != 0) {
                    ((void (*)(struct fn_80020B3C_Node *))r->unk_10)(node);
                }
                break;
            }
            hp++;
            tp++;
        }
    }
    if (node != 0) {
        slot = &p->head[idx];
        (void) slot;  /* fzgx: keeps the web at its definition */
        node->next = *slot;
        node->prev = 0;
        if (node->next != 0) {
            (*slot)->prev = node;
            *slot = node;
        } else {
            p->tail[idx] = node;
            *slot = node;
        }
        node->index = idx;
        node->unk_10 = arg1;
        node->unk_14 = arg2;
        fn_80022E68(node);
    }
    OSRestoreInterrupts(irq);
    return (u32)node;
}
#pragma opt_common_subs reset

