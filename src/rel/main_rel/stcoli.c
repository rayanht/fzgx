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

/* fzgx:begin fn_1_14F04 */
u8 *fn_1_14F04(void) {
    return lbl_801A66CC + 0x1b0;
}
/* fzgx:end fn_1_14F04 */

/* fzgx:begin fn_1_17B5C */
extern f32 lbl_1_rodata_6D0;

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

/* fzgx:begin fn_1_17C6C noprologue */
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

extern u32 lbl_1_bss_3BE0;
extern s16 fn_1_7B054(int);

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

        if (!(*(Root **)&lbl_1_bss_3BE0)->slots[current].entry->active) {
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

/* fzgx:begin fn_1_250F8 */
extern const f32 lbl_1_rodata_85C;

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
extern const f32 lbl_1_rodata_84C;
extern const f32 lbl_1_rodata_854;

typedef struct {
    u8 pad00[0xec];
    u8 field_ec[0xd0];
    u8 pad_1bc[0x1bc];
} Fn1_2A2A4Object;

extern void lbl_8006E1F0(void *, f32, f32, f32);
extern void lbl_8006DAEC(void);
extern void fn_8006E978(void *, void *, void *);
extern void mathutil_mtxA_from_quat(void *);
extern void lbl_8006DFC4(void *);
extern void lbl_8006DB74(void *);
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
extern f64 lbl_1_rodata_860[22];
extern f32 lbl_1_rodata_B74[25];

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

/* fzgx:begin fn_1_2B478 noprologue */
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
extern f32 lbl_1_rodata_84C;
extern f32 lbl_1_rodata_854;
extern struct fn_1_2B478_lbl_801A66CC lbl_801A66CC;
extern struct fn_1_2B478_lbl_801A6D00 lbl_801A6D00;
extern f32 lbl_8006D6FC(void *, void *);


f32 fn_1_2B478(void *arg0) {
    void *temp_r5;

    temp_r5 = (void *)(*(void **)((u8 *)(arg0) + 1180));
    if (!((*(s32 *)((u8 *)(temp_r5) + 124)) & 0x01800000) || ((*(f32 *)((u8 *)(arg0) + 456)) <= (*(f32 *)((u8 *)(&lbl_1_rodata_84C) + 0)))) {
        return *(f32 *)((u8 *)(&lbl_1_rodata_854) + 0);
    }
    (*(f32 *)((u8 *)(lbl_801A66CC.unk_0) + 212)) = (f32) -(*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 8));
    (*(f32 *)((u8 *)(lbl_801A66CC.unk_0) + 216)) = (f32) -(*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 24));
    (*(f32 *)((u8 *)(lbl_801A66CC.unk_0) + 220)) = (f32) -(*(f32 *)((u8 *)(lbl_801A6D00.unk_0) + 40));
    return lbl_8006D6FC((void *)(lbl_801A66CC.unk_0 + 0xD4), (void *)((u8 *)(temp_r5) + 0x50));
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

/* fzgx:begin fn_1_3FCD4 */
void fn_1_3FCD4(u32 mask) {
    if (mask == 0) {
        lbl_1_data_5B80 = 0xffffffff;
    } else {
        lbl_1_data_5B80 &= ~mask;
    }
}
/* fzgx:end fn_1_3FCD4 */
