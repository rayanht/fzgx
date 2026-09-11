#include "types.h"

typedef struct Entry {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
} Entry;

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);
extern void fn_8003E284(void);
extern void fn_80034378(u32);
extern u32 fn_8000A050(void);
extern u32 fn_8000A040(void);

extern u32 lbl_801A6C3C;
extern volatile u8 lbl_801A6C30;  /* frame counter shared with the timer handler */
extern u32 lbl_801A6C40;
extern u32 lbl_801A6C44;
extern u8 *lbl_801A6C48;
extern Entry *lbl_801A6C4C;
extern u32 lbl_801A6C54;
extern u32 lbl_801A6C58[2];

void fn_8003DC50(void) {
    u32 interrupts;
    u32 offset;
    u32 count;

    interrupts = OSDisableInterrupts();
    fn_8003E284();
    fn_80034378(lbl_801A6C3C);
    lbl_801A6C4C[lbl_801A6C44].unk8 = fn_8000A050();
    lbl_801A6C4C[lbl_801A6C44].unk4 = lbl_801A6C40;
    lbl_801A6C4C[lbl_801A6C44].unkC = fn_8000A040();
    lbl_801A6C40 = offset = 0;
    count = 0;
    lbl_801A6C44 = (lbl_801A6C44 + 1) % lbl_801A6C58[0];
    while (count < lbl_801A6C54) {
        *(u32 *)((u8 *)lbl_801A6C48 + offset + 8) = -1;
        offset += 16;
        count++;
    }
    lbl_801A6C30++;
    if (lbl_801A6C30 >= 16) {
        lbl_801A6C30 = 0;
    }
    OSRestoreInterrupts(interrupts);
}
