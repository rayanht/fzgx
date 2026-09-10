
#include "types.h"

typedef union AdxHeaderMagic {
    unsigned short value;
    struct {
        unsigned char high;
        unsigned char low;
    } bytes;
} AdxHeaderMagic;

typedef union AdxHeaderOffset {
    short value;
    struct {
        unsigned char high;
        unsigned char low;
    } bytes;
} AdxHeaderOffset;

typedef struct AdxHeader {
    AdxHeaderMagic magic;
    AdxHeaderOffset copyright_offset;
    unsigned char encoding;
    unsigned char block_size;
    unsigned char bits_per_sample;
    unsigned char channel_count;
    unsigned char sample_rate_0;
    unsigned char sample_rate_1;
    unsigned char sample_rate_2;
    unsigned char sample_rate_3;
    unsigned char total_samples_0;
    unsigned char total_samples_1;
    unsigned char total_samples_2;
    unsigned char total_samples_3;
    unsigned short highpass_frequency;
    unsigned char version;
    unsigned char flags;
    unsigned char reserved[4];
    unsigned short delay[4];
} AdxHeader;

static inline int decode_info_header(AdxHeader *header, int buffer_len, unsigned int *version) {
    int result = 0;
    if (buffer_len < 0x14) {
        result = -1;
    } else if (header->magic.value != 0x8000) {
        result = -2;
    } else if (header->copyright_offset.value < 0x10) {
        result = -1;
    } else {
        *version = header->version;
    }
    return result;
}

int ADX_DecodeInfoExLoop(signed char *buffer, int buffer_len, int *inserted_samples, short *num_loops,
                short *loop_type, int *start_sample, int *start_offset, int *end_sample,
                int *end_offset) {
    unsigned int version;
    int result;
    int required_len;
    int loop_offset;
    *num_loops = 0;
    result = decode_info_header((AdxHeader *)buffer, buffer_len, &version);
    if (result != 0) {
        return result;
    }
    required_len = version == 4 ? 0x3C : 0x30;
    if (buffer_len < required_len) {
        return -1;
    }
    if (*(const unsigned short *)buffer != 0x8000) {
        return -2;
    }
    if (*(const short *)(buffer + 2) < required_len - 4) {
        return -1;
    }
    loop_offset = 0x14;
    if (version == 4) {
        loop_offset = 0x20;
    }
    *inserted_samples = *(const short *)(buffer + loop_offset);
    loop_offset += 2;
    *num_loops = *(const short *)(buffer + loop_offset);
    loop_offset += 2;
    if (*num_loops != 1) {
        return -2;
    }
    loop_offset += 2;
    *loop_type = *(const short *)(buffer + loop_offset);
    loop_offset += 2;
    *start_sample = *(const int *)(buffer + loop_offset);
    loop_offset += 4;
    *start_offset = *(const int *)(buffer + loop_offset);
    loop_offset += 4;
    *end_sample = *(const int *)(buffer + loop_offset);
    loop_offset += 4;
    *end_offset = *(const int *)(buffer + loop_offset);
    return 0;
}
