#include "types.h"

typedef u32 (*fn_16_910_Fn0)(void);
struct fn_16_910_lbl_16_data_82C1C_0_E44 {
    u8 pad_0[0x20];
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
};
struct fn_16_910_lbl_16_data_82C1C {
    struct fn_16_910_lbl_16_data_82C1C_0_E44 unk_0[1];
};

extern s16 lbl_1_bss_962;
extern struct fn_16_910_lbl_16_data_82C1C lbl_16_data_82C1C;
extern u32 lbl_1_bss_71688;
extern u32 lbl_1_bss_7168C;

void fn_16_910(void) {
    struct fn_16_910_lbl_16_data_82C1C *p;
    s32 idx;
    p = (struct fn_16_910_lbl_16_data_82C1C *)&lbl_16_data_82C1C;
    idx = lbl_1_bss_962 - 190;
    lbl_1_bss_71688 = p->unk_0[idx].unk_24;
    lbl_1_bss_7168C = p->unk_0[idx].unk_28;
    ((fn_16_910_Fn0)p->unk_0[idx].unk_20)();
}
