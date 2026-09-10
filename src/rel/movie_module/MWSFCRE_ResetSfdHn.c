
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

typedef int SfdCallbackObject;

typedef int SfdConditionValue;

typedef int SfdTransportValue;

typedef struct SfdHandle SfdHandle;

typedef int (*SfdUserIsSkipFn)(SfdHandle *handle, int picture_type, int value, int scale);

typedef int (*SfdTimeSourceFn)(SfdHandle *handle, int *value, int *scale);

typedef struct SfdPlaybackSettings {
    int values_00[5];
    int frame_rate_code;
    int values_18[10];
} SfdPlaybackSettings;

typedef struct SfdPlaybackRuntime {
    int decoded_pictures;
    int skipped_pictures;
    int field_08;
    int field_0C;
    int field_10;
    int field_14;
    int frame_outstanding;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    union {
        long long time_values[12];
        struct {
            long long reserved_time_values[3];
            struct {
                int high;
                unsigned int low;
            } input_flow;
            long long remaining_time_values[8];
        } timing;
    };
    int tail_values[4];
} SfdPlaybackRuntime;

typedef struct SfdTimerTimeUnit {
    int active;
    int fields_04[7];
    unsigned short field_20;
    unsigned short field_22;
    int value;
    int scale;
} SfdTimerTimeUnit;

typedef struct SfdTimerSkipState {
    SfdUserIsSkipFn callback;
    int fields_04[7];
    unsigned short field_20;
    unsigned short field_22;
    int value;
    int scale;
} SfdTimerSkipState;

typedef struct SfdTimerCompactTimeUnit {
    int fields_00[6];
    unsigned short field_18;
    unsigned short field_1A;
    int value;
    int scale;
} SfdTimerCompactTimeUnit;

typedef struct SfdTimerStreamTimeUnit {
    int active;
    int field_04;
    int file_size;
    int total_time_value;
    int total_time_scale;
    int byte_rate;
    int seek_position;
    int field_1C;
    unsigned short field_20;
    unsigned short field_22;
    int value;
    int scale;
} SfdTimerStreamTimeUnit;

typedef struct SfdTimerSampleHistory {
    int fields_00[3];
    int samples[32];
} SfdTimerSampleHistory;

typedef struct SfdTimerSampleWindow {
    int enabled;
    int fields_04[3];
    int samples[32];
} SfdTimerSampleWindow;

typedef int (*SfdExternalClockFn)(SfdCallbackObject object, int *value, int *scale);

typedef struct SfdTimerState {
    SfdTimeSourceFn time_sources[6];
    SfdTimerSkipState skip_state;
    SfdTimerCompactTimeUnit compact_time;
    SfdTimerTimeUnit field_0068;
    SfdTimerStreamTimeUnit stream_time;
    SfdTimerTimeUnit field_00C0;
    SfdTimerTimeUnit video_start_time;
    SfdTimerTimeUnit elapsed_time;
    int start_time_value;
    int start_time_scale;
    int field_014C;
    long long field_0150;
    long long audio_start_pts;
    SfdTimerSampleHistory sample_history;
    SfdTimerSampleWindow sample_window;
    int video_end_time_value;
    int video_end_time_scale;
    int field_0284;
    int field_0288;
    int current_time_value;
    int current_time_scale;
    int interval_time_last;
    int interval_time_estimate;
    int interval_time_max;
    int interval_time_min;
    int field_02A4;
    int video_clock_sample;
    int speed;
    int field_02B0;
    int field_02B4;
    int field_02B8;
    int frame_time_repeat_count;
    float previous_frame_time;
    int previous_frame_ready;
    float last_frame_time;
    int field_02CC;
    int previous_clock_sample;
    SfdExternalClockFn external_clock_callback;
    int previous_external_sample;
    int current_clock_sample;
    int clock_sample_scale;
    int external_clock_wrap;
    SfdCallbackObject external_clock_object;
    unsigned char unknown_02EC[0x2C4];
    unsigned int video_pts[3];
    unsigned char unknown_05BC[0x24];
} SfdTimerState;

typedef struct SfdSeekState {
    SfdHandle *source_handle;
    int field_04;
    int field_08;
    int field_0C;
} SfdSeekState;

