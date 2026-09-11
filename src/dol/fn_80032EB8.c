#include "types.h"

extern void GXGetVtxDesc(int attr, u32 *type);

void fn_80032EB8(u32 fmt) {
    int attr;

    for (attr = 0; attr <= 20; attr++) {
        *(u32 *)(fmt + attr * 8) = attr;
        GXGetVtxDesc(attr, (u32 *)(fmt + attr * 8 + 4));
    }
    *(u32 *)(fmt + attr * 8) = 25;
    GXGetVtxDesc(25, (u32 *)(fmt + attr * 8 + 4));
    *(u32 *)(fmt + ++attr * 8) = 255;
}
