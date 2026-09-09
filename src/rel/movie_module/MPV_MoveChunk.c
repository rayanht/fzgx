#include "types.h"
#include "sofdec/mpv.h"

int MPV_MoveChunk(SJ *stream, int channel, int size) {
    SJCK chunk;
    int source_channel = channel;
    channel = channel == 0;
    stream->interface->get_chunk(stream, source_channel, size, &chunk);
    stream->interface->put_chunk(stream, channel, &chunk);
    return chunk.len;
}
