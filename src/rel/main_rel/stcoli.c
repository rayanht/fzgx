#include "types.h"
#include "rel/main_rel/globals.h"
#include "rel/main_rel/stcoli.h"

extern void fn_1_9D77C(u32, u32);
extern void fn_1_46B4(u32, u32, u8 *, s32);
extern u32 lbl_801A6410;
extern u8 *lbl_801A66CC;
extern void fn_1_180F4(int, int, int, int);
extern void fn_1_18784(int, int, int, int);
extern void fn_1_16BA0(void *, void *, void *, void *, int);
extern void fn_1_18214(void *, void *, int);
extern f32 lbl_1_rodata_6D0;
extern void fn_1_21950(void *, f32, f32);
extern f32 lbl_1_rodata_6D4;
extern void *memset(void *, int, unsigned int);
extern char lbl_1_bss_9C;
extern void fn_1_A2D84(int value);
extern unsigned char lbl_1_rodata_840[];
extern void lbl_8006DAEC(void);
extern void lbl_8006DB30(void);
extern int fn_1_8C66C(short value);
extern int fn_1_163BC(void *arg0, void *arg1, int mask, int value);
extern void lbl_8006E1D8(void *arg0, f32 arg1, f32 arg2, f32 arg3);
extern double lbl_1_rodata_910;
extern void fn_1_18784();
extern void lbl_8006DBE4(void);
extern const f32 lbl_1_rodata_84C;
extern const f32 lbl_1_rodata_854;
extern s16 fn_1_7B054(int);
extern void OSReport(const char *, ...);
extern void OSPanic(const char *, int, const char *, ...);
extern void *fn_1_868C0(s8 value);
extern void fn_1_F7338(s8 value, int arg2, int arg3);
extern const f32 lbl_1_rodata_85C;
extern void lbl_8006E1F0(void *, f32, f32, f32);
extern void fn_8006E978(void *, void *, void *);
extern void mathutil_mtxA_from_quat(void *);
extern void lbl_8006DFC4(void *);
extern void lbl_8006DB74(void *);
extern f64 lbl_1_rodata_860[22];
extern f32 lbl_1_rodata_B74[25];
extern struct fn_1_2B478_lbl_801A6D00 lbl_801A6D00;
extern f32 lbl_8006D6FC(void *, void *);
extern s16 lbl_1_bss_3C2A[3];

/* fzgx:begin fn_1_14CB4 */
void fn_1_14CB4(void) {
    if (lbl_1_bss_3BE0 != 0) {
        if (lbl_1_bss_3BE0->unk_54 != 0) {
            fn_1_9D77C(lbl_1_bss_3BE0->unk_54, lbl_1_bss_3BE0->unk_48);
        }

        fn_1_46B4(lbl_801A6410, lbl_1_bss_3BE4.unk_0, lbl_1_data_51C8, 0x2c9);
        lbl_1_bss_3BE4.unk_0 = 0;
        fn_1_46B4(lbl_801A6410, (u32)lbl_1_bss_3BE0, lbl_1_data_51C8, 0x2cb);
        lbl_1_bss_3BE0 = 0;
    }
}
/* fzgx:end fn_1_14CB4 */

/* fzgx:begin fn_1_14DC4 */
u32 fn_1_14DC4(void) {
    if (lbl_1_bss_3BE0 != 0) {
        return lbl_1_bss_3BE0->unk_14;
    }
    return 0;
}
/* fzgx:end fn_1_14DC4 */

/* fzgx:begin fn_1_14DE8 */
typedef struct {
    s32 unk_0;
    s32 unk_4;
    s8 unk_8;
    s8 unk_9;
} StcoliEntry;

typedef struct {
    s32 count;
    u8 *base;
    u8 pad_8[4];
} StcoliRecord;

extern f32 lbl_1_rodata_6B0[6];
extern u8 lbl_1_data_54B4[148];

#pragma opt_loop_invariants off
void fn_1_14DE8(u32 index) {
    Obj_1_bss_3BE0_Target **manager;
    f32 *constants;
    StcoliEntry *entry;
    StcoliRecord *record;
    u8 *object;
    s32 slot;
    f32 zero;
    f32 value;

    constants = lbl_1_rodata_6B0;
    manager = &lbl_1_bss_3BE0;
    if (*manager == 0) {
        return;
    }
    if (index >= 0x24) {
        return;
    }

    entry = ((StcoliEntry **)lbl_1_data_54B4)[index];
    if (entry == 0) {
        return;
    }

    while (entry->unk_0 >= 0) {
        record = (StcoliRecord *)(*manager)->unk_C + entry->unk_0;
        if (entry->unk_4 >= record->count) {
            return;
        }

        slot = entry->unk_4;
        object = record->base + slot * 0x50;
        if (entry->unk_8) {
            if ((s32)index == 7) {
                zero = constants[0];
                value = constants[3];
                *(f32 *)(object + 0x0C) = zero;
                *(f32 *)(object + 0x10) = zero;
                *(f32 *)(object + 0x14) = value;
                *(f32 *)(object + 0x08) = -*(f32 *)(object + 0x20);
            } else if (!*(s8 *)(object + 0x4C)) {
                *(s8 *)(object + 0x4C) = 1;
            }
        }

        if (entry->unk_9) {
            if ((s32)index == 7) {
                zero = constants[0];
                value = constants[4];
                *(f32 *)(object + 0x28) = zero;
                *(f32 *)(object + 0x2C) = zero;
                *(f32 *)(object + 0x30) = value;
                *(f32 *)(object + 0x24) = *(f32 *)(object + 0x3C);
            } else if (!*(s8 *)(object + 0x4D)) {
                *(s8 *)(object + 0x4D) = 1;
            }
        }

        entry++;
    }
}
#pragma opt_loop_invariants reset
/* fzgx:end fn_1_14DE8 */

/* fzgx:begin fn_1_14F04 */
u8 *fn_1_14F04(void) {
    return lbl_801A66CC + 0x1b0;
}
/* fzgx:end fn_1_14F04 */

/* fzgx:begin fn_1_17B5C */
typedef struct {
    u8 pad_0[0x40];
    f32 unk_40;
    f32 unk_44;
    u8 pad_48[0x5];
    s8 unk_4D;
} Fn17B5C_Record;

typedef struct {
    u32 unk_0;
    Fn17B5C_Record *unk_4;
    u32 unk_8;
} Fn17B5C_Slot;

