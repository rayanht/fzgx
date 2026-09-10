
#include "types.h"

typedef u32 file_handle;

typedef u32 file_position;

typedef struct FileMode {
    u32 open_mode : 2;
    u32 io_mode : 3;
    u32 buffer_mode : 2;
    u32 file_kind : 3;
    u32 file_orientation : 2;
    u32 binary_io : 1;
} FileMode;

typedef union FileModeWord {
    u32 value;
    FileMode bits;
    u16 half[2];
} FileModeWord;

typedef struct FileState {
    u32 io_state : 3;
    u32 free_buffer : 1;
    u8 eof;
    u8 error;
} FileState;

typedef void (*IdleProc)(void);

typedef int (*PositionProc)(file_handle handle, file_position *position, int mode, IdleProc idle);

typedef int (*IOProc)(file_handle handle, u8 *buffer, size_t *count, IdleProc idle);

typedef int (*CloseProc)(file_handle handle);

typedef struct FILE {
    file_handle handle;
    FileModeWord mode;
    FileState state;
    u8 is_dynamically_allocated;
    u8 char_buffer;
    u8 char_buffer_overflow;
    u8 ungetc_buffer[2];
    u16 ungetc_wide_buffer[2];
    u32 position;
    u8 *buffer;
    u32 buffer_size;
    u8 *buffer_ptr;
    u32 buffer_length;
    u32 buffer_alignment;
    u32 saved_buffer_length;
    u32 buffer_position;
    PositionProc position_proc;
    IOProc read_proc;
    IOProc write_proc;
    CloseProc close_proc;
    IdleProc idle_proc;
    struct FILE *next_file;
} FILE;

int fn_8007F8D4(FILE *file);

void __begin_critical_region(int region);

void __end_critical_region(int region);

void *fn_8007A1C0(unsigned long size);

void fn_8007A150(void *allocation);

extern unsigned long fn_80085494(int base, int max_width, int (*read_proc)(void *, int, int),
                                 void *read_context, int *chars_scanned, int *negative,
                                 int *overflow);

extern unsigned long long fn_80085088(int base, int max_width, int (*read_proc)(void *, int, int),
                                      void *read_context, int *chars_scanned, int *negative,
                                      int *overflow);

int fn_8007EA58(FILE *file, char *buffer, int mode, size_t size) {
    int io_mode;
    io_mode = (file->mode.half[0] >> 6) & 7;
    if (mode == 0)
        fn_8007F8D4(file);
    if (file->state.io_state != 0 || io_mode == 0)
        return -1;
    if (mode != 0 && mode != 1 && mode != 2)
        return -1;
    if (file->buffer != 0 && file->state.free_buffer)
        fn_8007A150(file->buffer);
    __begin_critical_region(2);
    file->mode.bits.buffer_mode = mode;
    file->state.free_buffer = 0;
    file->buffer = (u8 *)&file->char_buffer;
    file->buffer_ptr = (u8 *)&file->char_buffer;
    file->buffer_size = 1;
    file->buffer_length = 0;
    file->buffer_alignment = 0;
    if (mode == 0 || size < 1) {
        *file->buffer_ptr = 0;
        __end_critical_region(2);
        return 0;
    }
    if (buffer == 0) {
        buffer = fn_8007A1C0(size);
        if (buffer == 0) {
            __end_critical_region(2);
            return -1;
        }
        file->state.free_buffer = 1;
    }
    file->buffer = (u8 *)buffer;
    file->buffer_ptr = file->buffer;
    file->buffer_size = size;
    file->buffer_alignment = 0;
    __end_critical_region(2);
    return 0;
}
