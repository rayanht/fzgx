#include "types.h"

typedef enum _GXSpotFn {
    GX_SP_OFF,
    GX_SP_FLAT,
    GX_SP_COS,
    GX_SP_COS2,
    GX_SP_SHARP,
    GX_SP_RING1,
    GX_SP_RING2,
} GXSpotFn;

typedef struct _GXLightObj {
    u32 dummy[16];
} GXLightObj;

struct __GXLightObjInt_struct {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
};

extern f32 fn_80088624(f32);

void fn_80035420(GXLightObj *lt_obj, f32 cutoff, GXSpotFn spot_func) {
    f32 a0, a1, a2;
    f32 d, cr;
    struct __GXLightObjInt_struct *obj;

    if (cutoff <= 0.0f || cutoff > 90.0f)
        spot_func = GX_SP_OFF;

    cr = fn_80088624((3.14159265358979323846f * cutoff) / 180.0f);

    obj = (struct __GXLightObjInt_struct *)lt_obj;

    switch (spot_func) {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        a1 = 1.0f / (1.0f - cr);
        a0 = -cr * a1;
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        a2 = 1.0f / (1.0f - cr);
        a1 = -cr * a2;
        a0 = 0.0f;
        break;
    case GX_SP_SHARP:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = (cr * (cr - 2.0f)) * d;
        a1 = 2.0f * d;
        a2 = -d;
        break;
    case GX_SP_RING1:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a2 = -4.0f * d;
        a0 = a2 * cr;
        a1 = (4.0f * (1.0f + cr)) * d;
        break;
    case GX_SP_RING2:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = (2.0f * cr * cr) * d;
        a0 = 1.0f - a0;
        a1 = (4.0f * cr) * d;
        a2 = -2.0f * d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = a1;
        break;
    }

    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}
