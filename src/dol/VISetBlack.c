#include "types.h"

struct VISetBlack_lbl_8015CF68 {
    u8 pad_0[0xf6];
    u16 unk_f6;
    u8 pad_f8[2];
    u16 unk_fa;
    u8 pad_fc[0x34];
    u32 unk_130;
    u8 pad_134[0x10];
    u8 *unk_144;
};

extern struct VISetBlack_lbl_8015CF68 lbl_8015CF68;
extern u32 OSDisableInterrupts(u32);
extern u32 OSRestoreInterrupts(u32);
extern void setVerticalRegs(u16, u16, u8, u16, u16, u16, u16, u16, u32);

void VISetBlack(u32 arg0) {
    struct VISetBlack_lbl_8015CF68 *p_lbl_8015CF68;
    u32 v0;
    u32 t0;

    p_lbl_8015CF68 = (struct VISetBlack_lbl_8015CF68 *)&lbl_8015CF68;
    v0 = (arg0 + 0);
    t0 = OSDisableInterrupts(arg0);
    p_lbl_8015CF68->unk_130 = v0;
    v0 = (t0 + 0);
    setVerticalRegs(p_lbl_8015CF68->unk_fa, p_lbl_8015CF68->unk_f6,
                p_lbl_8015CF68->unk_144[0],
                *(u16 *)(p_lbl_8015CF68->unk_144 + 2),
                *(u16 *)(p_lbl_8015CF68->unk_144 + 4),
                *(u16 *)(p_lbl_8015CF68->unk_144 + 6),
                *(u16 *)(p_lbl_8015CF68->unk_144 + 8),
                *(u16 *)(p_lbl_8015CF68->unk_144 + 10),
                p_lbl_8015CF68->unk_130);
    OSRestoreInterrupts(v0);
}
