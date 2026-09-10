#include "types.h"

extern u32 fn_800415AC(void *);
extern u32 fn_80041578(void *);
extern u32 fn_80041554(void *);
extern u32 fn_80041434(void *);
extern u32 fn_800416D4(void *, u32);
extern void fn_800416DC(void *, u32);
extern void fn_800416CC(void *, u32);
extern void fn_800416F0(void *, u32);
extern void fn_8004DE70(void);
extern void fn_800416E4(void *, void (*)(void), void *);

struct fn_8004DFF0_Arg0 {
    u8 pad_0[4];
    void *unk_4;
    u8 pad_8[0x84];
    u32 unk_8C;
    u32 unk_90;
};

void fn_8004DFF0(void *arg0) {
    struct fn_8004DFF0_Arg0 *p = arg0;
    void *obj;
    u32 value_1;
    u32 value_2;
    u32 value_3;
    u32 diff;

    obj = p->unk_4;
    value_1 = fn_800415AC(obj);
    value_2 = fn_80041578(obj);
    value_3 = fn_80041554(obj);
    fn_80041434(obj);
    fn_800416D4(obj, 0);
    diff = value_3 - value_1;
    p->unk_90 = diff;
    fn_800416DC(obj, diff);
    fn_800416CC(obj, value_2);
    fn_800416F0(obj, value_1);
    fn_800416E4(obj, fn_8004DE70, p);
}
