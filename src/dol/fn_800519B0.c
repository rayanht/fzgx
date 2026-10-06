#include "types.h"

#define READ16(p) (((p)[0] << 8) | (p)[1])
#define READ32(p) (u32)(((p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | (p)[3])

typedef struct Fn800519B0_Loop {
    s16 type;
    s16 unk_2;
    u32 start_sample;
    u32 start_byte;
    u32 end_sample;
    u32 end_byte;
} Fn800519B0_Loop;

typedef struct Fn800519B0_Channel {
    s16 unk_0;
    s16 unk_2;
    s8 unk_4;
    s8 unk_5;
    s8 unk_6;
    s8 unk_7;
    s8 unk_8;
    s8 unk_9;
    s8 unk_A;
    s8 unk_B;
} Fn800519B0_Channel;

typedef struct Fn800519B0_Info {
    u8 encoding;
    u8 block_size;
    u8 bits;
    s8 channels;
    u32 sample_rate;
    u32 total_samples;
    u16 cutoff;
    s16 loop_count;
    Fn800519B0_Loop loops[1];
    Fn800519B0_Channel channel_info[1];
    u8 pad_30[0xC];
    u8 version;
    u8 flags;
} Fn800519B0_Info;

s32 fn_800519B0(u8 *data, s32 size, s32 *header_size, Fn800519B0_Info *info) {
    s32 offset;
    s32 i;
    u8 *p;

    if (header_size != NULL) {
        *header_size = 0;
    }
    if (size < 4) {
        return -1;
    }
    if ((u16)READ16(data) != 0x8000) {
        return -4;
    }
    offset = READ16(data + 2);
    if (header_size != NULL) {
        *header_size = offset;
    }
    if (info == NULL) {
        return 0;
    }
    if (size < offset + 4) {
        return -2;
    }
    offset -= 6;
    if (offset < 0x10) {
        return -2;
    }
    offset -= 0x10;
    info->encoding = data[4];
    info->block_size = data[5];
    info->bits = data[6];
    info->channels = data[7];
    info->sample_rate = READ32(data + 8);
    info->total_samples = READ32(data + 12);
    info->cutoff = READ16(data + 16);
    info->version = data[18];
    info->flags = data[19];
    if (offset < 4) {
        return -2;
    }
    p = data + 24;
    info->loop_count = READ16(data + 22);
    if (offset < info->loop_count * 0x14) {
        return -3;
    }
    for (i = 0; i < info->loop_count; i++) {
        info->loops[i].type = READ16(p);
        info->loops[i].unk_2 = READ16(p + 2);
        info->loops[i].start_sample = READ32(p + 4);
        info->loops[i].start_byte = READ32(p + 8);
        info->loops[i].end_sample = READ32(p + 12);
        info->loops[i].end_byte = READ32(p + 16);
    }
    offset -= info->loop_count * 0x14;
    for (i = 0; i < info->channels; i++) {
        if (offset < 0xC) {
            return 0;
        }
        info->channel_info[i].unk_0 = READ16(p);
        if (info->channel_info[i].unk_0 > 0) {
            info->channel_info[i].unk_2 = READ16(p + 2);
        }
        info->channel_info[i].unk_4 = p[4];
        if (info->channel_info[i].unk_4 > 0) {
            info->channel_info[i].unk_5 = p[5];
        }
        info->channel_info[i].unk_6 = p[6];
        if (info->channel_info[i].unk_6 > 0) {
            info->channel_info[i].unk_7 = p[7];
        }
        info->channel_info[i].unk_8 = p[8];
        if (info->channel_info[i].unk_8 > 0) {
            info->channel_info[i].unk_9 = p[9];
        }
        info->channel_info[i].unk_A = p[10];
        if (info->channel_info[i].unk_A > 0) {
            info->channel_info[i].unk_B = p[11];
        }
        p += 0xC;
        offset -= 0xC;
    }
    return 0;
}
