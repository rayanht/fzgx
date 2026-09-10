#include "types.h"

extern u32 ADXT_Stop(u32);
extern u32 fn_8004EBB4(void);
extern u32 fn_8004EBD4(void);
extern u32 fn_800541EC(u32);
extern u32 fn_800542C8(u32);
extern u32 fn_800545B0(void);

u32 fn_80051DC4(u32 arg0) {
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;
    u32 t1, t2, t3, t4, t5;
    ADXT_Stop(arg0);
    v0 = *(u32 *)((u8 *)arg0 + 4);
    v1 = *(u32 *)((u8 *)v0 + 4);
    v2 = *(u32 *)((u8 *)v1 + 176);
    v3 = v0;
    if (v2 != 0) {
    t1 = fn_8004EBD4();
    v3 = t1;
    v3 = v2;
    t2 = fn_800541EC(v3);
    v3 = t2;
    v3 = v2;
    t3 = fn_800542C8(v3);
    v3 = t3;
    *(u32 *)((u8 *)v1 + 176) = 0;
    t4 = fn_8004EBB4();
    v3 = t4;
    t5 = fn_800545B0();
    v3 = t5;
    }
    return v3;
}
