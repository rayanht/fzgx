
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

typedef struct ADXStream ADXStream;

typedef struct LSCStreamInfo {
    s32 id;
    const char *filename;
    u32 filename_checksum;
    void *directory;
    s32 offset;
    s32 sector_count;
    s32 state;
    s32 read_sectors;
} LSCStreamInfo;

typedef struct LSCObject {
    s8 used;
    s8 state;
    s8 reading;
    s8 loop;
    s8 paused;
    u8 reserved_05;
    u16 reserved_06;
    SJ *sj;
    SJCK chunk;
    s32 minimum_buffer_size;
    s32 buffer_size;
    s32 write_position;
    s32 read_position;
    s32 stream_count;
    ADXStream *stream;
    s32 file_sectors;
    s32 requested_sectors;
    s32 error_count;
    LSCStreamInfo stream_info[16];
} LSCObject;

extern void fn_800565FC(const char *format, ...);

extern void fn_80056710(s32 *state);

extern void fn_800566F0(s32 *state);

extern void fn_8004AC58(ADXStream *stream);

static inline void lsc_ResetEntries(LSCObject *lsc) {
    if (lsc == 0) {
        fn_800565FC("E0003: Illigal parameter lsc=NULL\n");
    } else if (lsc->state == 0) {
        lsc->write_position = 0;
        lsc->read_position = 0;
        lsc->stream_count = 0;
    }
}

static inline void LSC_Stop(LSCObject *lsc) {
    if (lsc == 0) {
        fn_800565FC("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    if (lsc->state != 0) {
        lsc->state = 0;
        if (lsc->stream != 0 && lsc->reading == 1) {
            fn_8004AC58(lsc->stream);
            lsc->reading = 0;
        }
        lsc->file_sectors = 0;
        lsc_ResetEntries(lsc);
        lsc->error_count = 0;
    }
}

void fn_80056D8C(LSCObject *lsc) {
    s32 critical_state;
    if (lsc == 0) {
        fn_800565FC("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    fn_80056710(&critical_state);
    if (lsc->state != 0) {
        LSC_Stop(lsc);
    }
    if (lsc->stream_count > 0) {
        lsc->state = 2;
    } else {
        lsc->state = 1;
    }
    fn_800566F0(&critical_state);
}
