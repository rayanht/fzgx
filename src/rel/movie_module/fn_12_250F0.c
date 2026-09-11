#include "types.h"

typedef struct MpsHandle MpsHandle;

typedef struct SfmpsWork {
    MpsHandle *decoder;
    s32 max_video_bound;
    s32 max_audio_bound;
    s32 video_pts_baseline;
    s32 audio_pts_baseline;
    s32 concat_count;
    s32 previous_video_stream;
    s32 previous_audio_stream;
    s32 first_video_stream;
    s32 first_audio_stream;
    s32 selected_video_id;
    s32 selected_audio_id;
    s32 delimiter_state;
    void *element_outputs[0x44];
    void *element_callback;
    void *element_callback_argument;
} SfmpsWork;

typedef struct SfdHandle {
    u8 pad_0000[0x1AEC];
    SfmpsWork *work;
    u8 pad_1AF0[0x214];
    SfmpsWork mps_work_storage;
} SfdHandle;

typedef void (*MpsErrorCallback)(void *object, s32 error);

extern MpsHandle *fn_12_6B28(void);
extern int fn_12_6A90(MpsHandle *handle);
extern int fn_12_6CA8(MpsHandle *handle, MpsErrorCallback callback, void *object);
extern int fn_12_24A88(SfdHandle *handle, s32 error);
extern void fn_12_250D0(void *object, s32 error);

s32 fn_12_250F0(SfdHandle *handle) {
    SfmpsWork *work;
    MpsHandle *decoder;
    struct { int value; } i;

    work = &handle->mps_work_storage;
    handle->work = work;
    work->decoder = 0;
    work->max_video_bound = 0;
    work->max_audio_bound = 0;
    work->video_pts_baseline = 0x7FFFFFFF;
    work->audio_pts_baseline = 0x7FFFFFFF;
    work->concat_count = 0;
    work->previous_video_stream = 0x7FFFFFFF;
    work->previous_audio_stream = 0x7FFFFFFF;
    work->first_video_stream = -1;
    work->first_audio_stream = -1;
    work->selected_video_id = -1;
    work->selected_audio_id = -1;
    work->delimiter_state = 0;
    for (i.value = 0; i.value < 0x44; i.value++) {
        work->element_outputs[i.value] = 0;
    }
    work->element_callback = 0;
    work->element_callback_argument = 0;
    decoder = fn_12_6B28();
    if (decoder == 0) {
        return fn_12_24A88(handle, 0xFF000D08);
    }
    if (fn_12_6CA8(decoder, fn_12_250D0, handle) != 0) {
        fn_12_6A90(decoder);
        return fn_12_24A88(handle, 0xFF000D09);
    }
    work->decoder = decoder;
    return 0;
}
