#include "types.h"

extern u32 fn_80045D3C(u32);
extern u32 memset(u32, u32, u32);
extern void fn_80046718(void);
extern void fn_80046738(void);

void fn_800421CC(u32 arg0) {
    u32 v0;
    u32 t0, t2;
    v0 = arg0;
    if (arg0 != 0) {
    v0 = *(u32 *)((u8 *)arg0 + 4);
    if (v0 != 0) {
    *(u32 *)((u8 *)arg0 + 4) = 0;
    t0 = fn_80045D3C(v0);
    v0 = t0;
    }
    fn_80046738();
    v0 = arg0;
    t2 = memset(v0, 0, 156);
    v0 = t2;
    fn_80046718();
    }
}
