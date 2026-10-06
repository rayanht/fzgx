#include "types.h"

typedef struct Fn8004FF68_Stream Fn8004FF68_Stream;

typedef struct Fn8004FF68_StreamVtbl {
    u8 pad_0[0x24];
    s32 (*unk_24)(Fn8004FF68_Stream *, s32);
} Fn8004FF68_StreamVtbl;

struct Fn8004FF68_Stream {
    Fn8004FF68_StreamVtbl *vtbl;
};

typedef struct Fn8004FF68_BitReader {
    u8 pad_0[0x4];
    Fn8004FF68_Stream *stream;
    s32 buffer;
    s32 bits_left;
    s32 bit_pos;
    u8 pad_14[0x10];
    s32 eof;
} Fn8004FF68_BitReader;

extern u32 lbl_801309C0[];
extern u32 lbl_80186FA8;
extern void fn_800502A0(Fn8004FF68_BitReader *);

static inline void fn_8004FF68_SkipBits(Fn8004FF68_BitReader *reader, s32 count) {
    lbl_80186FA8++;
    if (reader->bits_left < count) {
        fn_800502A0(reader);
    }
    if (count > reader->bits_left) {
        reader->bit_pos += reader->bits_left;
        reader->bits_left = 0;
    } else {
        reader->bits_left -= count;
        reader->bit_pos += count;
    }
}

static inline u32 fn_8004FF68_GetBits(Fn8004FF68_BitReader *reader, s32 count) {
    u32 value;

    lbl_80186FA8++;
    if (reader->bits_left < count) {
        fn_800502A0(reader);
    }
    if (count > reader->bits_left) {
        reader->bit_pos += reader->bits_left;
        reader->bits_left = 0;
        value = 0;
    } else {
        value = reader->buffer >> (reader->bits_left - count);
        value &= lbl_801309C0[count];
        reader->bits_left -= count;
        reader->bit_pos += count;
    }
    return value;
}

static inline int fn_8004FF68_IsEnd(Fn8004FF68_BitReader *reader) {
    if (reader->stream->vtbl->unk_24(reader->stream, 1) == 0 && reader->bits_left == 0 && reader->eof == 0) {
        return 1;
    }
    return 0;
}

s32 fn_8004FF68(Fn8004FF68_BitReader *reader) {
    u32 bits;
    u32 mask = lbl_801309C0[12];

    if (reader->bit_pos & 7) {
        fn_8004FF68_SkipBits(reader, 8 - (reader->bit_pos & 7));
    }
    bits = fn_8004FF68_GetBits(reader, 12);
    while (!fn_8004FF68_IsEnd(reader)) {
        if ((bits & mask) == 0xFFF) {
            return 1;
        }
        if (bits == 0x8001000C) { /* fzgx-allow: A1 bit pattern of the scan window, not an address */
            return 2;
        }
        bits <<= 4;
        bits |= fn_8004FF68_GetBits(reader, 4);
    }
    return 0;
}
