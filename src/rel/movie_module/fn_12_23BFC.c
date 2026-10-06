#include "types.h"

typedef struct Fn12_23BFC_Header {
    u8 layer;
    u8 protection;
    u8 bitrate;
    u8 sample_rate;
    u8 padding;
    u8 private_bit;
    u8 mode;
    u8 mode_ext;
    u8 copyright;
    u8 original;
    u8 emphasis;
} Fn12_23BFC_Header;

typedef struct Fn12_23BFC_Info {
    u8 unk_0;
    u8 unk_1;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u8 channels;
    u32 sample_rate;
    u8 pad_30[0x10];
} Fn12_23BFC_Info;

extern const u32 lbl_12_rodata_ADC[4];
extern const u32 lbl_12_rodata_AEC[5];
extern Fn12_23BFC_Header lbl_12_bss_69B0;
extern void *memset(void *, int, u32);
extern s32 fn_12_2396C(u8 *, s32, Fn12_23BFC_Info *);
extern s32 fn_12_232DC(u8 *, s32, Fn12_23BFC_Info *);
extern s32 fn_12_23410(u8 *, s32, Fn12_23BFC_Info *);

static inline u8 *fn_12_23BFC_find_header(u8 *buf, s32 size, Fn12_23BFC_Header *header) {
    s32 i;

    for (i = 4; i <= size; i++, buf++) {
        if (buf[0] == 0xFF && (buf[1] & 0xF8) == 0xF8) {
            header->layer = (buf[1] >> 1) & 3;
            header->protection = buf[1] & 1;
            header->bitrate = (buf[2] >> 4) & 0xF;
            header->sample_rate = (buf[2] >> 2) & 3;
            header->padding = (buf[2] >> 1) & 1;
            header->private_bit = buf[2] & 1;
            header->mode = (buf[3] >> 6) & 3;
            header->mode_ext = (buf[3] >> 4) & 3;
            header->copyright = (buf[3] >> 3) & 1;
            header->original = (buf[3] >> 2) & 1;
            header->emphasis = buf[3] & 3;
            if (header->layer != 0 && header->bitrate != 15 && header->sample_rate != 3) {
                return buf;
            }
        }
    }
    return NULL;
}

static inline BOOL fn_12_23BFC_read_header(u8 *buf, s32 size, Fn12_23BFC_Info *info) {
    Fn12_23BFC_Header header;

    if (fn_12_23BFC_find_header(buf, size, &header) != NULL) {
        if (header.layer == 2 && header.bitrate != 0 && header.sample_rate == 0) {
            info->channels = lbl_12_rodata_ADC[header.mode];
            info->sample_rate = lbl_12_rodata_AEC[header.sample_rate];
        }
        lbl_12_bss_69B0 = header;
        return TRUE;
    }
    return FALSE;
}

void fn_12_23BFC(u8 *buf, s32 size, Fn12_23BFC_Info *info) {
    memset(info, 0, sizeof(Fn12_23BFC_Info));
    info->unk_0 = 0;
    info->unk_1 = 0;
    info->unk_4 = 0;
    info->unk_8 = 0;
    info->unk_C = 0;
    info->unk_10 = 0;
    info->unk_14 = 0;
    info->unk_18 = 0;
    info->unk_1C = 0;
    info->unk_20 = 0;
    info->unk_24 = 0;
    info->channels = 0;
    info->sample_rate = 0;
    if (fn_12_2396C(buf, size, info) != 0) {
        return;
    }
    if (fn_12_232DC(buf, size, info) != 0) {
        return;
    }
    if (fn_12_23410(buf, size, info) != 0) {
        return;
    }
    if (!fn_12_23BFC_read_header(buf, size, info)) {
        return;
    }
}
