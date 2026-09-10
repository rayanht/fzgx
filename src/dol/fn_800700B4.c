#include "types.h"

extern void GXGetGPStatus(u8 *, u8 *, u8 *, u8 *, u8 *);

void fn_800700B4(void) {
    u8 v3;
    u8 v2;
    u8 v1;
    u8 v0;

    do {
        GXGetGPStatus(&v3, &v3, &v2, &v1, &v0);
    } while (v2 != 1);
}
