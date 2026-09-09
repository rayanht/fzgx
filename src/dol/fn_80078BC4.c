#include "types.h"

extern u32 lbl_801A6DA8;
extern void u_gxutil_upload_some_mtx(u32, s32);

void fn_80078BC4(u8 *arg0) {
    u8 *ptr;
    s32 i;

    ptr = arg0;
    i = 0;
    do {
        if ((s32)*ptr != 0xFF) {
            u_gxutil_upload_some_mtx(lbl_801A6DA8 + *ptr * 48, i + 1);
        }
        i++;
        ptr++;
    } while (i < 8);
}
