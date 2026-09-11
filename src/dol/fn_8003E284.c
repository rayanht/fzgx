#include "types.h"

typedef struct {
    u8 unk00;
    u8 pad01[0x0B];
    u32 unk0C;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
    u32 unk30;
    u32 unk34;
    u8 pad38[0x78];
} Entry;

typedef struct {
    Entry *entries;
    u32 unk04;
    u32 unk08;
    u32 unk0C;
} Slot;

extern s32 lbl_801A6584;
extern u32 lbl_801A6C44;
extern Slot *lbl_801A6C4C;

extern u32 fn_8000A020(void);
extern u32 fn_8000A040(void);
extern u32 fn_8000A050(void);
extern void fn_8003D588(Entry *entry, u32 arg);

void fn_8003E284(void) {
    if (lbl_801A6584 >= 0) {
        lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk10 = fn_8000A050();
        fn_8003D588(&lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584], 1);
        lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk24 = fn_8000A040();
        lbl_801A6C4C[lbl_801A6C44].entries[lbl_801A6584].unk34 = fn_8000A020();
    }
    lbl_801A6584 = -1;
}
