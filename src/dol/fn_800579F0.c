#include "types.h"
typedef u32 (*fn_800579F0_Fn0)(u32, u32);
extern u32 fn_80057728(void);

s32 fn_800576DC();                              /* extern */

void fn_800579F0(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 var_r0;
    s32 (*temp_r12)(s32, s32);
    s32 temp_r3;

    fn_80057728();
    if (arg1 == 0) {
        (*(s32 *)((u8 *)(arg3) + 4)) = 0;
        (*(s32 *)((u8 *)(arg3) + 0)) = 0;
    } else if (arg1 == 1) {
        temp_r3 = *(s32 *)((u8 *)(arg0) + 12);
        var_r0 = arg2;
        if (temp_r3 < arg2) {
            var_r0 = temp_r3;
        }
        (*(s32 *)((u8 *)(arg3) + 4)) = var_r0;
        (*(s32 *)((u8 *)(arg3) + 0)) = (s32) ((*(s32 *)((u8 *)(arg0) + 20)) + (*(s32 *)((u8 *)(arg0) + 16)));
        (*(s32 *)((u8 *)(arg0) + 16)) = (s32) ((*(s32 *)((u8 *)(arg0) + 16)) + (*(s32 *)((u8 *)(arg3) + 4)));
        (*(s32 *)((u8 *)(arg0) + 12)) = (s32) ((*(s32 *)((u8 *)(arg0) + 12)) - (*(s32 *)((u8 *)(arg3) + 4)));
    } else {
        (*(s32 *)((u8 *)(arg3) + 4)) = 0;
        (*(s32 *)((u8 *)(arg3) + 0)) = 0;
        temp_r12 = (s32 (*)(s32, s32))(*(s32 (**)(s32, s32))((u8 *)(arg0) + 28));
        if (temp_r12 != NULL) {
            temp_r12(*(s32 *)((u8 *)(arg0) + 32), -3);
        }
    }
    fn_800576DC();
}
