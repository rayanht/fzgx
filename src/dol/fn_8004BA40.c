
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
    void (*unget_chunk)(SJ *sj, int channel, SJCK *chunk);
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
    s8 used;
    s8 status;
    s8 stream_type;
    s8 maximum_channels;
    AdxSjdHandle *decoder;
    ADXStream *stream;
    AXRNAHandle *rna;
    SJ *stream_sj;
    SJ *input_sj;
    SJ *output_sj[2];
    u8 *input_buffer;
    s32 input_buffer_size;
    s32 input_extra_size;
    u8 *output_buffer;
    s32 output_buffer_size;
    s32 output_buffer_distance;
    s32 server_frequency;
    s16 stream_buffer_sectors;
    s16 minimum_buffer_sectors;
    s16 output_volume;
    s16 output_pan[2];
    s16 field_46;
    s32 maximum_decode_samples;
    s32 loop_count;
    s32 link_data_length;
    s32 field_54;
    s32 field_58;
    s32 field_5C;
    s16 error_code;
    u8 reserved_62[2];
    s32 field_64;
    s16 field_68;
    s16 field_6A;
    s8 stream_loop_enabled;
    s8 auto_receiver;
    u8 reserved_6E[2];
    s8 suppress_playback;
    s8 decoder_ready;
    s8 paused;
    u8 reserved_73;
    ADX_AMP *amplifier;
    SJ *amplifier_input[2];
    SJ *amplifier_output[2];
    s32 time_offset;
    s32 eos_sector;
    s32 loop_sample_count;
    LSCObject *linked_stream_controller;
    s8 link_enabled;
    u8 reserved_99[3];
    u32 playback_time;
    s32 playback_start_vsync;
    s32 linked_decoded_samples;
    s8 pending_stream_start;
    u8 reserved_A9[3];
    u8 *work_end;
    const char *pending_filename;
    void *pending_directory;
    s32 pending_file_offset;
    s32 pending_file_sectors;
} ADXTHandle;

enum {
    ADXT_MAX_HANDLES = 16,
    ADXT_STATUS_STOP = 0,
    ADXT_STATUS_DECODING_HEADER = 1,
    ADXT_STATUS_BUFFERING = 2,
    ADXT_STATUS_PLAYING = 3,
    ADXT_STATUS_DRAINING = 4,
    ADXT_STATUS_PLAY_END = 5,
    ADXT_STREAM_TYPE_MEMORY = 2,
    ADXT_STREAM_TYPE_SJ = 3,
    ADXT_STREAM_TYPE_LINKED = 4,
    ADXT_SECTOR_SIZE = 0x800,
    ADXT_INPUT_EXTRA_SIZE = 0x24,
    ADXT_OUTPUT_SIZE = 0x2000,
    ADXT_OUTPUT_DISTANCE = 0x2060,
    ADXT_DEFAULT_PAN = -128
};

s32 fn_8004BA40(ADXTHandle *handle, s32 samples);

extern ADXTHandle lbl_80186B68[];
extern ADXTHandle lbl_80178CBC[];

extern s32 lbl_80178CB8;

extern void fn_80046738(void);

extern void fn_80046718(void);

extern void fn_80046738(void);

extern void ADXSTM_EntryEosFunc(ADXStream *stream, void (*callback)(void *object), void *object);

extern void fn_8004EE44(void);

extern s32 fn_8004ED84(AXRNAHandle *rna, s32 samples);

extern void fn_8004D220(ADXTHandle *handle);

void fn_8004C164(ADXTHandle *handle, s32 *sample_count, s32 *scale);

struct adx_tlkBss {
    s32 adxt_time_mode;
    s32 adxt_tsvr_enter_cnt;
    unsigned char padding_8[36];
    s32 adxt_time_unit;
};
extern struct adx_tlkBss lbl_8017E568;

static inline void adxt_ExecServers(struct adx_tlkBss *bss) {
    ADXTHandle *entry;
    s32 index;

    fn_80046738();
    if ((bss->adxt_tsvr_enter_cnt) != 0) {
        fn_80046718();
        return;
    }
    (bss->adxt_tsvr_enter_cnt) = 1;
    fn_80046718();
    fn_80046738();
    fn_80041700();
    (bss->adxt_tsvr_enter_cnt) = 2;
    entry = lbl_80178CBC;
    for (index = 0; index < ADXT_MAX_HANDLES; index++, entry++) {
        if (entry->used == 1) {
            fn_8004D220(entry);
        }
    }
    (bss->adxt_tsvr_enter_cnt) = 3;
    fn_8004EE44();
    (bss->adxt_tsvr_enter_cnt) = 0;
    fn_80046718();
}

s32 fn_8004BA40(ADXTHandle *handle, s32 samples) {
    s32 discarded;
    s32 count;
    s32 scale;
    s32 saved_time_mode;
    struct adx_tlkBss *bss = &lbl_8017E568;
    if (handle->paused == 0) {
        return 0;
    }
    discarded = fn_8004ED84(handle->rna, samples);
    adxt_ExecServers(bss);
    saved_time_mode = (bss->adxt_time_mode);
    (bss->adxt_time_mode) = 0;
    fn_8004C164(handle, &count, &scale);
    (bss->adxt_time_mode) = saved_time_mode;
    handle->playback_time = (u32)((f32)(bss->adxt_time_unit) * ((f32)count / (f32)scale));
    handle->playback_start_vsync = lbl_80178CB8;
    return discarded;
}
