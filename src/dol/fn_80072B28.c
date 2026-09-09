#include "types.h"
#include "dol/globals.h"

extern void fn_80037B68(u32);

void fn_80072B28(u32 arg0) {
    if (*(u8 *)(lbl_801A6D38 + 0xec) != 0xff &&
        *(u8 *)(lbl_801A6D38 + 0xec) == (u8)arg0) {
        return;
    }

    fn_80037B68(arg0);
    *(u8 *)(lbl_801A6D38 + 0xec) = arg0;
}
