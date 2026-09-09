#ifndef SOFDEC_SFX_H
#define SOFDEC_SFX_H

#include "types.h"

typedef struct SFXZObject SFXZObject;

typedef void (*SFXZConvertCallback)(u32 *source, void *destination, f32 near_clip, f32 far_clip);

struct SFXZObject {
    s32 active;
    s32 z_bit;
    s32 tag_info_set;
    u8 *tag_data;
    s32 tag_size;
    u8 reserved_14[4];
    s32 header_info_set;
    u8 *header_data;
    s32 header_size;
    u8 reserved_24[4];
    s32 frame_info_set;
    u8 *frame_data;
    s32 frame_size;
    u8 reserved_34[8];
    f32 near_clip;
    f32 far_clip;
    SFXZConvertCallback convert_callback;
    void *field_48;
};

#endif
