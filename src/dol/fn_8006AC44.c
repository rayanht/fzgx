#include "types.h"

typedef struct Fn8006AC44_Output {
    u8 pad_0[0x7];
    u8 x;
    u8 y;
} Fn8006AC44_Output;

typedef struct Fn8006AC44_Input {
    u16 buttons;
    u8 pad_2[0x4];
    u8 x;
    u8 y;
} Fn8006AC44_Input;

typedef struct Fn8006AC44_Calib {
    u8 pad_0[0x7];
    u8 min_x;
    u8 min_y;
    u8 pad_9[0x8];
    u8 max_x;
    u8 max_y;
    u8 pad_13[0x8];
    u8 dead_x;
    u8 dead_y;
    u8 pad_1D[0x1];
    u16 flags;
} Fn8006AC44_Calib;

static inline u8 fn_8006AC44_scale(s32 value, u8 *min, u8 *max, u8 dead) {
    s32 lo;
    s32 hi;
    s32 range;
    s32 result;

    lo = *min;
    hi = *max;
    if (value < lo) {
        *min = value;
        lo = value;
    }
    if (value > hi) {
        *max = value;
        hi = value;
    }
    range = hi - lo - dead * 2;
    if (range == 0) {
        range = 1;
    }
    result = (value - (lo + dead)) * 0xFF / range;
    if (result < 0) {
        result = 0;
    }
    if (result > 0xFF) {
        result = 0xFF;
    }
    return result;
}

void fn_8006AC44(Fn8006AC44_Output *out, Fn8006AC44_Input *in, Fn8006AC44_Calib *calib) {
    s32 value;

    if (in->x > calib->max_x - calib->dead_x * 2) {
        if ((in->buttons ^ calib->flags) & 0x40) {
            value = in->x - calib->dead_x;
            calib->max_x = value < 0 ? 0 : value;
            out->x = 0xFF;
        } else if (in->buttons & 0x40) {
            out->x = 0xFF;
        } else {
            out->x = fn_8006AC44_scale(in->x, &calib->min_x, &calib->max_x, calib->dead_x);
        }
    } else {
        out->x = fn_8006AC44_scale(in->x, &calib->min_x, &calib->max_x, calib->dead_x);
    }

    if (in->y > calib->max_y - calib->dead_y * 2) {
        if ((in->buttons ^ calib->flags) & 0x20) {
            value = in->y - calib->dead_y;
            calib->max_y = value < 0 ? 0 : value;
            out->y = 0xFF;
        } else if (in->buttons & 0x20) {
            out->y = 0xFF;
        } else {
            out->y = fn_8006AC44_scale(in->y, &calib->min_y, &calib->max_y, calib->dead_y);
        }
    } else {
        out->y = fn_8006AC44_scale(in->y, &calib->min_y, &calib->max_y, calib->dead_y);
    }
}
