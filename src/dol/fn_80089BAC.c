#include "types.h"

struct fn_80089BAC_Buffer {
    u32 unk_0;
    u8 unk_4;
    u8 pad_5[3];
    u8 unk_8;
    u8 pad_9[0x37];
};

extern u8 lbl_800958C4[44];
extern u32 MWTRACE(u32, ...);
extern s32 TRKTargetStopped(void);
extern void *memset(void *, s32, u32);
extern u32 fn_8008D398(u32, u32);
extern s32 TRKTargetContinue(void);

s32 fn_80089BAC(void) {
    struct fn_80089BAC_Buffer buffer0;
    struct fn_80089BAC_Buffer buffer1;

    MWTRACE(1, (u32)&lbl_800958C4);
    if (!TRKTargetStopped()) {
        memset(&buffer0, 0, 0x40);
        buffer0.unk_4 = 0x80;
        buffer0.unk_0 = 0x40;
        buffer0.unk_8 = 0x16;
        fn_8008D398((u32)&buffer0, 0x40);
        return 0;
    }

    memset(&buffer1, 0, 0x40);
    buffer1.unk_4 = 0x80;
    buffer1.unk_0 = 0x40;
    buffer1.unk_8 = 0;
    fn_8008D398((u32)&buffer1, 0x40);
    return TRKTargetContinue();
}
