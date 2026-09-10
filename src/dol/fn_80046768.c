#include "types.h"

extern char lbl_80090930[];
extern u32 strlen(char *);

u32 fn_80046768(s32 flag, u32 subtrahend, u32 value, u32 divisor) {
    if (flag == 0) {
        return (0x1b + subtrahend + strlen(lbl_80090930) + value + divisor) / divisor * divisor -
               value;
    }
    return (0x33 + subtrahend + strlen(lbl_80090930) + value + divisor) / divisor * divisor - value;
}
