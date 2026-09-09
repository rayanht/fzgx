#include "types.h"

extern u8 lbl_80192D68[1344];
extern void fn_8005FBDC(u8 value);

struct fn_800622B0_Entry {
    u8 pad_0[0x14];
    u8 data[16][4];
};

void fn_800622B0(void) {
    struct fn_800622B0_Entry *entries = (struct fn_800622B0_Entry *)lbl_80192D68;
    u8 i;
    u8 j;

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            if (entries[i].data[j][0] == 1) {
                if (entries[i].data[j][2] != 0xff) {
                    fn_8005FBDC(entries[i].data[j][2]);
                }
                if (entries[i].data[j][3] != 0xff) {
                    fn_8005FBDC(entries[i].data[j][3]);
                }
                entries[i].data[j][0] = 0;
            }
        }
        entries[i].pad_0[0xb] = 0;
    }
}
