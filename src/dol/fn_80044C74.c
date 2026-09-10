
#include "types.h"

void *fn_80044C74(void *header, int length, int *rate, int *channels, int *bits, int *samples,
                  int *codec);

static inline s32 rd32(const unsigned char *p) {
    return p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
}

static inline unsigned int sw32(unsigned int v) {
    return v >> 24 | (v >> 8 & 0xFF00) | (v << 8 & 0xFF0000) | v << 24;
}

#pragma opt_common_subs off
void *fn_80044C74(void *header, int length, int *rate, int *channels, int *bits, int *samples,
                  int *codec) {
    unsigned int magic;
    unsigned int header_size;
    int encoding;
    int data_size;
    unsigned char *p = header;
    magic = rd32(p);
    p += 4;
    if (magic != 0x64732E) {
        if (magic != 0x646E732E)
            return ((void *)0);
    }
    header_size = rd32(p);
    header_size = sw32(header_size);
    p += 4;
    if ((int)header_size > length)
        return ((void *)0);
    data_size = rd32(p);
    data_size = sw32(data_size);
    p += 4;
    encoding = rd32(p);
    encoding = sw32(encoding);
    p += 4;
    switch (encoding) {
    case 1:
        *codec = 2;
        *bits = 8;
        break;
    case 2:
        *codec = 1;
        *bits = 8;
        break;
    case 3:
        *codec = 0;
        *bits = 16;
        break;
    default:
        return ((void *)0);
    }
    *rate = rd32(p);
    *rate = sw32(*rate);
    p += 4;
    *channels = rd32(p);
    *channels = sw32(*channels);
    p += 4;
    if (*codec == 2)
        *samples = data_size / *channels;
    else if (*codec == 1)
        *samples = data_size / *channels;
    else if (*codec == 0)
        *samples = (data_size / 2) / *channels;
    else
        *samples = 0x7FFF0000;
    return (unsigned char *)header + header_size;
}
#pragma opt_common_subs reset