typedef void (*SfdErrorCallback)(SfdCallbackObject object, int error);

typedef struct SfdErrorInfo {
    SfdErrorCallback callback;
    SfdCallbackObject callback_object;
    int first_error;
    int field_0C;
    int field_10;
} SfdErrorInfo;

typedef struct SfdHeaderState {
    int field_00;
    int field_04;
    int field_08;
    int field_0C;
    unsigned char unknown_0010[0x6C];
    int field_7C;
    unsigned char unknown_0080[0x10];
    int field_90;
} SfdHeaderState;

typedef struct SfdTimerSummary {
    long long total;
    long long minimum;
    long long maximum;
    int count;
    int field_1C;
} SfdTimerSummary;

typedef struct SfdTransportInterface SfdTransportInterface;

typedef struct SfdTransportSetup SfdTransportSetup;

typedef struct SfdVideoFrameState SfdVideoFrameState;

typedef void (*SfdBufferHandleCallback)(SfdHandle *handle, int stream_index);

typedef void (*SfdBufferObjectCallback)(SfdCallbackObject object, int stream_index);

typedef struct SfdBufferChannel {
    SJ *stream_joint;
    SfdCallbackObject object;
    SfdBufferHandleCallback handle_callback;
    SfdBufferObjectCallback object_callback;
} SfdBufferChannel;

typedef struct SfdPtsEntry {
    long long pts;
    unsigned char *data;
    int size;
} SfdPtsEntry;

typedef struct SfdPtsQueue {
    SfdPtsEntry *entries;
    int capacity;
    int count;
    int write_index;
    int read_index;
} SfdPtsQueue;

typedef struct SfdBufferRingWork {
    int field_00;
    SJ *stream_joint;
    unsigned char *buffer;
    int buffer_size;
    int field_10;
    int field_14;
    unsigned char *delimiter_position;
    unsigned char *delimiter_end;
    int write_total;
    int read_total;
    SfdPtsQueue pts_queue;
} SfdBufferRingWork;

typedef struct SfdBufferLinearWork {
    unsigned char *buffer;
    int buffer_size;
    int field_08;
    int field_0C;
    SfdVideoFrameState *video_frames;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
} SfdBufferLinearWork;

typedef union SfdBufferWork {
    SfdBufferRingWork ring;
    SfdBufferLinearWork linear;
    SfdBufferChannel user_channels[3];
    unsigned char raw[0x3C];
} SfdBufferWork;

typedef int (*SfdTransportLifecycleFn)(SfdHandle *handle);

typedef int (*SfdTransportPauseFn)(SfdHandle *handle, int state);

typedef int (*SfdTransportTransferFn)(SfdHandle *handle, SfdTransportValue parameter, int value);

typedef int (*SfdTransportBufferFn)(SfdHandle *handle, void *buffer);

struct SfdTransportInterface {
    SfdTransportLifecycleFn init;
    SfdTransportLifecycleFn finish;
    SfdTransportLifecycleFn exec_server;
    SfdTransportLifecycleFn create;
    SfdTransportLifecycleFn destroy;
    SfdTransportLifecycleFn standby;
    SfdTransportLifecycleFn start;
    SfdTransportLifecycleFn stop;
    SfdTransportPauseFn pause;
    SfdTransportBufferFn get_write;
    SfdTransportTransferFn add_write;
    SfdTransportBufferFn get_read;
    SfdTransportTransferFn add_read;
    SfdTransportTransferFn seek;
};

typedef struct SfdBufferState {
    int storage_mode;
    int active;
    int prepared;
    int terminated;
    SfdBufferWork work;
    int input_transport;
    int output_transport;
    unsigned char unknown_0054[0x20];
} SfdBufferState;

typedef struct SfdVideoFrameInfo {
    int width, height, macroblocks_per_row, macroblock_rows;
    int picture_type;
    int display_time_value, display_time_scale;
    int output_format;
    void *frame_buffer;
    int field_24, field_28, picture_order, field_30, field_34;
    void *picture_user_buffer;
    int field_3C, field_40, reserved_44, display_mode, reserved_4C;
    int field_50, field_54, field_58, field_5C, field_60, field_64;
    short field_68, field_6A;
    unsigned char fields_6C[0x0F];
    unsigned char reserved_7B[5];
} SfdVideoFrameInfo;

