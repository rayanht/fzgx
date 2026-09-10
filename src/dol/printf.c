
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

typedef struct MkVaListState {
    signed char gpr;
    signed char fpr;
    unsigned short reserved;
    char *input_arg_area;
    char *reg_save_area;
} __va_list[1];

typedef __va_list va_list;

extern FILE __files[4];

int fwide(FILE *file, int mode);

void __begin_critical_region(int region);

void __end_critical_region(int region);

int __pformatter(void *(*WriteProc)(void *, const char *, size_t), void *WriteProcArg,
                 const char *format_str, va_list arg);

void *__FileWrite(void *pFile, const char *pBuffer, size_t char_num);

int printf(const char *format, ...) {
    int ret;
    va_list args;
    if (fwide((&__files[1]), -1) >= 0) {
        return -1;
    }
    __begin_critical_region(2);
    ((void)(format), __builtin_va_info(&(args)));
    ret = __pformatter(&__FileWrite, (void *)(&__files[1]), format, args);
    ((void)0);
    __end_critical_region(2);
    return ret;
}
