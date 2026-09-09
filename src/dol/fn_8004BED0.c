#include "types.h"

extern u32 fn_800474E4(u32);
extern char lbl_80090DCC[42];

u32 fn_8004BED0(u32 arg0) {
    if (arg0 == 0) {
        fn_800474E4((u32)&lbl_80090DCC);
        return 0;
    }
    return (s16)*(s16 *)((u8 *)arg0 + 64);
}
