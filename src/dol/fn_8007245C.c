#include "types.h"

extern u32 lbl_801A6D28;
extern void fn_80032F48(u32 value);
extern void fn_800324C8(u32 index, u32 value);

void fn_8007245C(u32 value) {
    u32 index;

    if (value != lbl_801A6D28) {
        fn_80032F48(value);
        lbl_801A6D28 = value;
        index = 0;
        while (index < 0x1a) {
            if (value & 1) {
                fn_800324C8(index, 1);
            }
            index++;
            value >>= 1;
        }
    }
}
