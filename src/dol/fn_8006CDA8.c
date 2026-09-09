#include "types.h"

typedef u32 (*fn_8006CDA8_Fn0)(void);

extern u32 GXLoadPosMtxImm(u32, u32);
extern u32 fn_8006CE44(void);
extern u32 lbl_801A6CAC;
extern u32 lbl_801A6D00;
extern void lbl_8006D758(void);

void fn_8006CDA8(void) {
    lbl_8006D758();
    GXLoadPosMtxImm(lbl_801A6D00, 0);
    if (lbl_801A6CAC != 0) {
        ((fn_8006CDA8_Fn0)lbl_801A6CAC)();
    }
    lbl_8006D758();
    GXLoadPosMtxImm(lbl_801A6D00, 0);
    fn_8006CE44();
}
