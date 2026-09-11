#include "types.h"

typedef struct fn_80041BF8_Obj fn_80041BF8_Obj;
struct fn_80041BF8_Obj {
    void **vtable;
};

struct fn_80041BF8_Arg0 {
    u8 pad_0[0x1];
    u8 unk_1;
    u8 pad_2[0x1];
    s8 unk_3;
    fn_80041BF8_Obj *unk_4;
    fn_80041BF8_Obj *unk_8;
    fn_80041BF8_Obj *unk_C;
    u8 pad_10[0x4];
    void *unk_14;
    s32 unk_18;
    u8 pad_1C[0x18];
    s32 unk_34;
    u8 pad_38[0x4];
    s32 unk_3C;
    s32 unk_40;
    u8 pad_44[0x4];
    void (*unk_48)(u32);
    u32 unk_4C;
};

struct fn_8004550C_Arg {
    u8 pad_0[0x4];
};

struct fn_80045514_Arg {
    u8 pad_0[0x4];
};

extern int fn_8004559C(void *);
extern s32 fn_8004550C(struct fn_8004550C_Arg *);
extern u32 fn_80045514(struct fn_80045514_Arg *);
extern void fn_800453A4(void *, void *, s32);
extern void fn_8004538C(void *);

void fn_80041BF8(struct fn_80041BF8_Arg0 *arg0) {
    fn_80041BF8_Obj *obj4;
    fn_80041BF8_Obj *obj8;
    s32 s;
    s32 t;
    s32 n;

    t = arg0->unk_3C;
    obj4 = arg0->unk_4;
    obj8 = arg0->unk_8;
    if (t >= 0 && arg0->unk_40 >= t) {
        if (arg0->unk_48 != NULL) {
            arg0->unk_48(arg0->unk_4C);
        }
    }
    if (arg0->unk_3 == 1) {
        if (((s32 (*)(fn_80041BF8_Obj *, s32))obj8->vtable[9])(obj8, 1) == 0) {
            arg0->unk_1 = 3;
            return;
        }
    }
    ((u32 (*)(fn_80041BF8_Obj *, s32, u32, void *))obj8->vtable[6])(obj8, 1, 0x7FFFFFFF, &arg0->unk_14);
    if (fn_8004559C(obj4) == 0 && arg0->unk_18 >= 2 && (u16)*(s16 *)arg0->unk_14 == 0x8001) {
        arg0->unk_1 = 3;
        ((u32 (*)(fn_80041BF8_Obj *, s32, void *))obj8->vtable[7])(obj8, 1, &arg0->unk_14);
        return;
    }
    if (arg0->unk_34 >= fn_8004550C((struct fn_8004550C_Arg *)arg0->unk_4)) {
        arg0->unk_1 = 3;
        ((u32 (*)(fn_80041BF8_Obj *, s32, void *))obj8->vtable[7])(obj8, 1, &arg0->unk_14);
        return;
    }
    s = fn_80045514((struct fn_80045514_Arg *)arg0->unk_4);
    {
        fn_80041BF8_Obj *objC = arg0->unk_C;
        n = ((s32 (*)(fn_80041BF8_Obj *, s32))objC->vtable[9])(objC, 0);
    }
    if (n / 2 < s) {
        ((u32 (*)(fn_80041BF8_Obj *, s32, void *))obj8->vtable[7])(obj8, 1, &arg0->unk_14);
        return;
    }
    if (fn_8004559C(obj4) == 0xA) {
        ((u32 (*)(fn_80041BF8_Obj *, s32, void *))obj8->vtable[7])(obj8, 1, &arg0->unk_14);
    }
    fn_800453A4(obj4, arg0->unk_14, arg0->unk_18);
    fn_8004538C(obj4);
}
