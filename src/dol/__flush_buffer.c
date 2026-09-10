
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

extern unsigned long __strtoul(int base, int max_width, int (*read_proc)(void *, int, int),
                                 void *read_context, int *chars_scanned, int *negative,
                                 int *overflow);

extern unsigned long long __strtoull(int base, int max_width, int (*read_proc)(void *, int, int),
                                      void *read_context, int *chars_scanned, int *negative,
                                      int *overflow);

int __flush_buffer(FILE *file, size_t *bytes_flushed) {
    size_t buffer_len;
    int io_result;
    buffer_len = file->buffer_ptr - file->buffer;
    if (buffer_len != 0) {
        file->buffer_length = buffer_len;
        io_result =
            file->write_proc(file->handle, file->buffer, &file->buffer_length, file->idle_proc);
        if (bytes_flushed != 0)
            *bytes_flushed = file->buffer_length;
        if (io_result != 0)
            return io_result;
        file->position += file->buffer_length;
    }
    file->buffer_ptr = file->buffer;
    file->buffer_length = file->buffer_size;
    file->buffer_length -= file->position & file->buffer_alignment;
    file->buffer_position = file->position;
    return 0;
}
