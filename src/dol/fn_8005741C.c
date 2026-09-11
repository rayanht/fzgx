#include "types.h"

struct fn_8005741C_lbl_80188A88 {
    u32 unk_0;
};

extern struct fn_8005741C_lbl_80188A88 lbl_80188A88[];
/* read through a volatile lvalue so the access is not optimised away */
extern volatile u32 lbl_800922C0[];
extern u32 lbl_80188A8C[];
extern u32 memset(u32, u32, u32);
extern void fn_800566BC(u32, u32);
extern void fn_800566F0(u32 *, u32, struct fn_8005741C_lbl_80188A88 *);
extern void fn_80056710(u32 *);

void fn_8005741C(void) {
    f64 loc_8[1];
    u32 value;

    (void)lbl_800922C0[0];
    fn_80056710((u32 *)&loc_8);
    if ((s32)lbl_80188A88[0].unk_0 == 0) {
        memset((u32)&lbl_80188A8C, 0, 0x2380);
        fn_800566BC(0, 0);
    }
    value = lbl_80188A88[0].unk_0;
    lbl_80188A88[0].unk_0 = value + 1;
    fn_800566F0((u32 *)&loc_8, value, lbl_80188A88);
}
