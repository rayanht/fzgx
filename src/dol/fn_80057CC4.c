#include "types.h"

extern u32 lbl_8018AE18[];
extern u8 lbl_8018AE1C[1156];
extern void *memset(void *destination, int value, u32 size);

void fn_80057CC4(void) {
    if (--lbl_8018AE18[0] == 0) {
        memset(lbl_8018AE1C, 0, 0x480);
    }
}
