#include "types.h"
extern u32 lbl_801A6CE0;
extern u32 lbl_801A6CF8;
extern u32 lbl_801A6CFC;
extern u8 lbl_801A6621;
extern u8 lbl_801A6CE8;
extern u8 lbl_801A6CE9;
extern void * OSGetArenaLo(void);
extern u32 OSGetArenaHi(void);
extern u32 fn_8000E7A0(void);
extern u32 fn_8000E794(void);
extern void OSSetArenaLo(u32);
extern void OSSetArenaHi(u32);
extern void fn_80070A58(void);


void fn_80070538(void) {
    u32 temp_r4;
    u32 var_r3;
    u32 temp_r31;
    void *temp_r30;
    u32 var_r29;

    temp_r30 = (void *)(OSGetArenaLo());
    var_r29 = OSGetArenaHi();
    (*(u32 *)((u8 *)(&lbl_801A6CF8) + 0)) = 0;
    (*(u32 *)((u8 *)(&lbl_801A6CFC) + 0)) = 0;
    temp_r31 = fn_8000E7A0();
    if (((u8) (*(u8 *)((u8 *)(&lbl_801A6CE9) + 0)) != 0) || (temp_r31 <= 0x01800000U)) {
        var_r3 = 0x01800000;
    } else {
        var_r3 = fn_8000E794();
    }
    if (var_r3 > 0x01800000U) {
        temp_r4 = (*(u32 *)((u8 *)(&lbl_801A6CE0) + 0)) | 8;
        (*(u32 *)((u8 *)(&lbl_801A6CE0) + 0)) = temp_r4;
        if ((u8) (*(u8 *)((u8 *)(&lbl_801A6CE8) + 0)) == 0) {
            (*(u32 *)((u8 *)(&lbl_801A6CF8) + 0)) = var_r29;
            (*(u32 *)((u8 *)(&lbl_801A6CE0) + 0)) = temp_r4 | 1;
            var_r29 -= temp_r31 + 0xFE800000;
            (*(u32 *)((u8 *)(&lbl_801A6CFC) + 0)) = var_r29;
        } else {
            (*(u32 *)((u8 *)(&lbl_801A6CFC) + 0)) = var_r29;
            (*(u32 *)((u8 *)(&lbl_801A6CF8) + 0)) = var_r29 + (var_r3 - temp_r31);
        }
    }
    (*(u8 *)((u8 *)(&lbl_801A6621) + 0)) = 0;
    OSSetArenaLo((u32)(temp_r30));
    OSSetArenaHi(var_r29);
    fn_80070A58();
}
