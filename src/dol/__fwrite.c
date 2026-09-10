
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

void __stdio_atexit(void);

void __prep_buffer(FILE *file);

int __flush_buffer(FILE *file, size_t *bytes_flushed);

int fseek(FILE *file, u32 offset, int origin);

int fwide(FILE *file, int mode);

void *memcpy(void *destination, const void *source, unsigned long size);

extern void *__memrchr(const void *memory, int character, size_t count);

size_t __fwrite(const void *data, size_t member_size, size_t member_count, FILE *file) {
    const u8 *current;
    size_t remaining;
    size_t transferred;
    size_t count;
    int buffered;
    if (fwide(file, 0) == 0) {
        fwide(file, -1);
    }
    remaining = member_size * member_count;
    if (remaining == 0 || file->state.error || file->mode.bits.file_kind == 0) {
        return 0;
    }
    if (file->mode.bits.file_kind == 2) {
        __stdio_atexit();
    }
    buffered = !file->mode.bits.binary_io || file->mode.bits.buffer_mode == 2 ||
               file->mode.bits.buffer_mode == 1;
    if (file->state.io_state == 0 && (file->mode.bits.io_mode & 2)) {
        if ((file->mode.bits.io_mode & 4) && fseek(file, 0, 2) != 0) {
            return 0;
        }
        file->state.io_state = 1;
        __prep_buffer(file);
    }
    if (file->state.io_state != 1) {
        file->state.error = 1;
        file->buffer_length = 0;
        return 0;
    }
    current = data;
    transferred = 0;
    if (remaining != 0 && (file->buffer_ptr != file->buffer || buffered)) {
        file->buffer_length = file->buffer_size - (file->buffer_ptr - file->buffer);
        do {
            const u8 *newline = 0;
            count = file->buffer_length;
            if (count > remaining) {
                count = remaining;
            }
            if (file->mode.bits.buffer_mode == 1 && count != 0) {
                newline = __memrchr(current, '\n', count);
                if (newline != 0) {
                    count = newline + 1 - current;
                }
            }
            if (count != 0) {
                memcpy(file->buffer_ptr, current, count);
                current += count;
                transferred += count;
                remaining -= count;
                file->buffer_ptr += count;
                file->buffer_length -= count;
            }
            if ((file->buffer_length == 0 || newline != 0 || file->mode.bits.buffer_mode == 0) &&
                __flush_buffer(file, 0) != 0) {
                file->state.error = 1;
                file->buffer_length = 0;
                remaining = 0;
                break;
            }
        } while (remaining != 0 && buffered);
    }
    if (remaining != 0 && !buffered) {
        u8 *saved_buffer = file->buffer;
        size_t saved_size = file->buffer_size;
        file->buffer = (u8 *)current;
        file->buffer_size = remaining;
        file->buffer_ptr = (u8 *)current + remaining;
        if (__flush_buffer(file, &count) != 0) {
            file->state.error = 1;
            file->buffer_length = 0;
        }
        transferred += count;
        file->buffer = saved_buffer;
        file->buffer_size = saved_size;
        __prep_buffer(file);
        file->buffer_length = 0;
    }
    if (file->mode.bits.buffer_mode != 2) {
        file->buffer_length = 0;
    }
    return (transferred + member_size - 1) / member_size;
}
