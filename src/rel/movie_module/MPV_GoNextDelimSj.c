#include "sofdec/mpv.h"

void fn_800589BC(const SJCK *source, int nbyte, SJCK *first, SJCK *remainder);

const unsigned char *fn_12_A0D8(const unsigned char *data, int length, int mask);

int fn_12_A2C4(const unsigned char *data);

int MPV_GoNextDelimSj(SJ *stream) {
    SJCK chunk;
    SJCK remainder;
    const u8 *delimiter;
    int delimiter_type;
    for (;;) {
        stream->interface->get_chunk(stream, 1, 0x7FFFFFFF, &chunk);
        if (chunk.len < 4) {
            stream->interface->unget_chunk(stream, 1, &chunk);
            delimiter_type = 0;
            break;
        }
        delimiter = fn_12_A0D8(chunk.data, chunk.len, -1);
        if (delimiter == 0) {
            fn_800589BC(&chunk, chunk.len - 3, &chunk, &remainder);
            stream->interface->put_chunk(stream, 0, &chunk);
            stream->interface->unget_chunk(stream, 1, &remainder);
            continue;
        }
        delimiter_type = fn_12_A2C4(delimiter);
        fn_800589BC(&chunk, delimiter - chunk.data, &chunk, &remainder);
        stream->interface->put_chunk(stream, 0, &chunk);
        stream->interface->unget_chunk(stream, 1, &remainder);
        break;
    }
    return delimiter_type;
}
