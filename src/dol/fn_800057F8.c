#include "types.h"

extern void fn_8000EE5C(void *, void *);
extern u8 lbl_801A66B0[4];
extern void *memset(void *, int, u32);
extern void *memcpy(void *, const void *, u32);

void fn_800057F8(void) {
    void *src;
    void *dst;

    fn_8000EE5C(&src, &dst);
    if (src == 0 || dst == 0) {
        memset(lbl_801A66B0, 0, 4);
    } else {
        memcpy(lbl_801A66B0, src, 4);
    }
}
