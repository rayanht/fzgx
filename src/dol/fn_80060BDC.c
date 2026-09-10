#include "types.h"
#include "dol/globals.h"

extern u8 lbl_80192D68[1344];

struct fn_80060BDC_Entry {
    u8 pad_0[0x14];
    u8 data[16][4];
};

void fn_80060BDC(u32 arg0) {
    u8 i = ((u8 *)lbl_801A6C80 + arg0 * 0x118)[0x140e];
    u8 j = ((u8 *)lbl_801A6C80 + arg0 * 0x118)[0x140f];
    struct fn_80060BDC_Entry *entries = (struct fn_80060BDC_Entry *)lbl_80192D68;

    if (arg0 == entries[i].data[j][2]) {
        entries[i].data[j][2] = 0xff;
        entries[i].data[j][0] = 0;
        return;
    }
    if (arg0 == entries[i].data[j][3]) {
        entries[i].data[j][3] = 0xff;
        entries[i].data[j][0] = 0;
    }
}
