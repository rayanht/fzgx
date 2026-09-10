#include "types.h"

extern u32 lbl_801A6D28;
extern void GXClearVtxDesc(u32 value);
extern void GXSetVtxDesc(u32 index, u32 value);

void fn_8007245C(u32 value) {
    u32 index;

    if (value != lbl_801A6D28) {
        GXClearVtxDesc(value);
        lbl_801A6D28 = value;
        index = 0;
        while (index < 0x1a) {
            if (value & 1) {
                GXSetVtxDesc(index, 1);
            }
            index++;
            value >>= 1;
        }
    }
}
