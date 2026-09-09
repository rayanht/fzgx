#include "types.h"

s32 fn_80049728(void *);                            /* extern */
s32 fn_80049958(void *);                            /* extern */

void fn_80047A50(void *arg0) {
    s32 temp_r3;

loop_1:
    if ((s8) (*(u8 *)((u8 *)(arg0) + 3)) == 0) {
loop_2:
        temp_r3 = fn_80049958((void *)(arg0));
        if (temp_r3 != 0) {
            (*(s32 *)((u8 *)(arg0) + 44)) = (s32) ((*(s32 *)((u8 *)(arg0) + 44)) + temp_r3);
            if ((s32) (*(s32 *)((u8 *)(arg0) + 48)) >= (s32) (*(s32 *)((u8 *)(arg0) + 60))) {
                (*(u8 *)((u8 *)(arg0) + 3)) = 1U;
                goto loop_1; /* Preserves the retail branch. */
            }
            goto loop_2; /* Preserves the retail branch. */
        }
    } else if (fn_80049728((void *)(arg0)) > 0) {
        (*(s8 *)((u8 *)(arg0) + 1)) = 3;
    }
}
