#include "types.h"

typedef struct MovieBuffer {
    u8 data[0x894];
} MovieBuffer;

typedef struct MovieData {
    u8 pad_00[0x0c];
    MovieBuffer buffer;
} MovieData;

typedef struct MovieModule {
    u8 pad_00[0x78];
    MovieBuffer buffer;
    u8 pad_90c[0x2908 - 0x90c];
    MovieData *movie;
} MovieModule;

extern int fn_12_24E94(MovieModule *self);
extern void fn_12_24570(void *data);

void fn_12_245C4(MovieModule *self) {
    MovieBuffer *copy;

    if (self->movie == 0) {
        copy = 0;
    } else if (fn_12_24E94(self) > 0) {
        copy = 0;
    } else {
        copy = &self->movie->buffer;
    }

    if (copy != 0) {
        self->buffer = *copy;
        fn_12_24570(self->buffer.data);
        *(u32 *)((u8 *)self + 0x930) = *(u32 *)((u8 *)self + 0x9c);
        *(u32 *)((u8 *)self + 0x934) = *(u32 *)((u8 *)self + 0xa0);
        *(u32 *)((u8 *)self + 0x938) = *(u32 *)((u8 *)self + 0xa4);
    }
}
