#include "types.h"

extern u32 fn_8000A020(void);
extern u32 fn_8000A040(void);
extern u32 fn_8000A050(void);
extern u32 fn_8003D588(void *, u32);
extern volatile u32 lbl_801A6584;  /* written then re-read as an MMIO-visible slot */
extern volatile u32 lbl_801A6C40;
extern u32 lbl_801A6C44;
extern u32 lbl_801A6C50;

typedef struct {
    u8 unk00;
    u8 pad01[0x0B];
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u8 pad24[0x0C];
    u32 unk30;
    u8 pad34[0x7C];
} Entry;

typedef struct {
    Entry *entries;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
} Slot;

extern Slot *lbl_801A6C4C;

void fn_8003E13C(void) {
    u32 max = lbl_801A6C50 - 1;
    u32 idx;

    if (lbl_801A6C40 >= max) {
        lbl_801A6C40 = max;
        idx = lbl_801A6C40;
    } else {
        idx = lbl_801A6C40;
        lbl_801A6C40 = idx + 1;
    }
    lbl_801A6584 = idx;

    lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk00 = 0xff;
    lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk14 = 0;
    fn_8003D588(&lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584], 0);
    lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk0C = fn_8000A050();
    lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk10 = 0;
    lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk20 = fn_8000A040();
    lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk30 = fn_8000A020();
}