struct SfdVideoFrameState {
    int state;
    int field_04;
    union {
        unsigned char payload[0x80];
        SfdVideoFrameInfo info;
    } data;
};

typedef struct SfdBufferCreateConfig {
    const SfdTransportSetup *transport_setup;
    unsigned char *memory;
    int buffer_sizes[7];
    int field_24;
    int ring_alignment;
} SfdBufferCreateConfig;

typedef struct SfdCreateConfig {
    SfdBufferCreateConfig buffer;
    int picture_user_buffer_minimum;
    int maximum_width;
    int maximum_height;
    int video_output_format;
    unsigned char *handle_memory;
    int handle_memory_size;
} SfdCreateConfig;

typedef struct SfdTransportState {
    int prepared;
    int terminated;
    void *context;
    const SfdTransportInterface *interface;
    int parameter_10;
    int parameter_14;
    int parameter_18;
    int parameter_1C;
    int state;
    unsigned char unknown_0024[0x20];
} SfdTransportState;

typedef struct SfdUserOutputWork {
    int state;
    SfdBufferChannel channels[3];
} SfdUserOutputWork;

struct SfdTransportSetup {
    const SfdTransportInterface *entries[9];
};

typedef struct SfdAudioOutputCallbacks SfdAudioOutputCallbacks;

typedef void (*SfdAudioSetPanFn)(SfdHandle *, int, int, SfdAudioOutputCallbacks *);

typedef int (*SfdAudioGetPanFn)(SfdHandle *, int, SfdAudioOutputCallbacks *);

typedef void (*SfdAudioSetVolumeFn)(SfdHandle *, int, SfdAudioOutputCallbacks *);

typedef int (*SfdAudioGetVolumeFn)(SfdHandle *, SfdAudioOutputCallbacks *);

typedef void (*SfdAudioSetSpeedFn)(SfdHandle *, int);

struct SfdAudioOutputCallbacks {
    int reserved_00;
    SfdAudioSetPanFn set_pan;
    SfdAudioGetPanFn get_pan;
    SfdAudioSetVolumeFn set_volume;
    SfdAudioGetVolumeFn get_volume;
    SfdAudioSetSpeedFn set_speed;
    int reserved_18;
};

struct SfdHandle {
    SfdCreateConfig create_config;
    int field_0044;
    int playback_state;
    int requested_state;
    int field_0050;
    int field_0054;
    unsigned char unknown_0058[0x20];
    SfdHeaderState header_state;
    unsigned char unknown_010C[0x800];
    SfdPlaybackSettings playback_settings;
    int field_094C;
    SfdPlaybackRuntime playback_runtime;
    SfdErrorInfo error_info;
    SfdConditionValue conditions_primary[100];
    SfdConditionValue conditions_secondary[100];
    int field_0D24;
    SfdTimerState timer_state;
    SfdBufferState buffers[8];
    SfdVideoFrameState video_frames[16];
    SfdTransportState transports[9];
    unsigned char unknown_218C[4];
    unsigned char mps_work_storage[0x168];
    unsigned char unknown_22F8[0xA8];
    unsigned char mpv_work_storage[0xF80];
    unsigned char unknown_3320[0x154];
    SfdAudioOutputCallbacks audio_output_callbacks;
    SfdUserOutputWork user_output_work;
    int field_34C4;
    SfdSeekState seek_state;
    SfdTimerSummary timer_summaries[6];
};

typedef struct LSC LSC;

typedef struct SFXHandle SFXHandle;

typedef struct MwsPlayer MwsPlayer;

typedef struct MwsStHandle {
    int active;
    unsigned char reserved_004[8];
    SJ *stream;
    int element_id;
    void *backend;
} MwsStHandle;

typedef struct MwsPictureUserConfig {
    void *buffer;
    int buffer_size;
    int element_size;
} MwsPictureUserConfig;

