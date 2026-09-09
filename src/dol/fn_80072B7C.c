#include "types.h"
#include "dol/globals.h"

extern void fn_80037B94(u32);

void fn_80072B7C(u32 arg0) {
    if (*(u8 *)(lbl_801A6D38 + 0xed) != 0xff &&
        *(u8 *)(lbl_801A6D38 + 0xed) == (u8)arg0) {
        return;
    }

    fn_80037B94(arg0);
    *(u8 *)(lbl_801A6D38 + 0xed) = (u8)arg0;
}
