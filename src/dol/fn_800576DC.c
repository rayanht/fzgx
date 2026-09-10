#include "types.h"

extern s32 lbl_8018AE10[];
extern s32 lbl_8018AE14[];
extern u32 OSRestoreInterrupts(u32);

void fn_800576DC(void) {
    /* refcount is decremented from interrupt context; the test must re-read it */
    volatile s32 *counter = (volatile s32 *)&lbl_8018AE10;
    *counter = *counter - 1;
    if (*counter == 0) {
        OSRestoreInterrupts(lbl_8018AE14[0]);
    }
}