int fn_1_17B5C(int a, int b, int count, f32 threshold) {
    int end;
    int span;
    int j;
    int found;
    int result;
    Fn17B5C_Slot *left;
    Fn17B5C_Slot *right;
    f32 delta;

    if (a == b) {
        return 1;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

    span = b - a;
    {
        int diff = count - span;
        if (diff < span) {
            int temp = a;
            a = b;
            b = temp;
            span = diff;
        }
    }

    left = &((Fn17B5C_Slot *)lbl_1_bss_3BE0->unk_C)[a];
    right = &((Fn17B5C_Slot *)lbl_1_bss_3BE0->unk_C)[b];
    if (threshold > lbl_1_rodata_6D0) {
        delta = right->unk_4->unk_40 - left->unk_4->unk_44;
        if (delta < lbl_1_rodata_6D0) {
            delta += *(f32 *)lbl_1_bss_3BE0->unk_90;
        }
        if (delta > threshold) {
            return 0;
        }
    }

    b = a + 1;
    end = count - 1;
    found = 0;
    for (j = 0; j < span; j++) {
        if (b > end) {
            b = 0;
        }
        if (!((Fn17B5C_Slot *)lbl_1_bss_3BE0->unk_C)[a].unk_4->unk_4D) {
            break;
        }
        a = b;
        found++;
        b++;
    }

    result = 0;
    if (span == 0 || found >= span) {
        result = 1;
    }
    return result;
}
/* fzgx:end fn_1_17B5C */

/* fzgx:begin fn_1_17C6C */
#include "types.h"

typedef struct Entry {
    char pad[0x4d];
    s8 active;
} Entry;

typedef struct Slot {
    int pad;
    Entry *entry;
    int tail;
} Slot;

typedef struct Root {
    char pad[0xc];
    Slot *slots;
} Root;

int fn_1_17C6C(int current, int next, int limit) {
    int end;
    int count;
    int span;
    int result;

    if (current == next) {
        return 1;
    }

    if (current > next) {
        int temp = current;
        current = next;
        next = temp;
    }

    span = next - current;
    {
        int diff = limit - span;
        if (diff < span) {
            current = next;
            span = diff;
        }
    }

    next = current + 1;
    count = 0;
    end = limit - 1;

    while (count < span) {
        if (next > end) {
            next = 0;
        }

        if (!(*(Root **)&(*(u32 *)&lbl_1_bss_3BE0))->slots[current].entry->active) {
            break;
        }
        if (current == 0x8b && fn_1_7B054(current) == 3) {
            break;
        }
        current = next;
        count++;
        next++;
    }

    result = 0;
    if (span == 0 || count >= span) {
        result = 1;
    }
    return result;
}
/* fzgx:end fn_1_17C6C */

/* fzgx:begin fn_1_17D5C */
typedef struct Node {
    u32 unk_0;
    u8 pad_4[0x8];
    s32 count;
    struct Node *children;
    u8 pad_14[0x50 - 0x14];
} Node;

void fn_1_17D5C(Node *node, u32 *acc);

void fn_1_17D5C(Node *node, u32 *acc) {
    Node *root;
    s32 i1;
    Node *p1;
    Node *p2;
    s32 i2;
    Node *p3;
    s32 i3;
    Node *p4;
    s32 i4;
    Node *p5;
    s32 i5;
    Node *p6;
    s32 i6;
    Node *p7;
    s32 i7;
    Node *p8;
    s32 i8;
    Node *p9;
    s32 i9;

    root = node;
    *acc |= root->unk_0;
    if (root->count > 0) {
        i1 = 0;
        p1 = root->children;
        while (i1 < root->count) {
            *acc |= p1->unk_0;
            if (p1->count > 0) {
                p2 = p1->children;
                i2 = 0;
                while (i2 < p1->count) {
                    *acc |= p2->unk_0;
                    if (p2->count > 0) {
                        p3 = p2->children;
                        i3 = 0;
                        while (i3 < p2->count) {
                            *acc |= p3->unk_0;
                            if (p3->count > 0) {
                                p4 = p3->children;
                                i4 = 0;
                                while (i4 < p3->count) {
                                    *acc |= p4->unk_0;
                                    if (p4->count > 0) {
                                        p5 = p4->children;
                                        i5 = 0;
                                        while (i5 < p4->count) {
                                            *acc |= p5->unk_0;
                                            if (p5->count > 0) {
                                                p6 = p5->children;
                                                i6 = 0;
                                                while (i6 < p5->count) {
                                                    *acc |= p6->unk_0;
                                                    if (p6->count > 0) {
                                                        p7 = p6->children;
                                                        i7 = 0;
                                                        while (i7 < p6->count) {
                                                            *acc |= p7->unk_0;
                                                            if (p7->count > 0) {
                                                                p8 = p7->children;
                                                                i8 = 0;
                                                                while (i8 < p7->count) {
                                                                    *acc |= p8->unk_0;
                                                                    if (p8->count > 0) {
                                                                        p9 = p8->children;
                                                                        i9 = 0;
                                                                        while (i9 < p8->count) {
                                                                            fn_1_17D5C(p9, acc);
                                                                            i9++;
                                                                            p9++;
                                                                        }
                                                                    }
                                                                    i8++;
                                                                    p8++;
                                                                }
                                                            }
                                                            i7++;
                                                            p7++;
                                                        }
                                                    }
                                                    i6++;
                                                    p6++;
                                                }
                                            }
                                            i5++;
                                            p5++;
                                        }
                                    }
                                    i4++;
                                    p4++;
                                }
                            }
                            i3++;
                            p3++;
                        }
                    }
                    i2++;
                    p2++;
                }
            }
            i1++;
            p1++;
        }
    }
}
/* fzgx:end fn_1_17D5C */

/* fzgx:begin fn_1_17FCC */
typedef struct {
    u8 pad_0[0x8];
    u32 unk_8;
} StcoliEntry;

extern void fn_1_17D5C(u32, u32 *);

int fn_1_17FCC(int a, int b, int c) {
    int count;
    int i;
    int end;
    StcoliEntry *last;
    StcoliEntry *entry;
    u32 fa;
    u32 fb;
    int result;

    if (a == b) {
        return 1;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    count = b - a;
    i = c - count;
    if (i < count) {
        a = b;
        count = i;
    }
    b = a + 1;
    end = c;
    end = end - 1;
    last = (StcoliEntry *)lbl_1_bss_3BE0->unk_C + a;
    i = 0;
    while (i < count) {
        if (b > end) {
            b = 0;
        }
        entry = (StcoliEntry *)lbl_1_bss_3BE0->unk_C + b;
        fb = 0;
        fa = 0;
        fn_1_17D5C(last->unk_8, &fa);
        fn_1_17D5C(entry->unk_8, &fb);
        if ((fa & 0x01000000) != 0 && (fb & 0x00800000) != 0) {
            break;
        }
        if ((fb & 0x01000000) != 0 && (fa & 0x00800000) != 0) {
            break;
        }
        last = entry;
        i++;
        b++;
    }
    result = 0;
    if (count == 0 || i >= count) {
        result = 1;
    }
    return result;
}
/* fzgx:end fn_1_17FCC */

/* fzgx:begin fn_1_181CC */
// fn_1_181CC: main_rel .text:0x000181CC size 0x24
// Wrapper function that passes first three arguments through and sets fourth to 1

void fn_1_181CC(int a, int b, int c) {
    fn_1_180F4(a, b, c, 1);
}
/* fzgx:end fn_1_181CC */

/* fzgx:begin fn_1_181F0 */
void fn_1_181F0(int a, int b, int c) {
    fn_1_180F4(a, b, c, 0);
}
/* fzgx:end fn_1_181F0 */

/* fzgx:begin fn_1_18214 noprologue */
#include "types.h"

typedef struct {
    u32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24;
    u32 f28, f2c, f30, f34, f38, f3c, f40, f44;
} Cfg;

typedef struct {
    u8 pad_0[0x4];
    Cfg *cfg;
    u8 pad_8[0xc];
    f32 fx;
    f32 fy;
    f32 fz;
    f32 rxv;
    f32 ryv;
    f32 rzv;
    f32 sxv;
    f32 syv;
    f32 szv;
} Entity;

typedef struct {
    u32 count;
    u32 entries[1];
} Stack;

extern f32 fn_1_9E14C(u32, u32, f32);
extern f32 fn_1_9E170(u32, u32, void *, f32);
extern const f32 lbl_1_rodata_6D0;
extern f32 lbl_1_rodata_6F8;
extern u32 mathutil_mtxA_rotate_x(u32);
extern u32 mathutil_mtxA_rotate_y(u32);
extern u32 mathutil_mtxA_rotate_z(u32);
extern void fn_80008BEC(void *, int, void *);
extern void lbl_8006E0B4(f32, f32, f32);

void fn_1_18214(Entity *arg0, f32 *arg1, Stack *arg2, f32 t) {
    Cfg *v0 = arg0->cfg;
    u8 *slot;
    s32 ang;
    f32 a;
    f32 b;
    f32 c;
    f32 r;

    if (arg2 != 0) {
        slot = (u8 *)arg2 + arg2->count * 36 + 44;
        if (arg2->entries[arg2->count] != (u32)arg0) {
            fn_80008BEC((u8 *)arg2 + arg2->count * 36 + 44, 0, (void *)36);
        }
        if (v0->f3c != 0) {
            a = fn_1_9E170(v0->f18, v0->f3c, slot, t);
        } else {
            a = arg0->sxv;
        }
        if (v0->f40 != 0) {
            b = fn_1_9E170(v0->f1c, v0->f40, slot + 4, t);
        } else {
            b = arg0->syv;
        }
        if (v0->f44 != 0) {
            c = fn_1_9E170(v0->f20, v0->f44, slot + 8, t);
        } else {
            c = arg0->szv;
        }
        if (lbl_1_rodata_6D0 != a || lbl_1_rodata_6D0 != b || lbl_1_rodata_6D0 != c) {
            lbl_8006E0B4(arg1[0] * a, arg1[1] * b, arg1[2] * c);
        }
        if (v0->f30 != 0) {
            a = fn_1_9E170(v0->f0c, v0->f30, slot + 12, t);
        } else {
            a = arg0->rxv;
        }
        if (v0->f34 != 0) {
            b = fn_1_9E170(v0->f10, v0->f34, slot + 16, t);
        } else {
            b = arg0->ryv;
        }
        if (v0->f38 != 0) {
            c = fn_1_9E170(v0->f14, v0->f38, slot + 20, t);
        } else {
            c = arg0->rzv;
        }
        if (lbl_1_rodata_6D0 != c) {
            if (((s32)(lbl_1_rodata_6F8 * c) & 0xFFFF) != 0) {
                mathutil_mtxA_rotate_z((s16)(u16)(s32)(lbl_1_rodata_6F8 * c));
            }
        }
        if (lbl_1_rodata_6D0 != b) {
            if (((s32)(lbl_1_rodata_6F8 * b) & 0xFFFF) != 0) {
                mathutil_mtxA_rotate_y((s16)(u16)(s32)(lbl_1_rodata_6F8 * b));
            }
        }
        if (lbl_1_rodata_6D0 != a) {
            if (((s32)(lbl_1_rodata_6F8 * a) & 0xFFFF) != 0) {
                mathutil_mtxA_rotate_x((s16)(u16)(s32)(lbl_1_rodata_6F8 * a));
            }
        }
        if (v0->f24 != 0) {
            r = fn_1_9E170(v0->f00, v0->f24, slot + 24, t);
        } else {
            r = arg0->fx;
        }
        arg1[0] = arg1[0] * r;
        if (v0->f28 != 0) {
            r = fn_1_9E170(v0->f04, v0->f28, slot + 28, t);
        } else {
            r = arg0->fy;
        }
        arg1[1] = arg1[1] * r;
        if (v0->f2c != 0) {
            r = fn_1_9E170(v0->f08, v0->f2c, slot + 32, t);
        } else {
            r = arg0->fz;
        }
        arg1[2] = arg1[2] * r;
    } else {
        if (v0->f3c != 0) {
            a = fn_1_9E14C(v0->f18, v0->f3c, t);
        } else {
            a = arg0->sxv;
        }
        if (v0->f40 != 0) {
            b = fn_1_9E14C(v0->f1c, v0->f40, t);
        } else {
            b = arg0->syv;
        }
        if (v0->f44 != 0) {
            c = fn_1_9E14C(v0->f20, v0->f44, t);
        } else {
            c = arg0->szv;
        }
        if (lbl_1_rodata_6D0 != a || lbl_1_rodata_6D0 != b || lbl_1_rodata_6D0 != c) {
            lbl_8006E0B4(arg1[0] * a, arg1[1] * b, arg1[2] * c);
        }
        if (v0->f30 != 0) {
            b = fn_1_9E14C(v0->f0c, v0->f30, t);
        } else {
            b = arg0->rxv;
        }
        if (v0->f34 != 0) {
            a = fn_1_9E14C(v0->f10, v0->f34, t);
        } else {
            a = arg0->ryv;
        }
        if (v0->f38 != 0) {
            c = fn_1_9E14C(v0->f14, v0->f38, t);
        } else {
            c = arg0->rzv;
        }
        if (lbl_1_rodata_6D0 != c) {
            if (((s32)(lbl_1_rodata_6F8 * c) & 0xFFFF) != 0) {
                mathutil_mtxA_rotate_z((s16)(u16)(s32)(lbl_1_rodata_6F8 * c));
            }
        }
        if (lbl_1_rodata_6D0 != a) {
            if (((s32)(lbl_1_rodata_6F8 * a) & 0xFFFF) != 0) {
                mathutil_mtxA_rotate_y((s16)(u16)(s32)(lbl_1_rodata_6F8 * a));
            }
        }
        if (lbl_1_rodata_6D0 != b) {
            if (((s32)(lbl_1_rodata_6F8 * b) & 0xFFFF) != 0) {
                mathutil_mtxA_rotate_x((s16)(u16)(s32)(lbl_1_rodata_6F8 * b));
            }
        }
        if (v0->f24 != 0) {
            r = fn_1_9E14C(v0->f00, v0->f24, t);
        } else {
            r = arg0->fx;
        }
        arg1[0] = arg1[0] * r;
        if (v0->f28 != 0) {
            r = fn_1_9E14C(v0->f04, v0->f28, t);
        } else {
            r = arg0->fy;
        }
        arg1[1] = arg1[1] * r;
        if (v0->f2c != 0) {
            r = fn_1_9E14C(v0->f08, v0->f2c, t);
        } else {
            r = arg0->fz;
        }
        arg1[2] = arg1[2] * r;
    }
    if (arg2 != 0) {
        arg2->entries[arg2->count] = (u32)arg0;
        if ((s32)arg2->count < 9) {
            arg2->count = arg2->count + 1;
        }
    }
}
/* fzgx:end fn_1_18214 */

/* fzgx:begin fn_1_18F28 noprologue */
#include "types.h"

typedef struct {
    unsigned char pad0[0x0c];
    int count;
    void *entries;
} Fn118F28Object;

typedef struct {
    unsigned int flags;
} Fn118F28Entry;

typedef struct {
    int x;
    int y;
    int z;
} Fn118F28Vector;

extern void lbl_8006DAEC(void);
extern void lbl_8006DB30(void);
extern void lbl_8006DBE4(int, int);
extern void fn_1_1902C(Fn118F28Entry *, int *, int, float);

void fn_1_18F28(Fn118F28Object *obj, int *args, int arg2, float value) {
    Fn118F28Vector vector;
    int i;
    Fn118F28Entry *entry;

    if (obj->count > 0) {
        lbl_8006DAEC();
        entry = (Fn118F28Entry *)obj->entries;
        i = 0;
        while (i < obj->count) {
            if ((entry->flags & 0x1e0002) == 0) {
                vector = *(Fn118F28Vector *)args;
                lbl_8006DBE4(vector.y, vector.x);
                fn_1_1902C(entry, args, arg2, value);
                *(Fn118F28Vector *)args = vector;
            }
            i++;
            entry = (Fn118F28Entry *)((char *)entry + 0x50);
        }
        lbl_8006DB30();
    }
}
/* fzgx:end fn_1_18F28 */

/* fzgx:begin fn_1_18FFC */
void fn_1_18FFC(int a, int b, int c, int d, int e, int f, int g) {
    fn_1_18784(c, d, e, g);
}
/* fzgx:end fn_1_18FFC */

/* fzgx:begin fn_1_1902C */
typedef struct StcoliNode StcoliNode;
typedef struct StcoliVec {
    u32 x;
    u32 y;
    u32 z;
} StcoliVec;

struct StcoliNode {
    u32 flags;
    u8 pad[8];
    s32 count;
    StcoliNode *items;
    u8 rest[0x3c];
};

extern void fn_1_18F28(StcoliNode *, StcoliVec *, void *, f32);

// Traverse the four-level collision hierarchy, preserving the input vector at each level.
void fn_1_1902C(StcoliNode *root, StcoliVec *vec, void *arg3, f32 value) {
    StcoliNode *level1;
    s32 i1;

    fn_1_18784(0x800000, root, vec, 0, value);
    if (root->count > 0) {
        lbl_8006DAEC();
        level1 = root->items;
        i1 = 0;
        while (i1 < root->count) {
            if ((level1->flags & 0x001e0002) == 0) {
                StcoliVec saved1 = *vec;
                StcoliNode *level2;
                s32 i2;

                lbl_8006DBE4();
                fn_1_18784(0x800000, level1, vec, 0, value);
                if (level1->count > 0) {
                    lbl_8006DAEC();
                    level2 = level1->items;
                    i2 = 0;
                    while (i2 < level1->count) {
                        if ((level2->flags & 0x001e0002) == 0) {
                            StcoliVec saved2 = *vec;
                            StcoliNode *level3;
                            s32 i3;

                            lbl_8006DBE4();
                            fn_1_18784(0x800000, level2, vec, 0, value);
                            if (level2->count > 0) {
                                lbl_8006DAEC();
                                level3 = level2->items;
                                i3 = 0;
                                while (i3 < level2->count) {
                                    if ((level3->flags & 0x001e0002) == 0) {
                                        StcoliVec saved3 = *vec;
                                        StcoliNode *level4;
                                        s32 i4;

                                        lbl_8006DBE4();
                                        fn_1_18784(0x800000, level3, vec, 0, value);
                                        if (level3->count > 0) {
                                            lbl_8006DAEC();
                                            level4 = level3->items;
                                            i4 = 0;
                                            while (i4 < level3->count) {
                                                if ((level4->flags & 0x001e0002) == 0) {
                                                    StcoliVec saved4 = *vec;

                                                    lbl_8006DBE4();
                                                    fn_1_18784(0x800000, level4, vec, 0, value);
                                                    fn_1_18F28(level4, vec, arg3, value);
                                                    *vec = saved4;
                                                }
                                                i4 += 1;
                                                level4 += 1;
                                            }
                                            lbl_8006DB30();
                                        }
                                        *vec = saved3;
                                    }
                                    i3 += 1;
                                    level3 += 1;
                                }
                                lbl_8006DB30();
                            }
                            *vec = saved2;
                        }
                        i2 += 1;
                        level2 += 1;
                    }
                    lbl_8006DB30();
                }
                *vec = saved1;
            }
            i1 += 1;
            level1 += 1;
        }
        lbl_8006DB30();
    }
}
/* fzgx:end fn_1_1902C */

/* fzgx:begin fn_1_20258 */
typedef struct Fn_1_20258Constants {
    unsigned char pad08[8];
    f32 value08;
    f32 value0c;
    unsigned char pad10[0xb0];
    f64 valuec0;
    f32 valuec8;
    unsigned char padcc[4];
    f64 valued0;
} Fn_1_20258Constants;

extern Fn_1_20258Constants lbl_1_rodata_6C8;

typedef struct Fn_1_20258 {
    unsigned char pad00[0x30];
    f32 field30;
    f32 field34;
    unsigned char pad38[4];
    f32 field3c;
    unsigned char pad40[0x28];
    f32 field68;
    f32 field6c;
    unsigned char pad70[0xc];
    u32 flags;
} Fn_1_20258;

#pragma opt_strength_reduction on
f32 fn_1_20258(Fn_1_20258 *self, f32 *out_ratio) {
    u32 flags = self->flags;
    u8 *data = (*(u8 (*)[400])&lbl_1_data_5548);
    Fn_1_20258Constants *constants = &lbl_1_rodata_6C8;
    f32 ratio;
    f32 scale;

    if ((flags & 0x01c00000) != 0) {
        ratio = self->field34 / self->field30;
        if (ratio < constants->valuec0) {
            ratio = constants->value08;
        }
    } else if ((flags & 0x02200000) != 0) {
        ratio = constants->value0c;
    } else {
        OSReport((const char *)(data + 0x108), flags);
        OSPanic((const char *)(data + 0x12c), 0x1650,
                    (const char *)(data + 0x134));
    }

    if ((self->flags & 0x02200000) != 0 ||
        constants->value08 == ratio) {
        scale = self->field68;
    } else if ((self->flags & 0x01800000) != 0) {
        f32 t;

        t = constants->valuec8 * ratio;
        scale = (constants->value0c + t) * (self->field6c * self->field68);
    } else if ((self->flags & 0x00400000) != 0) {
        f32 t;
        f64 prod;

        t = constants->valuec8 * ratio;
        prod = constants->valued0 * self->field3c;
        scale = prod + (constants->value0c + t) * (self->field68 - self->field3c);
    } else {
        OSReport((const char *)(data + 0x138), self->flags);
        OSPanic((const char *)(data + 0x12c), 0x1661,
                    (const char *)(data + 0x15c));
    }

    if (out_ratio != 0) {
        *out_ratio = ratio;
    }
    return scale;
}
#pragma opt_strength_reduction reset
/* fzgx:end fn_1_20258 */

/* fzgx:begin fn_1_20994 noprologue */
#include "types.h"

typedef struct Fn_1_20994_Object {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u8 pad_0C[0x71];
    u8 unk_7D;
} Fn_1_20994_Object;

extern const f32 lbl_1_rodata_6D0;
extern Fn_1_20994_Object *lbl_1_bss_3BE0;
extern int fn_1_210A8(void *, f32 *, int, int, int);

int fn_1_20994(void *arg, f32 *out) {
    f32 value;
    int result;
    int index;
    Fn_1_20994_Object *object;

    value = lbl_1_rodata_6D0;
    result = 0;
    object = lbl_1_bss_3BE0;
    if (object != 0) {
        if (object->unk_7D != 0) {
            index = 0;
        } else {
            index = object->unk_8 - 1;
        }
        do {
            result = fn_1_210A8(arg, &value, index--, 0, 0);
        } while (result < 0 && index >= 0);
        if (result < 0) {
            result = 0;
            value = lbl_1_rodata_6D0;
        }
    }
    *out = value;
    return result;
}
/* fzgx:end fn_1_20994 */

/* fzgx:begin fn_1_21644 noprologue */
#include "types.h"

extern int fn_1_16BA0(void *, void *, void *, int *, int);
extern f32 fn_1_16E68(void *, void *, int);

void *fn_1_21644(void *arg0, f32 *arg1, void *arg2) {
    int local;

    int status;

    local = 0;
    status = fn_1_16BA0(arg0, arg1, arg2, &local, 0);
    if (status < 0) {
        local = 0;
        *arg1 = fn_1_16E68(arg0, arg2, 0);
        return arg2;
    }
    return (void *)status;
}
/* fzgx:end fn_1_21644 */

/* fzgx:begin fn_1_216C0 */
void fn_1_216C0(void *arg0, void *arg1, void *arg2) {
    int local;

    local = 0;
    fn_1_16BA0(arg0, arg1, arg2, &local, 0);
}
/* fzgx:end fn_1_216C0 */

/* fzgx:begin fn_1_2192C */
void fn_1_2192C(void *self, void *arg) {
    fn_1_18214(self, arg, 0);
}
/* fzgx:end fn_1_2192C */

/* fzgx:begin fn_1_21BE4 */
typedef struct Fn_1_21BE4 {
    u32 flags;
    unsigned char pad04[0x38];
    f32 field3c;
    f32 field40;
} Fn_1_21BE4;

void fn_1_21BE4(Fn_1_21BE4 *self, void *arg) {
    f32 value2;
    f32 value1;

    fn_1_18214(self, arg, 0);
    if ((self->flags & 0x800) != 0) {
        value2 = self->field3c;
    } else {
        value2 = lbl_1_rodata_6D0;
    }
    if ((self->flags & 0x400) != 0) {
        value1 = self->field40;
    } else {
        value1 = lbl_1_rodata_6D0;
    }
    fn_1_21950(arg, value1, value2);
}
/* fzgx:end fn_1_21BE4 */

/* fzgx:begin fn_1_21C5C */
void fn_1_21C5C(void *self, void *arg) {
    fn_1_18214(self, arg, 0);
    fn_1_21950(arg, lbl_1_rodata_6D4, lbl_1_rodata_6D4);
}
/* fzgx:end fn_1_21C5C */

/* fzgx:begin fn_1_21CA0 */
typedef struct Fn_1_21CA0 {
    u32 flags;
    unsigned char pad04[0x38];
    f32 field3c;
    f32 field40;
} Fn_1_21CA0;

void fn_1_21CA0(Fn_1_21CA0 *self, void *arg) {
    f32 value2;
    f32 value1;

    if ((self->flags & 0x800) != 0) {
        value2 = self->field3c;
    } else {
        value2 = lbl_1_rodata_6D0;
    }
    if ((self->flags & 0x400) != 0) {
        value1 = self->field40;
    } else {
        value1 = lbl_1_rodata_6D0;
    }
    fn_1_21950(arg, value1, value2);
}
/* fzgx:end fn_1_21CA0 */

/* fzgx:begin fn_1_22E8C */
typedef struct Fn_1_22E8CInput {
    unsigned char pad00[0x04];
    float field04;
    float field08;
    float field0c;
    float field10;
    float field14;
    float field18;
    float field1c;
    float field20;
    float field24;
    float field28;
    float field2c;
    float field30;
    float field34;
    float field38;
    float field3c;
    float field40;
    float field44;
    unsigned char field48;
    unsigned char field49;
    unsigned char pad4a[0x02];
    float field4c;
    float field50;
} Fn_1_22E8CInput;

typedef struct Fn_1_22E8COutput {
    unsigned int flags;
    unsigned char pad04[0x04];
    float field08;
    float field0c;
    float field10;
    float field14;
    float field18;
    float field1c;
    float field20;
    float field24;
    float field28;
    float field2c;
    float field30;
    float field34;
    float field38;
    unsigned char pad3c[0x1e4];
    float field220;
    unsigned char pad224[0x08];
    float field22c;
    float field230;
    float field234;
    float field238;
    float field23c;
    unsigned char pad240[0x237];
    unsigned char field477;
} Fn_1_22E8COutput;

void fn_1_22E8C(Fn_1_22E8COutput *self, Fn_1_22E8CInput *source) {
    float first = source->field04;
    double scale = lbl_1_rodata_910;

    self->field08 = first;
    self->field0c = source->field10;
    self->field28 = source->field14;
    self->field14 = source->field20;
    self->field1c = source->field28;
    self->field20 = source->field2c;
    self->field24 = source->field30;
    self->field30 = source->field44;
    self->field10 = source->field18;
    self->field2c = source->field1c;
    self->field477 = source->field48;
    self->field34 = source->field4c;
    self->field38 = source->field50;
    self->field18 = source->field24;
    self->field220 = source->field08;
    self->field22c = source->field0c;
    self->field230 = (float)(scale * source->field34);
    self->field234 = source->field38;
    self->field238 = source->field3c;
    self->field23c = source->field40;
    if (source->field49 & 1) {
        self->flags |= 0x100;
    } else {
        self->flags &= ~0x100;
    }
    if (source->field49 & 2) {
        self->flags |= (1u << 31);
    } else {
        self->flags &= 0x7fffffff;
    }
}
/* fzgx:end fn_1_22E8C */

/* fzgx:begin fn_1_23500 */
#pragma section code_type ".fzgxpool"
__declspec(section ".fzgxpool") static void fzgx_pool_prime1(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 52.0f;
    s = 0.0625f;
    s = 45.0f;
    s = 0.0f;
    s = 1.7000000476837158f;
    s = 1.0f;
    s = 0.10000000149011612f;
    s = 0.5f;
    d = 4503599627370496.0;
    s = 40.0f;
    s = 348.0f;
    s = 36.0f;
    s = 4.0f;
    s = 0.6000000238418579f;
    s = 5.0f;
    s = 0.05000000074505806f;
    s = 1000.0f;
    s = 8.0f;
}
static const u32 fzgx_pool_table2[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep2(void) { const u32 *volatile cp; cp = fzgx_pool_table2; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime3(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 216.0;
    d = 2.0;
    s = 0.25f;
    s = 0.07000000029802322f;
    s = 0.20000000298023224f;
}
static const u32 fzgx_pool_table4[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep4(void) { const u32 *volatile cp; cp = fzgx_pool_table4; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime5(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 1.834999918937683f;
}
static const u32 fzgx_pool_table6[1] = {0xAE147AE1};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep6(void) { const u32 *volatile cp; cp = fzgx_pool_table6; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime7(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 2.0f;
    s = 1.7999999523162842f;
    s = 1.399999976158142f;
    s = 1.5f;
    s = 1.2000000476837158f;
    s = 2.299999952316284f;
    s = 0.4000000059604645f;
    s = 3.200000047683716f;
    s = 0.15000000596046448f;
    s = -0.25f;
    s = 0.1599999964237213f;
    s = 0.11999999731779099f;
    s = 0.07999999821186066f;
    s = 0.44999998807907104f;
    s = 0.699999988079071f;
}
static const u32 fzgx_pool_table8[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep8(void) { const u32 *volatile cp; cp = fzgx_pool_table8; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime9(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.6000000238418579;
    s = 0.3100000023841858f;
    s = 0.029999999329447746f;
    s = 0.009999999776482582f;
    s = 700.0f;
    s = 1.7674999237060547f;
}
static const u32 fzgx_pool_table10[1] = {0xA3D70A3D};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep10(void) { const u32 *volatile cp; cp = fzgx_pool_table10; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime11(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.5699999928474426f;
}
static const u32 fzgx_pool_table12[4] = {0x00000000, 0x00000000, 0x00000000, 0x3F800000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep12(void) { const u32 *volatile cp; cp = fzgx_pool_table12; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime13(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = -0.10000000149011612f;
    s = 200.0f;
    s = 0.019999999552965164f;
}
#pragma section code_type ".text"

typedef struct Fn_1_23500_Rodata {
    unsigned char pad00[0xc];
    f32 value0c;
    unsigned char pad10[0x4];
    f32 value14;
    unsigned char pad18[0x38];
    f64 value50;
    unsigned char pad58[0x98];
    f32 valuef0;
} Fn_1_23500_Rodata;

extern unsigned char lbl_1_rodata_840[];
extern void fn_1_22F90(void *self, int value);
extern void lbl_8006E1F0(void *self, f32 x, f32 y, f32 z);
extern void fn_1_8A190(void *self, int value);

typedef struct Fn_1_23500 {
    int flags;
    unsigned char pad04[4];
    f32 field08;
    unsigned char pad0c[0x88];
    f32 field94;
    unsigned char pad98[0x168];
    f32 field200;
    unsigned char pad204[0x20];
    f32 field224;
    unsigned char pad228[0x259];
    unsigned char field481;
} Fn_1_23500;

void fn_1_23500(Fn_1_23500 *self, f32 value) {
    Fn_1_23500_Rodata *table;
    f64 factor;
    f32 amount;
    f32 one;

    table = (Fn_1_23500_Rodata *)lbl_1_rodata_840;
    factor = value / (216.0);
    amount = factor * self->field08;
    fn_1_22F90(self, 1);
    if ((0.0f) != value) {
        lbl_8006E1F0(&self->field94, (0.0f), (0.0f), -amount);
        one = (1.0f);
        self->field224 = value / (200.0f);
        self->flags |= 0x400;
        self->field200 = one;
        self->field481 = 0x5a;
    }
    fn_1_8A190(self, 1);
}
/* fzgx:end fn_1_23500 */

/* fzgx:begin fn_1_235C8 */
typedef struct Fn_1_235C8 {
    unsigned char *field00;
    unsigned char *field04;
    unsigned char data[0xb8];
} Fn_1_235C8;

void fn_1_235C8(Fn_1_235C8 *self) {
    if (self != 0) {
        memset(self, 0, 0xc0);
        self->field00 = &self->data[0];
        self->field04 = &self->data[0x5c];
    }
}
/* fzgx:end fn_1_235C8 */

/* fzgx:begin fn_1_23610 */
void fn_1_23610(void *self) {
    if (self != 0) {
        memset(self, 0, 0x194);
    }
}
/* fzgx:end fn_1_23610 */

/* fzgx:begin fn_1_23640 */
typedef struct Fn_1_23640 {
    unsigned char pad00[0x80];
    int field80;
    unsigned char pad84[0x0c];
    int *field90;
    int *field94;
    unsigned char pad98[0x04];
    int field9c;
    unsigned char padA0[0x18];
    int fieldb8;
    unsigned char padbc[0x0c];
    int fieldc8;
    unsigned char padcc[0x0c];
    int fieldd8;
    unsigned char pade0[0x40];
    int field11c;
    unsigned char pad120[0x3c];
    int field15c;
    unsigned char tail160[0x9c];
} Fn_1_23640;

void fn_1_23640(Fn_1_23640 *self, int value) {
    if (self != 0) {
        if (value != 0) {
            memset(self, 0, 0x1fc);
            self->field11c = -1;
            self->field15c = -1;
        } else {
            memset(self, 0, 0x117);
        }
        self->field80 = value;
        self->field90 = &self->fieldb8;
        self->field94 = &self->fieldc8;
        self->field9c = -1;
        self->fieldb8 = -1;
        self->fieldd8 = -1;
    }
}
/* fzgx:end fn_1_23640 */

/* fzgx:begin fn_1_248C0 */
typedef struct Fn_1_248C0 {
    u32 unk_00;
    unsigned char pad04[0x471];
    signed char unk_475;
    unsigned char pad476[0x3d];
    unsigned char unk_4b3;
} Fn_1_248C0;

// Updates the collision state and reports whether the current flags trigger a response.
int fn_1_248C0(Fn_1_248C0 *self, int arg) {
    int result;
    int test;

    result = 0;
    if (self->unk_00 & 0x800) {
        if (self->unk_00 & 1) {
            result = 1;
        } else if (self->unk_00 & 0x10000) {
            result = 1;
        }
        if (!(self->unk_00 & 0x10000) && self->unk_4b3 == 0) {
            if (*(s16 *)&lbl_1_bss_960 == 9 && lbl_1_bss_9C == 5) {
            } else if (lbl_1_bss_9C == 6) {
            } else if (self->unk_475 != -1 && !(self->unk_00 & 0x04000200)) {
                fn_1_A2D84(0xA9072100);
            }
            self->unk_4b3 = 1;
        }
    } else {
        test = self->unk_00 & 0x80;
        if (test && self->unk_4b3 == 0 && !(self->unk_00 & 0x10000)) {
            if (self->unk_475 != -1 && !(self->unk_00 & 0x04000200)) {
                fn_1_A2D84(0xA9072200);
            }
            self->unk_4b3 = 1;
        }
        if ((self->unk_00 & 1) && test) {
            if ((self->unk_00 & 0x02810000) || arg) {
                result = 1;
            }
        }
    }
    if ((self->unk_00 & 0x40000000) && (self->unk_00 & 1)) {
        result = 1;
    }
    if (self->unk_00 & 0x10000000) {
        result = 0;
    }
    return result;
}
/* fzgx:end fn_1_248C0 */

/* fzgx:begin fn_1_24F10 */
typedef struct Fn_1_24F10 {
    int flags;
    unsigned char pad04[0x2c];
    f32 field30;
    unsigned char pad34[0x150];
    f32 field184;
    unsigned char pad188[0x8c];
    u16 field214;
    unsigned char pad216[0x0e];
    f32 field224;
    unsigned char pad228[0x284];
    f32 field4ac;
    unsigned char pad4b0[0xe3];
    u8 field593;
    unsigned char pad594[0x46];
    u16 field5da;
} Fn_1_24F10;

#pragma section code_type ".fzgxpool"
__declspec(section ".fzgxpool") static void fzgx_pool_prime1(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 52.0f;
    s = 0.0625f;
    s = 45.0f;
    s = 0.0f;
    s = 1.7000000476837158f;
    s = 1.0f;
    s = 0.10000000149011612f;
    s = 0.5f;
    d = 4503599627370496.0;
    s = 40.0f;
    s = 348.0f;
    s = 36.0f;
    s = 4.0f;
    s = 0.6000000238418579f;
    s = 5.0f;
    s = 0.05000000074505806f;
    s = 1000.0f;
    s = 8.0f;
}
static const u32 fzgx_pool_table2[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep2(void) { const u32 *volatile cp; cp = fzgx_pool_table2; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime3(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 216.0;
    d = 2.0;
    s = 0.25f;
    s = 0.07000000029802322f;
    s = 0.20000000298023224f;
}
static const u32 fzgx_pool_table4[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep4(void) { const u32 *volatile cp; cp = fzgx_pool_table4; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime5(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 1.834999918937683f;
}
static const u32 fzgx_pool_table6[1] = {0xAE147AE1};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep6(void) { const u32 *volatile cp; cp = fzgx_pool_table6; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime7(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 2.0f;
    s = 1.7999999523162842f;
    s = 1.399999976158142f;
    s = 1.5f;
    s = 1.2000000476837158f;
    s = 2.299999952316284f;
    s = 0.4000000059604645f;
    s = 3.200000047683716f;
    s = 0.15000000596046448f;
    s = -0.25f;
    s = 0.1599999964237213f;
    s = 0.11999999731779099f;
    s = 0.07999999821186066f;
    s = 0.44999998807907104f;
    s = 0.699999988079071f;
}
static const u32 fzgx_pool_table8[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep8(void) { const u32 *volatile cp; cp = fzgx_pool_table8; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime9(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.6000000238418579;
    s = 0.3100000023841858f;
    s = 0.029999999329447746f;
    s = 0.009999999776482582f;
    s = 700.0f;
    s = 1.7674999237060547f;
}
static const u32 fzgx_pool_table10[1] = {0xA3D70A3D};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep10(void) { const u32 *volatile cp; cp = fzgx_pool_table10; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime11(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.5699999928474426f;
}
static const u32 fzgx_pool_table12[4] = {0x00000000, 0x00000000, 0x00000000, 0x3F800000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep12(void) { const u32 *volatile cp; cp = fzgx_pool_table12; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime13(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = -0.10000000149011612f;
    s = 200.0f;
    s = 0.019999999552965164f;
    d = 0.009999999776482582;
    s = 0.03999999910593033f;
    s = 0.800000011920929f;
    d = 13.88888888888889;
    s = 13.88888931274414f;
}
static const u32 fzgx_pool_table14[1] = {0x34000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep14(void) { const u32 *volatile cp; cp = fzgx_pool_table14; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime15(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 800.0f;
    s = 0.949999988079071f;
    s = 2.200000047683716f;
    s = -0.5f;
    s = 0.0020000000949949026f;
    s = 0.0010000000474974513f;
    s = 0.30000001192092896f;
}
static const u32 fzgx_pool_table16[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep16(void) { const u32 *volatile cp; cp = fzgx_pool_table16; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime17(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.4;
    d = 0.1;
    s = 80.0f;
    s = 1700.0f;
    d = 90.0;
    s = 0.3333333432674408f;
    s = -5000.0f;
    s = 900.0f;
    s = -10000.0f;
    s = 10.0f;
    s = 100.0f;
    s = 400.0f;
    s = 0.9900000095367432f;
    s = 20.0f;
    s = 1.0099999904632568f;
}
#pragma section code_type ".text"
int fn_1_24F10(Fn_1_24F10 *self, f32 value) {
    f32 amount;
    f32 dist;
    int result;

    if (self->field214 != 0 || self->field593 != 0) {
        return 0;
    }

    amount = value * self->field30;
    if ((self->flags & 0x200) == 0 && amount > 20.0f) {
        amount = 20.0f;
    }

    if (amount > 1.01f * (f32)self->field5da) {
        amount = 1.01f * (f32)self->field5da;
    }

    self->field4ac = amount;
    dist = self->field184 - self->field4ac;
    self->field184 = dist;
    if (dist < 0.0f) {
        if ((self->flags & 0x10080) != 0) {
            result = 0;
        } else {
            result = 1;
            self->field593 = 0x3c;
        }
        self->flags |= 0x80;
        self->field184 = 0.0f;
        self->field224 = 0.0f;
        return result;
    }

    return 0;
}
/* fzgx:end fn_1_24F10 */

/* fzgx:begin fn_1_25004 */
typedef struct Fn_1_25004_Obj {
    u32 flags00;
    s16 field04;
    u8 pad06[0x8e];
    f32 field94;
    f32 field98;
    f32 field9c;
    f32 fielda0;
    f32 fielda4;
    f32 fielda8;
    u8 padac[0xd0];
    f32 field17c;
    u8 pad180[0x4];
    f32 field184;
    u8 pad188[0x9c];
    f32 field224;
    u8 pad228[0x24c];
    u8 field474;
    u8 pad475[0x117];
    u32 flags58c;
} Fn_1_25004_Obj;

typedef struct Fn_1_25004_Result {
    u8 pad390[0x390];
    u32 flags390;
} Fn_1_25004_Result;

#pragma opt_strength_reduction off
void fn_1_25004(Fn_1_25004_Obj *self) {
    Fn_1_25004_Result *result;
    f32 zero;

    result = (Fn_1_25004_Result *)fn_1_868C0((s8)self->field04);
    if ((self->flags58c & 0x10) == 0) {
        if ((s8)self->field474 != -1) {
            fn_1_F7338((s8)self->field474, 2, 0x1e);
        }
        zero = (0.0f);
        self->flags00 |= 0x800;
        self->flags00 |= 0x80;
        self->flags00 |= 0x800000;
        self->flags00 |= 0x40000000;
        self->flags58c |= 0x10;
        self->field184 = zero;
        self->field224 = zero;
        self->field94 = zero;
        self->field98 = zero;
        self->field9c = zero;
        self->fielda0 = zero;
        self->fielda4 = zero;
        self->fielda8 = zero;
        self->field17c = zero;
        self->flags58c &= ~0x80;
        result->flags390 &= ~0x200000;
        result->flags390 |= 0x1000000;
    }
}
#pragma opt_strength_reduction reset
/* fzgx:end fn_1_25004 */

/* fzgx:begin fn_1_250F8 */
typedef struct Fn_1_250F8 {
    u32 flags;
    u8 pad04[0x180];
    f32 field184;
    u8 pad188[0x88];
    u16 field210;
    u8 pad212[0x01];
    u8 field213;
    u8 pad214[0x03];
    u8 field217;
    u8 pad218[0x29A];
    u8 field4b2;
    u8 pad4b3[0xD9];
    u32 field58c;
} Fn_1_250F8;

void fn_1_250F8(Fn_1_250F8 *self) {
    u16 value;
    f32 add;
    f32 elapsed;
    u32 delta;

    if ((self->flags & 0x10000) == 0) {
        value = self->field210;
        add = lbl_1_rodata_85C * self->field184;
        elapsed = (f32)value + add;
        delta = ((u32)self->field213 * 60) / 60;
        self->field210 = (s32)elapsed;
        if (self->field217 == 0) {
            self->field210 += 25;
        }
        if (self->field4b2 == 0) {
            self->field210 += 25;
        }
        if ((self->field58c & 1) == 0) {
            self->field210 += 40;
        }
        if (self->flags & 0x80) {
            self->field210 += 25;
        }
        if (self->field210 > delta) {
            self->field210 -= delta;
        } else {
            self->field210 = 0;
        }
    }
    self->flags |= 0x10000;
}
/* fzgx:end fn_1_250F8 */

/* fzgx:begin fn_1_25870 */
typedef struct Fn_1_25870 {
    u32 flags;
    unsigned char pad04[0x1f4];
    f32 field1f8;
    f32 field1fc;
    unsigned char pad200[0x24];
    f32 field224;
    unsigned char pad228[0x1c];
    u32 field244;
    unsigned char pad248[0x58];
    u32 field2a0;
    unsigned char pad2a4[0x58];
    u32 field2fc;
    unsigned char pad300[0x58];
    u32 field358;
    unsigned char pad35c[0x11a];
    u8 field476;
    u8 field477;
} Fn_1_25870;

void fn_1_25870(Fn_1_25870 *self) {
    unsigned char *data = lbl_1_rodata_840;
    u32 flags;
    int trigger;

    if (self->field476 != 0) {
        self->field476--;
    }
    flags = self->flags;
    if ((flags & 0x2) == 0) {
        if (self->field224 > *(f32 *)(data + 0x18)) {
            if ((flags & 0x2000) != 0) {
                self->field244 &= ~4;
                self->field2a0 &= ~4;
                self->field2fc &= ~4;
                self->field358 &= ~4;
                self->field476 = self->field477;
            } else {
                trigger = 0;
                if ((flags & 0x1000) != 0 &&
                    __fabs(self->field1fc) > *(f64 *)(data + 0x1b8)) {
                    trigger = 1;
                }
                if ((self->flags & 0x8) != 0) {
                    trigger = 1;
                }
                if (trigger != 0) {
                    self->field244 |= 4;
                    self->field2a0 |= 4;
                    self->field2fc |= 4;
                    self->field358 |= 4;
                }
            }
        }
    } else {
        self->field244 &= ~4;
        self->field2a0 &= ~4;
        self->field2fc &= ~4;
        self->field358 &= ~4;
    }
    flags = self->flags;
    if ((flags & 0x4000) != 0 &&
        __fabs(self->field1fc) < *(f64 *)(data + 0x1b8)) {
        self->flags = flags & ~0x4000;
    }
    if (__fabs(self->field1f8) > *(f64 *)(data + 0x1c0)) {
        self->flags |= 0x4000;
    }
    if ((self->flags & 0x4000) == 0) {
        return;
    }
    self->field244 |= 0x10;
    self->field2a0 |= 0x10;
    self->field2fc |= 0x10;
    self->field358 |= 0x10;
}
/* fzgx:end fn_1_25870 */

/* fzgx:begin fn_1_28660 */
typedef struct Fn_1_28660 {
    int field00;
    short field04;
    unsigned char pad06[0x212];
    int field218;
    unsigned char pad21c[0x2e0];
    int field4fc;
    unsigned char pad500[0x8c];
    int field58c;
} Fn_1_28660;

void fn_1_28660(Fn_1_28660 *self) {
    int result;
    int mask;

    lbl_8006DAEC();

    mask = 0x88;
    if ((self->field58c & 0x2) == 0) {
        mask |= 0x10;
    }
    if ((self->field4fc & 0x00100000) == 0) {
        mask |= 0x2;
    }
    if ((self->field4fc & 0x00080000) == 0) {
        mask |= 0x20;
    }
    if ((self->field4fc & 0x00040000) == 0) {
        mask |= 0x40;
    }
    if ((self->field4fc & 0x00020000) == 0) {
        mask |= 0x80;
    }

    if ((self->field00 & 0x2) != 0) {
        result = 0;
    } else {
        result = fn_1_163BC((char *)self + 0x7c, (char *)self + 0x88,
            mask, fn_1_8C66C(self->field04));
    }

    if ((result & 0x8) != 0) {
        self->field00 |= 0x00600000;
        self->field218 |= 0x10000000;
    }
    if ((self->field4fc & 0x00100000) != 0 ||
        (result & 0x2) != 0) {
        if ((self->field00 & 0x80) == 0) {
            self->field58c |= 1;
            self->field218 |= 0x08000000;
        }
    }
    if ((self->field00 & 0x20) == 0) {
        if ((self->field4fc & 0x00040000) != 0 ||
            (result & 0x40) != 0) {
            self->field218 |= 0x20000000;
        }
    }
    if ((self->field4fc & 0x00080000) != 0 ||
        (result & 0x20) != 0) {
        self->field218 |= 0x80000000u;
    }
    if ((result & 0x10) != 0) {
        self->field218 |= 0x04000000;
    }
    if ((self->field4fc & 0x00020000) != 0 ||
        (result & 0x80) != 0) {
        self->field218 |= 0x02000000;
    }

    lbl_8006DB30();
}
/* fzgx:end fn_1_28660 */

/* fzgx:begin fn_1_2A2A4 */
typedef struct {
    u8 pad00[0xec];
    u8 field_ec[0xd0];
    u8 pad_1bc[0x1bc];
} Fn1_2A2A4Object;

extern void lbl_8006DAEC(void);
extern void lbl_8006DB30(void);

void fn_1_2A2A4(Fn1_2A2A4Object *self) {
    u8 local_14[12];
    u8 local_8[12];
    f32 value_1;
    f32 value_2;

    value_1 = lbl_1_rodata_84C;
    value_2 = lbl_1_rodata_854;
    lbl_8006E1F0(local_8, value_1, value_2, value_1);
    lbl_8006DAEC();
    fn_8006E978(local_14, local_8, self->pad_1bc);
    mathutil_mtxA_from_quat(local_14);
    lbl_8006DFC4(self->field_ec);
    lbl_8006DB74(self->field_ec);
    lbl_8006DB30();
}
/* fzgx:end fn_1_2A2A4 */

/* fzgx:begin fn_1_2A318 */
typedef struct Fn_1_2A318 {
    unsigned char pad000[0x184];
    f32 field184;
    unsigned char pad188[0x02];
    unsigned char field18a;
    unsigned char pad18b[0x85];
    u16 field210;
    unsigned char field212;
    unsigned char pad213[0x26f];
    unsigned char field482;
    unsigned char pad483[0x10f];
    unsigned char field592;
    unsigned char pad593[0x47];
    u16 field5da;
} Fn_1_2A318;

void fn_1_2A318(Fn_1_2A318 *self) {
    u16 value;
    f32 progress;

    self->field482++;
    self->field212++;
    self->field210 += self->field212 * (self->field18a ? 15 : 10);
    if (self->field592 == 0) {
        self->field592 = 1;
    }
    value = self->field5da;
    progress = self->field184;
    if (progress < value) {
        progress += lbl_1_rodata_B74[0];
        self->field184 = progress;
        if (progress > value) {
            self->field184 = self->field5da;
        }
    }
}
/* fzgx:end fn_1_2A318 */

/* fzgx:begin fn_1_2A3E4 */
typedef struct Fn_1_2A3E4 {
    u32 flags;
    unsigned char pad04[0x186];
    u8 active;
    unsigned char pad18b[0x85];
    u16 value210;
} Fn_1_2A3E4;

void fn_1_2A3E4(Fn_1_2A3E4 *self) {
    if (self->active != 0) {
        if (self->flags & 0x00200000) {
            self->value210 += 0x14;
        } else {
            self->value210 += 0xA;
        }
    }
}
/* fzgx:end fn_1_2A3E4 */

/* fzgx:begin fn_1_2A41C */
typedef struct Fn_1_2A41C {
    u32 flags;
    unsigned char pad04[0x190];
    u16 value194;
} Fn_1_2A41C;

#pragma section code_type ".fzgxpool"
__declspec(section ".fzgxpool") static void fzgx_pool_prime1(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 52.0f;
    s = 0.0625f;
    s = 45.0f;
    s = 0.0f;
    s = 1.7000000476837158f;
    s = 1.0f;
    s = 0.10000000149011612f;
    s = 0.5f;
    d = 4503599627370496.0;
    s = 40.0f;
    s = 348.0f;
    s = 36.0f;
    s = 4.0f;
    s = 0.6000000238418579f;
    s = 5.0f;
    s = 0.05000000074505806f;
    s = 1000.0f;
    s = 8.0f;
}
static const u32 fzgx_pool_table2[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep2(void) { const u32 *volatile cp; cp = fzgx_pool_table2; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime3(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 216.0;
    d = 2.0;
    s = 0.25f;
    s = 0.07000000029802322f;
    s = 0.20000000298023224f;
}
static const u32 fzgx_pool_table4[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep4(void) { const u32 *volatile cp; cp = fzgx_pool_table4; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime5(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 1.834999918937683f;
}
static const u32 fzgx_pool_table6[1] = {0xAE147AE1};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep6(void) { const u32 *volatile cp; cp = fzgx_pool_table6; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime7(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 2.0f;
    s = 1.7999999523162842f;
    s = 1.399999976158142f;
    s = 1.5f;
    s = 1.2000000476837158f;
    s = 2.299999952316284f;
    s = 0.4000000059604645f;
    s = 3.200000047683716f;
    s = 0.15000000596046448f;
    s = -0.25f;
    s = 0.1599999964237213f;
    s = 0.11999999731779099f;
    s = 0.07999999821186066f;
    s = 0.44999998807907104f;
    s = 0.699999988079071f;
}
static const u32 fzgx_pool_table8[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep8(void) { const u32 *volatile cp; cp = fzgx_pool_table8; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime9(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.6000000238418579;
    s = 0.3100000023841858f;
    s = 0.029999999329447746f;
    s = 0.009999999776482582f;
    s = 700.0f;
    s = 1.7674999237060547f;
}
static const u32 fzgx_pool_table10[1] = {0xA3D70A3D};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep10(void) { const u32 *volatile cp; cp = fzgx_pool_table10; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime11(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 0.5699999928474426f;
}
static const u32 fzgx_pool_table12[4] = {0x00000000, 0x00000000, 0x00000000, 0x3F800000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep12(void) { const u32 *volatile cp; cp = fzgx_pool_table12; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime13(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = -0.10000000149011612f;
    s = 200.0f;
    s = 0.019999999552965164f;
    d = 0.009999999776482582;
    s = 0.03999999910593033f;
    s = 0.800000011920929f;
    d = 13.88888888888889;
    s = 13.88888931274414f;
}
static const u32 fzgx_pool_table14[1] = {0x34000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep14(void) { const u32 *volatile cp; cp = fzgx_pool_table14; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime15(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    s = 800.0f;
    s = 0.949999988079071f;
    s = 2.200000047683716f;
    s = -0.5f;
    s = 0.0020000000949949026f;
    s = 0.0010000000474974513f;
    s = 0.30000001192092896f;
}
static const u32 fzgx_pool_table16[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep16(void) { const u32 *volatile cp; cp = fzgx_pool_table16; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime17(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.4;
    d = 0.1;
    s = 80.0f;
    s = 1700.0f;
    d = 90.0;
    s = 0.3333333432674408f;
    s = -5000.0f;
    s = 900.0f;
    s = -10000.0f;
    s = 10.0f;
    s = 100.0f;
    s = 400.0f;
    s = 0.9900000095367432f;
    s = 20.0f;
    s = 1.0099999904632568f;
    d = 1.0;
    d = 0.550000011920929;
    s = 3.4000000953674316f;
    s = 0.75f;
    s = 182.04444885253906f;
    s = -45.0f;
    d = 0.9259259259259259;
    d = 5.555555555555555;
    s = 1.1299999952316284f;
}
static const u32 fzgx_pool_table18[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep18(void) { const u32 *volatile cp; cp = fzgx_pool_table18; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime19(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 0.10000000149011612;
    d = 0.30000001192092896;
    d = 0.046296296296296294;
    s = 0.8999999761581421f;
    s = 1.1100000143051147f;
    d = 0.0023148148148148147;
    d = 0.5;
    d = 0.004629629629629629;
    d = 0.023148148148148147;
    s = 2000.0f;
    s = 500.0f;
    d = 0.2;
    s = 0.6399999856948853f;
    s = 0.3499999940395355f;
    d = 1.8518518518518519;
    d = 3.4000000953674316;
    d = 1.7000000476837158;
    d = 3.0;
    d = 1.5;
    s = -0.4000000059604645f;
}
static const u32 fzgx_pool_table20[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep20(void) { const u32 *volatile cp; cp = fzgx_pool_table20; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime21(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 3.240740740740741;
    s = -1.0f;
    s = 9.999999747378752e-05f;
    s = 0.014000000432133675f;
    s = 9.0f;
    s = 60.0f;
    s = 3.0f;
    s = 0.1666666716337204f;
    s = 1200.0f;
    s = 1600.0f;
}
static const u32 fzgx_pool_table22[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep22(void) { const u32 *volatile cp; cp = fzgx_pool_table22; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime23(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 1000.0;
    d = 0.699999988079071;
    d = 1.1920928955078125e-07;
    s = 0.003000000026077032f;
    s = 0.125f;
    s = -2000.0f;
    s = 600.0f;
    s = 6.0f;
    s = 300.0f;
    s = 1.1111111640930176f;
    s = 10000.0f;
    s = -3.0f;
    s = 10430.3779296875f;
    d = 0.0;
    s = 0.9919999837875366f;
    s = 0.00800000037997961f;
    s = 50.0f;
    s = 15.0f;
    s = 4000.0f;
}
static const u32 fzgx_pool_table24[1] = {0x00000000};  /* fzgx-allow: A1 retail pool bytes */
__declspec(section ".fzgxpool") static void fzgx_pool_keep24(void) { const u32 *volatile cp; cp = fzgx_pool_table24; }  /* fzgx-allow: S2 pool primer sink */
__declspec(section ".fzgxpool") static void fzgx_pool_prime25(void) {
    volatile f32 s; volatile f64 d;  /* fzgx-allow: S2 pool primer sinks */
    d = 3.6;
    s = 1.2999999523162842f;
    s = 0.009000000543892384f;
    d = 9990.0;
    s = 46.25f;
    s = 1100.0f;
    s = 120.0f;
    s = -50.0f;
    d = 4503601774854144.0;
    s = 30.0f;
    s = -0.20000000298023224f;
    s = 90.0f;
    s = 0.006000000052154064f;
    d = 4.62962962962963;
    s = -5.0f;
    s = 4.5f;
    s = 3640.0f;
    s = 2.5f;
    s = -0.30000001192092896f;
    s = 5.999999848427251e-05f;
    s = 65536.0f;
    s = 6.666666507720947f;
    s = 3.5f;
    s = 0.000244140625f;
}
#pragma section code_type ".text"
f32 fn_1_2A41C(Fn_1_2A41C *self, int arg) {
    f32 result;
    u32 flags;
    f32 delta;
    f32 half;
    f32 scaled;
    f32 t;

    flags = self->flags;
    result = 1.0f;
    if ((flags & 0x20008) != 0) {
        if ((flags & 0x200) != 0) {
            if ((flags & 8) != 0) {
                result *= 3.5f;
            } else {
                result *= 4.0f;
            }
        } else {
            delta = (f32)self->value194;
            delta *= 0.000244140625f;
            half = 0.5f;
            scaled = half * delta;
            t = half + scaled;
            if (arg != 0) {
                if ((flags & 8) != 0) {
                    result *= 5.0f * t;
                } else {
                    result *= 6.0f;
                }
            } else {
                if ((flags & 8) != 0) {
                    result *= 3.0f * t;
                } else {
                    result *= 2.0f;
                }
            }
        }
    } else {
        if ((flags & 0x200) != 0) {
            result *= 0.8f;
        }
    }
    return result;
}
/* fzgx:end fn_1_2A41C */

/* fzgx:begin fn_1_2A638 */
typedef struct Fn_1_2A638 {
    unsigned char pad00[0x08];
    f32 field08;
    f32 field0c;
    f32 field10;
    unsigned char pad14[0x30];
    f32 field44;
    f32 field48;
} Fn_1_2A638;

void fn_1_2A638(void *arg0, Fn_1_2A638 *self) {
    lbl_8006E1D8((char *)self + 0x14, self->field08,
        self->field0c + self->field44 - self->field48, self->field10);
}
/* fzgx:end fn_1_2A638 */

/* fzgx:begin fn_1_2A678 */
typedef struct Fn_1_2A678_Values {
    int x;
    int y;
    int z;
} Fn_1_2A678_Values;

typedef struct Fn_1_2A678_Source {
    unsigned char pad00[0x7c];
    Fn_1_2A678_Values values;
} Fn_1_2A678_Source;

typedef struct Fn_1_2A678_Dest {
    unsigned char pad00[0xc];
    Fn_1_2A678_Values values;
} Fn_1_2A678_Dest;

void fn_1_2A678(Fn_1_2A678_Source *self, Fn_1_2A678_Dest *dest) {
    dest->values = self->values;
}
/* fzgx:end fn_1_2A678 */

/* fzgx:begin fn_1_2B478 */
#include "types.h"

struct fn_1_2B478_Arg0 {
    u8 pad_0[0x1C8];
    f32 unk_1C8;
    u8 pad_1CC[0x2D0];
    u32 unk_49C;
};
struct fn_1_2B478_lbl_801A6D00 {
    u32 unk_0;
};
struct fn_1_2B478_lbl_801A66CC {
    u32 unk_0;
};

f32 fn_1_2B478(void *arg0) {
    void *temp_r5;

    temp_r5 = (void *)(*(void **)((u8 *)(arg0) + 1180));
    if (!((*(s32 *)((u8 *)(temp_r5) + 124)) & 0x01800000) || ((*(f32 *)((u8 *)(arg0) + 456)) <= (*(f32 *)((u8 *)(&(*(f32 *)&lbl_1_rodata_84C)) + 0)))) {
        return *(f32 *)((u8 *)(&(*(f32 *)&lbl_1_rodata_854)) + 0);
    }
    (*(f32 *)((u8 *)((*(struct fn_1_2B478_lbl_801A66CC *)&lbl_801A66CC).unk_0) + 212)) = (f32) -(*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 8));
    (*(f32 *)((u8 *)((*(struct fn_1_2B478_lbl_801A66CC *)&lbl_801A66CC).unk_0) + 216)) = (f32) -(*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 24));
    (*(f32 *)((u8 *)((*(struct fn_1_2B478_lbl_801A66CC *)&lbl_801A66CC).unk_0) + 220)) = (f32) -(*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 40));
    return lbl_8006D6FC((void *)((*(struct fn_1_2B478_lbl_801A66CC *)&lbl_801A66CC).unk_0 + 0xD4), (void *)((u8 *)(temp_r5) + 0x50));
}
/* fzgx:end fn_1_2B478 */

/* fzgx:begin fn_1_2C688 noprologue */
#include "types.h"

extern u32 memset(u32, u32, u32);

u32 fn_1_2C688(u32 arg0, u32 arg1, u32 arg2) {
    u32 v1;
    s32 v0;
    u32 v2;
    u32 v3;
    u32 v4;
    u32 v5;
    u32 v6;
    u32 t0;
    u32 t1;
    u32 t2;
    v0 = 0;
    v1 = arg0;
    do {
    v2 = *(u32 *)((u8 *)v1 + 1160);
    v3 = arg0;
    v4 = arg1;
    v5 = arg2;
    if (v2 != 0) {
    v3 = v2;
    v4 = 0;
    v5 = 192;
    t0 = memset(v3, v4, v5);
    v3 = t0;
    v3 = (v2 + 8);
    *(u32 *)((u8 *)v2 + 0) = v3;
    *(u32 *)((u8 *)v2 + 4) = (v2 + 100);
    }
    v0++;
    v1 += 4;
    } while ((s32)v0 < 4);
    v3 = *(u32 *)((u8 *)arg0 + 1176);
    if (v3 != 0) {
    v4 = 0;
    v5 = 404;
    t1 = memset(v3, v4, v5);
    v3 = t1;
    }
    v6 = *(u32 *)((u8 *)arg0 + 1180);
    if (v6 != 0) {
    v3 = v6;
    v4 = 0;
    v5 = 279;
    t2 = memset(v3, v4, v5);
    v3 = t2;
    v4 = (v6 + 184);
    *(u32 *)((u8 *)v6 + 128) = 0;
    v3 = (v6 + 200);
    *(u32 *)((u8 *)v6 + 144) = v4;
    *(u32 *)((u8 *)v6 + 148) = v3;
    *(u32 *)((u8 *)v6 + 156) = -1;
    *(u32 *)((u8 *)v6 + 184) = -1;
    *(u32 *)((u8 *)v6 + 216) = -1;
    }
    return v3;
}
/* fzgx:end fn_1_2C688 */

/* fzgx:begin fn_1_2C768 */
void fn_1_2C768(u32 *arg0) {
    if (lbl_1_bss_3C2A[0] != 0x29 || (lbl_1_bss_3C30.unk_0 & 0x800)) {
        return;
    }
    if (lbl_1_bss_3C30.unk_5 == 2 && *arg0 != lbl_1_bss_3C30.unk_1474) {
        lbl_1_bss_3C30.unk_5 = 6;
    }
    *arg0 += 1;
}
/* fzgx:end fn_1_2C768 */

/* fzgx:begin fn_1_2C7C4 */
void fn_1_2C7C4(u8 *value, const u8 *target, int step) {
    if (value[0] != target[0]) {
        if (value[0] > target[0]) {
            if (value[0] > target[0] + step) {
                value[0] -= step;
            } else {
                value[0] = target[0];
            }
        } else {
            if (value[0] < target[0] - step) {
                value[0] += step;
            } else {
                value[0] = target[0];
            }
        }
    }
    if (value[1] != target[1]) {
        if (value[1] > target[1]) {
            if (value[1] > target[1] + step) {
                value[1] -= step;
            } else {
                value[1] = target[1];
            }
        } else {
            if (value[1] < target[1] - step) {
                value[1] += step;
            } else {
                value[1] = target[1];
            }
        }
    }
    if (value[2] != target[2]) {
        if (value[2] > target[2]) {
            if (value[2] > target[2] + step) {
                value[2] -= step;
            } else {
                value[2] = target[2];
            }
        } else {
            if (value[2] < target[2] - step) {
                value[2] += step;
            } else {
                value[2] = target[2];
            }
        }
    }
    if (value[3] != target[3]) {
        if (value[3] > target[3]) {
            if (value[3] > target[3] + step) {
                value[3] -= step;
            } else {
                value[3] = target[3];
            }
        } else {
            if (value[3] < target[3] - step) {
                value[3] += step;
            } else {
                value[3] = target[3];
            }
        }
    }
}
/* fzgx:end fn_1_2C7C4 */

/* fzgx:begin fn_1_2C908 noprologue */
#include "types.h"

struct fn_1_2C908_lbl_1_bss_3C00 {
    u8 pad_0[0x30];
    u32 unk_30;
    u8 pad_34[0x14B4];
    u16 unk_14E8;
    u8 pad_14EA[0x2];
    u16 unk_14EC;
    u8 pad_14EE[0x6];
    u8 unk_14F4;
    u8 pad_14F5[0x3];
    u32 unk_14F8;
    u16 unk_14FC;
};

extern int fn_1_4C10(void);
extern struct fn_1_2C908_lbl_1_bss_3C00 lbl_1_bss_3C00;
extern u32 fn_1_4060(void);
extern void fn_1_EB080(int);

#pragma opt_lifetimes off
u32 fn_1_2C908(void) {
    struct fn_1_2C908_lbl_1_bss_3C00 *p_lbl_1_bss_3C00;
    u32 v0;
    u32 v1;
    p_lbl_1_bss_3C00 = (struct fn_1_2C908_lbl_1_bss_3C00 *)&lbl_1_bss_3C00;
    v0 = fn_1_4C10();
    if ((s32)v0 == 0) {
    v0 = p_lbl_1_bss_3C00->unk_30;
    v1 = (v0 | 4096);
    p_lbl_1_bss_3C00->unk_14E8 = 42;
    p_lbl_1_bss_3C00->unk_30 = v1;
    p_lbl_1_bss_3C00->unk_14EC = 0;
    p_lbl_1_bss_3C00->unk_14F4 = (p_lbl_1_bss_3C00->unk_14F4 | 1);
    p_lbl_1_bss_3C00->unk_14F8 = 0;
    p_lbl_1_bss_3C00->unk_14FC = 0;
    fn_1_EB080(4);
    v0 = fn_1_4060();
    }
    return v0;
}
#pragma opt_lifetimes reset
/* fzgx:end fn_1_2C908 */

/* fzgx:begin fn_1_3FCD4 */
void fn_1_3FCD4(u32 mask) {
    if (mask == 0) {
        lbl_1_data_5B80 = 0xffffffff;
    } else {
        lbl_1_data_5B80 &= ~mask;
    }
}
/* fzgx:end fn_1_3FCD4 */
