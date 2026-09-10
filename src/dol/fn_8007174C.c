#include "types.h"

extern u32 OSPanic(u32, ...);
extern u32 sprintf(void *, ...);
extern u32 lbl_8015ABFC[];

void fn_8007174C(u32 arg0, u32 arg1) {
    struct { u32 a[258]; } loc_8;
    /* frame */
    sprintf(&loc_8, arg0, arg1);
    OSPanic((u32)&lbl_8015ABFC, 498, &loc_8);
}
