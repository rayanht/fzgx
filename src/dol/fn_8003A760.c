#include "types.h"

typedef struct {
    u8 *unk0;
    u32 unk4;
    s32 *unk8;
    u8 padC[0xC];
    s32 unk18[16];
    s32 unk58;
    s32 unk5C;
    s32 unk60[16];
} unkStruct;

s32 fn_8003A760(u8 *arg0, u32 arg1) {
    unkStruct *p = (unkStruct *)(arg0 + 0x420 + 0xA8 * (arg1 & 0xFF));
    s32 acc = 0;
    s32 i;

    for (i = 1; i <= 16; i++) {
        if (p->unk0[i - 1] != 0) {
            p->unk60[i - 1] = acc - p->unk8[acc];
            acc += p->unk0[i - 1];
            p->unk18[i - 1] = p->unk8[acc - 1];
        } else {
            p->unk18[i - 1] = -1;
            p->unk60[i - 1] = -1;
        }
    }
    p->unk58 = 0xFFFFF;
    return 0;
}
