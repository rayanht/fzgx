#include "types.h"

typedef struct Fn80025854Src {
    s32 *unk_0;
    s32 *unk_4;
    s32 *unk_8;
} Fn80025854Src;

typedef struct Fn80025854Elem {
    s32 unk_0;
    s32 unk_4;
} Fn80025854Elem;

typedef struct Fn80025854Args {
    u32 unk_0;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
    s32 *unk_30;
    s32 *unk_34;
    s32 *unk_38;
} Fn80025854Args;

void fn_80025854(Fn80025854Src *arg0, Fn80025854Args *arg1) {
    Fn80025854Elem *d;
    Fn80025854Elem *e;
    Fn80025854Elem *f;
    Fn80025854Elem *a;
    Fn80025854Elem *b;
    Fn80025854Elem *c;
    s32 x;
    s32 y;
    s32 z;
    s32 i;

    a = (Fn80025854Elem *)arg0->unk_0;
    b = (Fn80025854Elem *)arg0->unk_4;
    c = (Fn80025854Elem *)arg0->unk_8;
    d = (Fn80025854Elem *)((u8 *)arg1->unk_30 + arg1->unk_C * 0x280);
    e = (Fn80025854Elem *)((u8 *)arg1->unk_34 + arg1->unk_10 * 0x280);
    f = (Fn80025854Elem *)((u8 *)arg1->unk_38 + arg1->unk_14 * 0x280);

    for (i = 0; i < 80; i++) {
        x = d->unk_0;
        y = e->unk_0;
        z = f->unk_0;
        d->unk_0 = a->unk_0 + ((x * arg1->unk_18) >> 7);
        e->unk_0 = b->unk_0 + ((y * arg1->unk_1C) >> 7);
        f->unk_0 = c->unk_0 + ((z * arg1->unk_20) >> 7);
        a->unk_0 = (x * arg1->unk_24) >> 7;
        b->unk_0 = (y * arg1->unk_28) >> 7;
        c->unk_0 = (z * arg1->unk_2C) >> 7;

        x = d->unk_4;
        y = e->unk_4;
        z = f->unk_4;
        d->unk_4 = a->unk_4 + ((x * arg1->unk_18) >> 7);
        e->unk_4 = b->unk_4 + ((y * arg1->unk_1C) >> 7);
        f->unk_4 = c->unk_4 + ((z * arg1->unk_20) >> 7);
        a->unk_4 = (x * arg1->unk_24) >> 7;
        b->unk_4 = (y * arg1->unk_28) >> 7;
        c->unk_4 = (z * arg1->unk_2C) >> 7;

        a++;
        b++;
        c++;
        d++;
        e++;
        f++;
    }

    arg1->unk_C = (arg1->unk_C + 1) % arg1->unk_0;
    arg1->unk_10 = (arg1->unk_10 + 1) % arg1->unk_4;
    arg1->unk_14 = (arg1->unk_14 + 1) % arg1->unk_8;
}
