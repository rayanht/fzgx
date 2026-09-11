#include "types.h"

typedef struct {
    u8 pad_00[0x1e];
    u8 count;
    u8 pad_1f[0x9];
    u8 entries[8];
} Fn80078C28Arg0;

extern u32 lbl_801A6D00;
extern u32 lbl_801A6DA4;
extern u32 lbl_801A6DA8;
extern void lbl_8006DFFC(u32, u32, u32);
extern void u_gxutil_upload_some_mtx(u32, s32);

static inline void fn_80078C28_upload(Fn80078C28Arg0 *arg0) {
    s32 i;

    i = 0;
    do {
        if ((s32)arg0->entries[i] != 0xFF) {
            u_gxutil_upload_some_mtx(lbl_801A6DA8 + arg0->entries[i] * 0x30, i + 1);
        }
        i++;
    } while (i < 8);
}

void fn_80078C28(Fn80078C28Arg0 *arg0) {
    u32 index;

    index = 0;
    while (index < arg0->count) {
        lbl_8006DFFC(lbl_801A6D00,
                     *(u32 *)((u8 *)(u32)lbl_801A6DA4 + index * 4),
                     lbl_801A6DA8 + index * 0x30);
        index++;
    }

    fn_80078C28_upload(arg0);
}
