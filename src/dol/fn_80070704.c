#include "types.h"

extern u8 lbl_801A6CEA;
extern u8 lbl_8012AFF4[60];
extern u8 lbl_8012AFB8[60];
extern void fn_80034ECC(u8, u8 *, u32, u8 *);

void fn_80070704(s32 arg0) {
    struct { u8 *value; } table;

    if (arg0 == lbl_801A6CEA) {
        return;
    }
    lbl_801A6CEA = arg0;
    table.value = lbl_8012AFF4;
    if ((arg0 & 0xff) != 0) {
        table.value = lbl_8012AFB8;
    }
    fn_80034ECC(table.value[0x19], table.value + 0x1a, 1, table.value + 0x32);
}
