#include "types.h"

typedef union {
    f32 f;
    u32 u;
} FloatBits;

u32 fn_80007CDC(f32 *arg0) {
    u32 flags[2];
    FloatBits value0;
    FloatBits value1;
    FloatBits value2;

    flags[0] = 1;
    flags[1] = flags[0];
    value0.f = arg0[0];
    if ((value0.u & 0x7F800000) != 0x7F800000) {
        value1.f = arg0[1];
        if ((value1.u & 0x7F800000) != 0x7F800000) {
            flags[1] = 0;
        }
    }
    if ((s32)flags[1] == 0) {
        value2.f = arg0[2];
        if ((value2.u & 0x7F800000) != 0x7F800000) {
            flags[0] = 0;
        }
    }
    return flags[0];
}
