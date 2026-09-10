#include "types.h"

extern const f32 lbl_801A6E44;
extern const f32 lbl_801A6E48;
extern u32 lbl_801A7900[2];
extern const f32 lbl_801A6E4C;
extern const f32 lbl_801A6E50;
extern void fn_800721FC(f32, f32, f32, f32);
extern u32 fn_80072BD0(u32);
extern u32 fn_800728A8(u32, u32, u32, u32);
extern u32 GXSetAlphaCompare(u32, u32, u32, u32, u32);
extern u32 fn_80037D40(u32, u32);
extern void fn_80007A44(void);
extern void fn_8006CDFC(void *);
extern const f32 lbl_801A6E54;
extern void fn_8006CE1C(f32);

void fn_80005738(void) {
    u32 value[2];

    value[1] = lbl_801A7900[0];
    fn_800721FC(lbl_801A6E44, lbl_801A6E48, lbl_801A6E4C, lbl_801A6E50);
    fn_80072BD0(1);
    fn_800728A8(1, 4, 5, 0);
    GXSetAlphaCompare(4, 0, 0, 4, 0);
    fn_80037D40(0, 0);
    fn_80007A44();
    value[0] = value[1];
    fn_8006CDFC(&value[0]);
    fn_8006CE1C(lbl_801A6E54);
}