struct MwsPlayer {
    const void *interface;
    int active;
    int status;
    int file_type;
    int maximum_bps;
    int width;
    int height;
    int frame_count;
    int decoder_count;
    void *create_work;
    int create_work_size;
    int composition_mode;
    int buffer_format;
    int create_field_28;
    int create_field_2C;
    int playback_mode;
    SfdHandle *sfd;
    void *stream;
    void *transport;
    LSC *loader;
    int field_050;
    int field_054;
    int field_058;
    int flow_limit;
    int field_060;
    unsigned char reserved_064[8];
    int field_06C;
    int field_070;
    signed char concat_play;
    signed char concat_stopped;
    signed char paused;
    unsigned char field_077;
    int entry_count;
    unsigned char reserved_07C[12];
    int field_088;
    unsigned char reserved_08C[0x20];
    SFXHandle *sfx;
    void *composition_work;
    int composition_work_size;
    unsigned char reserved_0B8[4];
    MwsPictureUserConfig internal_picture_user;
    unsigned char reserved_170[12];
    MwsPictureUserConfig *picture_user;
    void *picture_user_work;
    int picture_user_header_size;
    int picture_user_write;
    int picture_user_read;
    SJ *additional_info_sj;
    void *additional_info_buffer;
    int additional_info_buffer_size;
    unsigned char reserved_19C[0x1C];
    char *filename;
    int filename_capacity;
    int start_requested;
    int file_offset;
    int file_length;
    int file_end_position;
    SJ *supply_sj;
    SJ *input_sj;
    void *input_buffer;
    int input_buffer_size;
    int input_buffer_extra_size;
    int supply_mode;
    void *supply_buffer;
    int supply_buffer_size;
    int supply_buffer_extra_size;
    SJ *memory_sj;
    void *memory_buffer;
    int memory_buffer_size;
    void *arena;
    unsigned int arena_size;
    unsigned char *arena_cursor;
    unsigned int arena_used;
    int allocation_count;
    void *allocations[32];
    MwsStHandle sound;
    unsigned char reserved_2AC[8];
    int sound_state;
};

int fn_12_249BC(SfdHandle *handle, SfdErrorCallback callback, SfdCallbackObject object);

int fn_12_2B358(SfdHandle *handle);

extern int fn_12_38A0C(int);

extern void fn_12_388C4(SfdCallbackObject, int);

extern void MWSFSVM_Error(const char *, ...);

extern int fn_12_38AE0(void);

extern int fn_12_2A434(SfdHandle *, void *, int, int);

struct mwsfdcre____rodata_0 {
    unsigned char padding_0[580];
    const char picture_user_internal_error[54];
    unsigned char padding_670[2];
    const char create_picture_short_message[58];
    unsigned char padding_730[162];
    const char reset_stop_failed[49];
    unsigned char padding_937[3];
    const char reset_error_callback_failed[53];
};
extern struct mwsfdcre____rodata_0 lbl_12_rodata_1D88;

int MWSFCRE_ResetSfdHn(MwsPlayer *player) {
    struct mwsfdcre____rodata_0 *data = &lbl_12_rodata_1D88;

    MwsPictureUserConfig *config;
    int frame_count;
    int element_size;
    void *buffer;
    SfdHandle *sfd;
    sfd = player->sfd;
    if (fn_12_2B358(sfd) != 0) {
        MWSFSVM_Error((data->reset_stop_failed));
        return -1;
    }
    if (fn_12_249BC(sfd, fn_12_388C4, (SfdCallbackObject)player) != 0) {
        fn_12_38A0C(-0x12F);
        MWSFSVM_Error((data->reset_error_callback_failed));
        return -1;
    }
    config = player->picture_user;
    if (config == 0) {
        MWSFSVM_Error((data->picture_user_internal_error));
    } else {
        frame_count = player->frame_count;
        element_size = config->element_size;
        buffer = config->buffer;
        if (config->buffer_size < (frame_count + 3) * element_size) {
            MWSFSVM_Error((data->create_picture_short_message));
        } else if (fn_12_38AE0() == 1) {
            fn_12_2A434(player->sfd, buffer, frame_count + 3, element_size);
        }
    }
    return 0;
}
