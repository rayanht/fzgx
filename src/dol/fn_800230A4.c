#include "types.h"
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL);

void fn_800230A4(void *arg0, s32 arg1) {
    s32 temp_r3;
    void *temp_r4;

    temp_r3 = OSDisableInterrupts();
    temp_r4 = (void *)((u8 *)(arg0) + 0x138);
    switch (arg1) {                                 /* irregular */
    case 0:
        (*(s16 *)((u8 *)(temp_r4) + 8)) = 2;
        break;
    case 1:
        (*(s16 *)((u8 *)(temp_r4) + 8)) = 1;
        break;
    case 2:
        (*(s16 *)((u8 *)(temp_r4) + 8)) = 0;
        (*(s16 *)((u8 *)(temp_r4) + 10)) = 0;
        break;
    case 3:
        (*(s16 *)((u8 *)(temp_r4) + 8)) = 0;
        (*(s16 *)((u8 *)(temp_r4) + 10)) = 1;
        break;
    case 4:
        (*(s16 *)((u8 *)(temp_r4) + 8)) = 0;
        (*(s16 *)((u8 *)(temp_r4) + 10)) = 2;
        break;
    }
    (*(s32 *)((u8 *)(arg0) + 28)) = (s32) ((*(s32 *)((u8 *)(arg0) + 28)) | 1);
    OSRestoreInterrupts(temp_r3);
}
