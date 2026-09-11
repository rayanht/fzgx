#include "types.h"

extern s32 lbl_801A6410;
extern char lbl_80094E48[54];
extern char lbl_80094E80[57];

extern void OSReport(const char *, ...);
extern u32 OSGetArenaLo(void);
extern u32 OSGetArenaHi(void);
extern u32 fn_80008EC8(u32, u32, u32);
extern void OSSetArenaLo(u32);
extern void fn_80008F60(u32, u32);
extern void fn_80008E84(void);
extern void fn_80008E5C(u32, u32);

void fn_80079EF0(u32 arg) {
    u32 lo;
    struct { u32 value; } hi;
    u32 masked;

    if (lbl_801A6410 == -1) {
        OSReport(lbl_80094E48);
        OSReport(lbl_80094E80);
        lo = OSGetArenaLo();
        hi.value = OSGetArenaHi();
        lo = fn_80008EC8(lo, hi.value, 1);
        OSSetArenaLo(lo);
        lo = (lo + 0x1f) & ~0x1fu;
        masked = hi.value & ~0x1fu;
        fn_80008F60(lo, masked);
        fn_80008E84();
        OSSetArenaLo(masked);
    }
    fn_80008E5C(lbl_801A6410, arg);
}
