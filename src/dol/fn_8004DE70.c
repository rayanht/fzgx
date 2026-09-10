
#include "types.h"

typedef struct SJCK {
    unsigned char *data;
    int len;
} SJCK;

typedef struct SJ SJ;

typedef struct SJInterface SJInterface;

typedef void (*SJErrorCallback)(void *object, int error);

struct SJInterface {
    void *reserved[3];
    void (*destroy)(SJ *sj);
    const void *(*get_uuid)(SJ *sj);
    void (*reset)(SJ *sj);
    void (*get_chunk)(SJ *sj, int channel, int max_size, SJCK *chunk);
    void *reserved_1C;
    void (*put_chunk)(SJ *sj, int channel, SJCK *chunk);
    int (*get_num_data)(SJ *sj, int channel);
    int (*is_get_chunk)(SJ *sj, int channel, int size, int *available);
    void (*entry_error_func)(SJ *sj, SJErrorCallback callback, void *object);
};

struct SJ {
    const SJInterface *interface;
};

typedef struct AdxSjdHandle AdxSjdHandle;

typedef struct ADXStream ADXStream;

typedef struct AXRNAHandle AXRNAHandle;

typedef struct LSCObject LSCObject;

typedef struct ADX_AMP ADX_AMP;

typedef struct ADXTHandle {
    u8 pad_0[2];
    s8 stream_type;
    u8 pad_3[1];
    AdxSjdHandle *decoder;
    u32 unk_8;
    u8 pad_C[8];
    SJ *input_sj;
    u8 pad_18[0x34];
    s32 loop_count;
    s32 link_data_length;
    u8 pad_54[0x18];
    s8 stream_loop_enabled;
    u8 pad_6D[0x23];
    s32 loop_sample_count;
} ADXTHandle;

enum {
    ADXT_STATUS_DECODING_HEADER = 1,
    ADXT_STATUS_BUFFERING = 2,
    ADXT_STATUS_PLAYING = 3,
    ADXT_STATUS_DRAINING = 4,
    ADXT_STATUS_ERROR = 6,
    ADXT_STREAM_TYPE_FILE = 0,
    ADXT_STREAM_TYPE_RANGE = 1,
    ADXT_STREAM_TYPE_MEMORY = 2,
    ADXT_STREAM_TYPE_LINKED = 3,
    ADXSJD_STATUS_HEADER_READY = 2,
    ADXSJD_STATUS_INPUT_END = 3,
    ADXSTM_STATUS_READING = 2,
    ADXSTM_STATUS_END = 3,
    ADXSTM_STATUS_ERROR = 4,
    ADXT_SECTOR_SIZE = 0x800,
    ADXT_MIN_PLAY_DATA = 0x40
};

void fn_8004DE70(void *object);

extern void fn_800474E4(const char *message);

extern s32 fn_80041554(AdxSjdHandle *decoder);

extern s32 fn_80041578(AdxSjdHandle *decoder);

extern s32 fn_800415AC(AdxSjdHandle *decoder);

extern void fn_800416DC(AdxSjdHandle *decoder, s32 samples);

extern void fn_800416DC(AdxSjdHandle *decoder, s32 length);

extern void fn_800416D4(AdxSjdHandle *decoder, s32 count);

extern void fn_800416CC(AdxSjdHandle *decoder, s32 position);

extern void ADXSJD_EntryTrapFunc(AdxSjdHandle *decoder, void (*callback)(void *object),
                                 void *object);

extern void fn_80041410(AdxSjdHandle *decoder);

extern void ADXSTM_EntryEosFunc(ADXStream *stream, void (*callback)(void *object), void *object);

extern const char lbl_80091104[];

void fn_8004DE70(void *object) {
    ADXTHandle *handle = (ADXTHandle *)object;
    AdxSjdHandle *decoder = handle->decoder;
    SJ *input = handle->input_sj;
    SJCK chunk;
    s32 loop_start_position;
    s32 loop_start_offset;
    s32 loop_end_position;
    s32 loop_sample_count;

    loop_start_position = fn_800415AC(decoder);
    loop_start_offset = fn_80041578(decoder);
    loop_end_position = fn_80041554(decoder);
    if (handle->unk_8 == 0 && handle->stream_loop_enabled == 0) {
        fn_800416DC(handle->decoder, -1);
        return;
    }
    input->interface->get_chunk(input, 1, handle->link_data_length, &chunk);
    if (chunk.len < handle->link_data_length) {
        fn_800474E4(lbl_80091104);
    }
    input->interface->put_chunk(input, 0, &chunk);
    fn_800416D4(decoder, 0);
    loop_sample_count = loop_end_position - loop_start_position;
    handle->loop_sample_count = loop_sample_count;
    fn_800416DC(decoder, loop_sample_count);
    fn_800416CC(decoder, loop_start_offset);
    fn_800416F0(decoder, loop_start_position);
    if (handle->stream_type == ADXT_STREAM_TYPE_MEMORY) {
        input->interface->reset(input);
        input->interface->get_chunk(input, 1, loop_start_offset, &chunk);
        input->interface->put_chunk(input, 0, &chunk);
    }
    fn_80041410(decoder);
    handle->loop_count++;
}
