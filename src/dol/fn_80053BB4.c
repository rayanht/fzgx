#include "types.h"

extern u32 lbl_80187370[4];
extern u32 lbl_80187380[16];
extern void *memset(void *dest, int value, u32 size);

void fn_80053BB4(void) {
    u32 *counter = lbl_80187370;
    *counter -= 1;
    if (*counter == 0) {
        memset(lbl_80187380, 0, 0x40);
    }
}
