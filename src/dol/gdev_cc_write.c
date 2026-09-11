#include "types.h"

extern s32 lbl_801A6E10[2];
extern void MWTRACE(s32, const char *, ...);
extern s32 fn_8008F45C(void *, s32);

u32 gdev_cc_write(void *buffer, s32 size) {
    s32 current_size = size;
    void *current_buffer = buffer;

    if (0 == lbl_801A6E10[0]) {
        MWTRACE(8, "cc not initialized\n");
        return -10001;
    }

    MWTRACE(8, "cc_write : Output data 0x%08x %ld bytes\n\000\000\000", buffer, size);
    while (current_size > 0) {
        MWTRACE(1, "cc_write sending %ld bytes\n", current_size);
        {
            s32 written = fn_8008F45C(current_buffer, current_size);
            if (written == 0) {
                break;
            }
            current_buffer = ((written) + ((u8 *)current_buffer));
            current_size -= written;
        }
    }
    return 0;
}
