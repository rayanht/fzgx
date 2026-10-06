#include "types.h"

typedef struct Fn8004CAC8_Obj Fn8004CAC8_Obj;

typedef struct Fn8004CAC8_Vtbl {
    u8 pad_0[0xC];
    void (*destroy)(Fn8004CAC8_Obj *obj);
    u8 pad_10[0x4];
    void (*stop)(Fn8004CAC8_Obj *obj);
} Fn8004CAC8_Vtbl;

struct Fn8004CAC8_Obj {
    Fn8004CAC8_Vtbl *vtbl;
};

typedef struct Fn8004CAC8_Ply {
    s8 used;
    s8 unk_1;
    s8 mode;
    s8 count;
    void *unk_4;
    void *unk_8;
    void *unk_C;
    Fn8004CAC8_Obj *unk_10;
    Fn8004CAC8_Obj *unk_14;
    Fn8004CAC8_Obj *unk_18[4];
    u8 pad_28[0x4C];
    void *unk_74;
    Fn8004CAC8_Obj *unk_78[2];
    Fn8004CAC8_Obj *unk_80[4];
    u8 pad_90[0x4];
    void *unk_94;
    u8 pad_98[0x10];
    u8 unk_A8;
    u8 pad_A9[0x17];
} Fn8004CAC8_Ply;

extern char lbl_80091014[];
extern char lbl_80090FC4[];
extern void (*lbl_8017E58C[2])(void *);
extern void fn_800474E4(const char *msg);
extern void fn_8004B0EC(void *);
extern void fn_80046738(void);
extern void fn_80046718(void);
extern void fn_80056CD0(void *);
extern void fn_8004EEC4(void *, s32);
extern void fn_8004EEA4(void *, s32);
extern void fn_800420F4(void *);
extern void fn_80046510(void *);
extern void fn_8004EEE4(void *);
extern void fn_800421CC(void *);
extern void fn_8004AC4C(void *, s32, s32);
extern void fn_8004B1DC(void *);
extern void fn_80057114(void *);
extern void fn_800466D4(void *);
extern void *memset(void *, int, u32);

static inline void fn_8004CAC8_stop(Fn8004CAC8_Ply *ply) {
    Fn8004CAC8_Obj *obj;

    if (ply == NULL) {
        fn_800474E4(lbl_80090FC4);
        return;
    }
    if (ply->unk_8 != NULL) {
        fn_8004B0EC(ply->unk_8);
    }
    fn_80046738();
    if (ply->mode == 4) {
        fn_80056CD0(ply->unk_94);
        if (ply->unk_14 != NULL) {
            ply->unk_14->vtbl->stop(ply->unk_14);
        }
    }
    fn_80046738();
    fn_8004EEC4(ply->unk_C, 0);
    fn_8004EEA4(ply->unk_C, 0);
    fn_800420F4(ply->unk_4);
    if (ply->mode == 2 && (obj = ply->unk_14) != NULL) {
        ply->unk_14 = NULL;
        obj->vtbl->destroy(obj);
    }
    if (ply->unk_74 != NULL) {
        fn_80046510(ply->unk_74);
    }
    ply->unk_14 = NULL;
    ply->unk_1 = 0;
    ply->unk_A8 = 0;
    fn_80046718();
    fn_80046718();
}

void fn_8004CAC8(Fn8004CAC8_Ply *ply) {
    Fn8004CAC8_Obj *obj;
    void *ptr;
    s32 i;

    if (ply == NULL) {
        fn_800474E4(lbl_80091014);
        return;
    }
    if (lbl_8017E58C[0] != NULL) {
        lbl_8017E58C[0](ply);
    }
    if (ply->used == 1) {
        fn_8004CAC8_stop(ply);
    }
    if ((ptr = ply->unk_C) != NULL) {
        ply->unk_C = NULL;
        fn_8004EEE4(ptr);
    }
    if ((ptr = ply->unk_4) != NULL) {
        ply->unk_4 = NULL;
        fn_800421CC(ptr);
    }
    if ((ptr = ply->unk_8) != NULL) {
        ply->unk_8 = NULL;
        fn_8004AC4C(ptr, 0, 0);
        fn_8004B1DC(ptr);
    }
    if ((ptr = ply->unk_94) != NULL) {
        ply->unk_94 = NULL;
        fn_80057114(ptr);
    }
    fn_80046738();
    if ((obj = ply->unk_10) != NULL) {
        ply->unk_10 = NULL;
        obj->vtbl->destroy(obj);
    }
    for (i = 0; i < ply->count; i++) {
        if ((obj = ply->unk_18[i]) != NULL) {
            ply->unk_18[i] = NULL;
            obj->vtbl->destroy(obj);
        }
        if ((obj = ply->unk_78[i]) != NULL) {
            ply->unk_78[i] = NULL;
            obj->vtbl->destroy(obj);
        }
        if ((obj = ply->unk_80[i]) != NULL) {
            ply->unk_80[i] = NULL;
            obj->vtbl->destroy(obj);
        }
    }
    if ((ptr = ply->unk_74) != NULL) {
        ply->unk_74 = NULL;
        fn_800466D4(ptr);
    }
    memset(ply, 0, sizeof(Fn8004CAC8_Ply));
    ply->used = 0;
    fn_80046718();
}
