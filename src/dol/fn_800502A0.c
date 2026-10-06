#include "types.h"

typedef struct Fn800502A0_Chunk {
    u8 *ptr;
    s32 len;
} Fn800502A0_Chunk;

typedef struct Fn800502A0_Stream Fn800502A0_Stream;

typedef struct Fn800502A0_StreamVtbl {
    u8 pad_0[0x18];
    void (*get_chunk)(Fn800502A0_Stream *, s32, s32, Fn800502A0_Chunk *);
    void (*unget_chunk)(Fn800502A0_Stream *, s32, Fn800502A0_Chunk *);
    void (*release_chunk)(Fn800502A0_Stream *, s32, Fn800502A0_Chunk *);
} Fn800502A0_StreamVtbl;

struct Fn800502A0_Stream {
    Fn800502A0_StreamVtbl *vtbl;
};

typedef struct Fn800502A0_BitReader {
    u8 pad_0[0x4];
    Fn800502A0_Stream *stream;
    u32 buffer;
    s32 bits_left;
    s32 bit_pos;
    u8 pad_14[0x4];
    s32 request;
    Fn800502A0_Chunk chunk;
    s32 avail;
    u8 *read_ptr;
} Fn800502A0_BitReader;

extern void fn_800589BC(Fn800502A0_Chunk *, s32, Fn800502A0_Chunk *, Fn800502A0_Chunk *);

void fn_800502A0(Fn800502A0_BitReader *reader) {
    Fn800502A0_Chunk used;
    Fn800502A0_Chunk rest;
    s32 space;
    s32 count;
    u32 value;
    u8 *p;

    space = (32 - reader->bits_left) / 8;
    if (reader->avail < 4) {
        used = reader->chunk;
        if (used.len != 0) {
            fn_800589BC(&used, used.len - reader->avail, &used, &rest);
            reader->stream->vtbl->release_chunk(reader->stream, 0, &used);
            reader->stream->vtbl->unget_chunk(reader->stream, 1, &rest);
        }
        reader->stream->vtbl->get_chunk(reader->stream, 1, reader->request, &reader->chunk);
        reader->read_ptr = reader->chunk.ptr;
        reader->avail = reader->chunk.len;
    }

    count = reader->avail;
    if (space < count) {
        count = space;
    }
    if (count == 3) {
        p = reader->read_ptr;
        value = reader->buffer;
        value = value << 8 | *p++;
        value = value << 8 | *p++;
        value = value << 8 | *p++;
        reader->read_ptr = p;
        reader->buffer = value;
        reader->bits_left += 24;
        reader->avail -= 3;
    } else if (count == 2) {
        p = reader->read_ptr;
        value = reader->buffer;
        value = value << 8 | *p++;
        value = value << 8 | *p++;
        reader->read_ptr = p;
        reader->buffer = value;
        reader->bits_left += 16;
        reader->avail -= 2;
    } else if (count == 1) {
        p = reader->read_ptr;
        value = reader->buffer;
        value = value << 8 | *p++;
        reader->read_ptr = p;
        reader->buffer = value;
        reader->bits_left += 8;
        reader->avail -= 1;
    } else if (count == 4) {
        p = reader->read_ptr;
        value = reader->buffer;
        value = value << 8 | *p++;
        value = value << 8 | *p++;
        value = value << 8 | *p++;
        value = value << 8 | *p++;
        reader->read_ptr = p;
        reader->buffer = value;
        reader->bits_left += 32;
        reader->avail -= 4;
    }
}
