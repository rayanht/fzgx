#include "types.h"

typedef struct GXContext {
    u8 pad_0[0x80];
    u32 field_80;
} GXContext;

extern GXContext* gx;
extern void fn_80039088(u32);

void fn_80038CFC(u32 value) {
    GXContext* context = gx;
    context->field_80 = (context->field_80 & ~0x3fu) | value;
    fn_80039088(0);
}
