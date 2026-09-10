#include "types.h"

extern void GXGetVtxAttrFmt(void *vat, int attr, u32 *cnt, u32 *type, u32 *frac);

typedef struct GXVtxAttrFmt {
    u32 attr;
    u32 cnt;
    u32 type;
    u32 frac;
} GXVtxAttrFmt;

void GXGetVtxAttrFmtv(void *vat, GXVtxAttrFmt *fmt) {
    int attr;

    for (attr = 9; attr <= 20; attr++) {
        fmt->attr = (u32)attr;
        GXGetVtxAttrFmt(vat, attr, &fmt->cnt, &fmt->type, &fmt->frac);
        fmt++;
    }
    fmt->attr = 0xff;
}
