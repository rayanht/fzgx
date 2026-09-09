#include "types.h"

extern void fn_80063F38(void *arg0, u8 arg1);

struct fn_800641A8_lbl_801A6C80_T {
    u8 data[0x444];
    u32 flags;
};

extern struct fn_800641A8_lbl_801A6C80_T *lbl_801A6C80;

void fn_800641A8(void *arg0) {
    u32 flags = lbl_801A6C80->flags;

    if (flags & 0x10) {
        u8 i = 0;

        while (i < 0x10) {
            if (*(u32 *)(lbl_801A6C80->data + (i << 4)) + 0x10000 != 0xffff) {
                fn_80063F38(arg0, i);
            }
            i++;
        }
    } else {
        fn_80063F38(arg0, flags & 0xf);
    }
}
