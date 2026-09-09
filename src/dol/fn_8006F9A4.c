#include "types.h"

extern u32 fn_8006E5FC(void *);
extern u32 fn_8006EB4C(void *, void *, void *, f32);
extern void mathutil_mtxA_from_quat(void *);
extern u32 lbl_8006DC34(u32);
extern void lbl_8006DBAC(void *);

void fn_8006F9A4(f32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    struct { u32 a[4]; } loc_28;
    struct { u32 a[4]; } loc_18;
    struct { u32 a[4]; } loc_8;

    lbl_8006DBAC((void *)arg1);
    fn_8006E5FC((void *)&loc_28);
    lbl_8006DBAC((void *)arg2);
    fn_8006E5FC((void *)&loc_18);
    fn_8006EB4C((void *)&loc_8, (void *)&loc_28, (void *)&loc_18, arg0);
    mathutil_mtxA_from_quat((void *)&loc_8);
    lbl_8006DC34(arg3);
}
