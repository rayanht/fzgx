#include "types.h"
struct fn_80078D60_gx_T {
    u8 pad_0[0x204];
    u32 unk_204;
};
extern struct fn_80078D60_gx_T *gx;
extern u32 lbl_801A6D9C;
extern u32 func_8008D6BC(u32);


void fn_80078D60(s32 arg0) {
    u32 temp_r3;

    if ((s32) (*(u32 *)((u8 *)(&lbl_801A6D9C) + 0)) != arg0) {
        (*(u32 *)((u8 *)(&lbl_801A6D9C) + 0)) = (u32) arg0;
        temp_r3 = ((*(struct fn_80078D60_gx_T **)((u8 *)(&gx) + 0))->unk_204 & 0xFFFF3FFF) | (arg0 << 0xE);
        (*(struct fn_80078D60_gx_T **)((u8 *)(&gx) + 0))->unk_204 = temp_r3;
        func_8008D6BC((u32)(temp_r3));
    }
}
