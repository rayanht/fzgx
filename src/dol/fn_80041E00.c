
#include "types.h"

typedef struct AdxXpndParams {
    int channel_count;
    const signed char *input;
    int num_blocks;
    short *output_left;
    short *output_right;
} AdxXpndParams;

typedef struct AdxXpnd {
    int used;
    int index;
    int mode;
    int status;
    int num_decoded_blocks;
    AdxXpndParams params;
    short delay[2][2];
    short coefficients[2];
    short random_state;
    short random_multiplier;
    short random_increment;
    short reserved;
} AdxXpnd;

typedef struct AdxDecodeParams {
    const unsigned short *input;
    int input_blocks;
    int channel_count;
    int block_size;
    int samples_per_block;
    short *pcm_buffer;
    int pcm_size;
    int pcm_distance;
    int write_position;
    int room;
    int loop_samples;
} AdxDecodeParams;

typedef void (*AdxGetWriteInfo)(void *, int *, int *, int *);

typedef void (*AdxAddWriteInfo)(void *, int, int);

typedef struct AdxBasicDecoder {
    short used;
    short header_decoded;
    int status;
    AdxXpnd *expander;
    signed char encoding;
    signed char bits_per_sample;
    signed char channel_count;
    signed char block_length;
    int samples_per_block;
    int sample_rate;
    int total_samples;
    short coefficient;
    short field_1E;
    int loop_insert_samples;
    short loop_count;
    short loop_type;
    int loop_start_sample;
    int loop_start_offset;
    int loop_end_sample;
    int loop_end_offset;
    int max_channels;
    short *pcm_buffer;
    int pcm_size;
    int pcm_distance;
    AdxDecodeParams decode;
    short field_74;
    short field_76;
    AdxGetWriteInfo get_write_info;
    void *get_write_object;
    AdxAddWriteInfo add_write_info;
    void *add_write_object;
    int total_decoded_samples;
    int current_write_position;
    int decoded_samples;
    int decoded_data_length;
    short format_type;
    short field_9A;
    short codec_type;
} AdxBasicDecoder;

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
    void (*unget_chunk)(SJ *sj, int channel, SJCK *chunk);
    void (*put_chunk)(SJ *sj, int channel, SJCK *chunk);
    int (*get_num_data)(SJ *sj, int channel);
    int (*is_get_chunk)(SJ *sj, int channel, int size, int *available);
    void (*entry_error_func)(SJ *sj, SJErrorCallback callback, void *object);
};

struct SJ {
    const SJInterface *interface;
};

enum {
    ADXSJD_MAX_HANDLES = 16,
    ADXSJD_MAX_CHANNELS = 2,
    ADXSJD_MAX_HEADER_SIZE = 0xC800,
    ADXSJD_MAX_OUTPUT_CHUNK = 0x4000
};

typedef struct AhxDecoder AhxDecoder;

typedef struct AdxBasicDecoderExt {
    AdxBasicDecoder base;
    s16 default_key[3];
    s16 snapshot_key[3];
    s16 delay_left[2];
    s16 delay_right[2];
    AhxDecoder *ahx_decoder;
    s32 ahx_max_decoded_samples;
    s32 ahx_max_decoded_blocks;
    s32 ainf_length;
    u8 ainf[16];
    s16 default_out_volume;
    s16 default_pan[2];
    u8 reserved_DA[2];
    void *pl2_context;
    u8 reserved_E0[8];
    s32 last_notified_data_length;
    s32 field_EC;
    void (*notify)(void *, s32, s32);
    void *notify_object;
} AdxBasicDecoderExt;

typedef void (*AdxSjdTrapCallback)(void *object);

typedef void (*AdxSjdOutputCallback)(void *object, s32 channel, u8 *data, s32 length);

typedef struct AdxSjdHandle {
    s8 used;
    s8 status;
    s8 channel_count;
    s8 wait_for_input;
    AdxBasicDecoderExt *decoder;
    SJ *input;
    SJ *output[ADXSJD_MAX_CHANNELS];
    SJCK input_chunk;
    SJCK output_chunk[ADXSJD_MAX_CHANNELS];
    s32 decoded_samples;
    s32 decoded_data_length;
    s32 decode_position;
    s32 max_decode_samples;
    s32 trap_num_samples;
    s32 trap_count;
    s32 trap_data_length;
    AdxSjdTrapCallback trap_callback;
    void *trap_object;
    AdxSjdOutputCallback output_callback;
    void *output_object;
    u8 spsd_info[0x40];
    s32 header_length;
    s32 link_switch;
    s32 pending_leading_samples;
    s32 pending_trailing_samples;
} AdxSjdHandle;

extern s32 fn_80045588(AdxBasicDecoderExt *decoder);

extern s16 *fn_800455A4(AdxBasicDecoderExt *decoder);

extern u8 *fn_80057DB0(SJ *sj);

void fn_80041E00(void *object, int *write_position, int *writable_samples, int *limit_samples) {
    AdxSjdHandle *handle = object;
    SJ *first_output = handle->output[0];
    s32 channel;
    s32 samples;
    s32 available_samples;
    for (channel = 0; channel < fn_80045588(handle->decoder); channel++) {
        handle->output[channel]->interface->get_chunk(
            handle->output[channel], 0, ADXSJD_MAX_OUTPUT_CHUNK, &handle->output_chunk[channel]);
    }
    *write_position = (handle->output_chunk[0].data - fn_80057DB0(first_output)) / 2;
    samples = handle->max_decode_samples;
    available_samples = handle->output_chunk[0].len / 2;
    if (available_samples < samples) {
        samples = available_samples;
    }
    *writable_samples = samples;
    if (handle->trap_num_samples >= 0) {
        *limit_samples = handle->trap_num_samples - handle->trap_count;
    } else {
        *limit_samples = 0x1FFFFFFF;
    }
    (void)fn_800455A4(handle->decoder);
}
