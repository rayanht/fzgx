#include <types.h>

typedef u8 GXBool;

typedef enum _GXTexFilter {
    GX_NEAR,
    GX_LINEAR,
    GX_NEAR_MIP_NEAR,
    GX_LIN_MIP_NEAR,
    GX_NEAR_MIP_LIN,
    GX_LIN_MIP_LIN,
} GXTexFilter;

typedef enum _GXAnisotropy {
    GX_ANISO_1,
    GX_ANISO_2,
    GX_ANISO_4,
    GX_MAX_ANISOTROPY,
} GXAnisotropy;

typedef struct _GXTexObj {
    u32 texture_filter;
    u32 texture_lod;
    u32 texture_size;
    u32 texture_address;
    u32 user_data;
    u32 texture_format;
    u32 tlut_name;
    u16 texture_time_count;
    u8 texture_tile_type;
    u8 texture_flags;
} GXTexObj;

extern u8 lbl_801A6570[6];

void fn_80035EC4(GXTexObj *obj, GXTexFilter minFilter, GXTexFilter maxFilter, f32 minLOD,
                 f32 maxLOD, f32 lodBias, GXBool doBiasClamp, GXBool doEdgeLOD,
                 GXAnisotropy maxAniso) {
    GXTexObj *internal = (GXTexObj *)obj;
    u8 reg1, reg2;
    if (lodBias < -4.0f) {
        lodBias = -4.0f;
    } else if (lodBias >= 4.0f) {
        lodBias = 3.99f;
    }
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((22 - 15 + 1))) - 1) << (31 - (15) - ((22 - 15 + 1)) + 1))) |
        ((int)((u8)(lodBias * 32.0f)) << (31 - (15) - ((22 - 15 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((27 - 27 + 1))) - 1) << (31 - (27) - ((27 - 27 + 1)) + 1))) |
        ((int)(maxFilter == 1 ? 1 : 0) << (31 - (27) - ((27 - 27 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((26 - 24 + 1))) - 1) << (31 - (24) - ((26 - 24 + 1)) + 1))) |
        ((int)(lbl_801A6570[minFilter]) << (31 - (24) - ((26 - 24 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((23 - 23 + 1))) - 1) << (31 - (23) - ((23 - 23 + 1)) + 1))) |
        ((int)(doEdgeLOD ? 0 : 1) << (31 - (23) - ((23 - 23 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((14 - 14 + 1))) - 1) << (31 - (14) - ((14 - 14 + 1)) + 1))) |
        ((int)(0) << (31 - (14) - ((14 - 14 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((13 - 13 + 1))) - 1) << (31 - (13) - ((13 - 13 + 1)) + 1))) |
        ((int)(0) << (31 - (13) - ((13 - 13 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((12 - 11 + 1))) - 1) << (31 - (11) - ((12 - 11 + 1)) + 1))) |
        ((int)(maxAniso) << (31 - (11) - ((12 - 11 + 1)) + 1));
    (internal->texture_filter) =
        (internal->texture_filter &
         ~(((1 << ((10 - 10 + 1))) - 1) << (31 - (10) - ((10 - 10 + 1)) + 1))) |
        ((int)(doBiasClamp) << (31 - (10) - ((10 - 10 + 1)) + 1));
    if (minLOD < 0.0f) {
        minLOD = 0.0f;
    } else if (minLOD > 10.0f) {
        minLOD = 10.0f;
    }
    reg1 = minLOD * 16.0f;
    if (maxLOD < 0.0f) {
        maxLOD = 0.0f;
    } else if (maxLOD > 10.0f) {
        maxLOD = 10.0f;
    }
    reg2 = maxLOD * 16.0f;
    (internal->texture_lod) = (internal->texture_lod & ~(((1 << ((31 - 24 + 1))) - 1)
                                                         << (31 - (24) - ((31 - 24 + 1)) + 1))) |
                              ((int)(reg1) << (31 - (24) - ((31 - 24 + 1)) + 1));
    (internal->texture_lod) = (internal->texture_lod & ~(((1 << ((23 - 16 + 1))) - 1)
                                                         << (31 - (16) - ((23 - 16 + 1)) + 1))) |
                              ((int)(reg2) << (31 - (16) - ((23 - 16 + 1)) + 1));
}
