
#include "types.h"

typedef struct AdxXpndParams {
    int channel_count;
    const signed char *input;
    int num_blocks;
    short *output_left;
    short *output_right;
} AdxXpndParams;

typedef struct AdxXpnd {
    union {
        unsigned char padding_extent[60];
        struct {
            int used;
        } view_used;
    } fields;
} AdxXpnd;

typedef struct AdxDecodeParams {
    union {
        unsigned char padding_extent[44];
        struct {
            unsigned char padding_pcm_buffer[20];
            short *pcm_buffer;
        } view_pcm_buffer;
        struct {
            unsigned char padding_pcm_size[24];
            int pcm_size;
        } view_pcm_size;
        struct {
            unsigned char padding_pcm_distance[28];
            int pcm_distance;
        } view_pcm_distance;
    } fields;
} AdxDecodeParams;

typedef void (*AdxGetWriteInfo)(void *, int *, int *, int *);

typedef void (*AdxAddWriteInfo)(void *, int, int);

typedef struct AdxBasicDecoder {
    union {
        unsigned char padding_extent[160];
        struct {
            short used;
        } view_used;
        struct {
            unsigned char padding_expander[8];
            AdxXpnd *expander;
        } view_expander;
        struct {
            unsigned char padding_max_channels[56];
            int max_channels;
        } view_max_channels;
        struct {
            unsigned char padding_pcm_buffer[60];
            short *pcm_buffer;
        } view_pcm_buffer;
        struct {
            unsigned char padding_pcm_size[64];
            int pcm_size;
        } view_pcm_size;
        struct {
            unsigned char padding_pcm_distance[68];
            int pcm_distance;
        } view_pcm_distance;
        struct {
            unsigned char padding_get_write_info[120];
            AdxGetWriteInfo get_write_info;
        } view_get_write_info;
        struct {
            unsigned char padding_get_write_object[124];
            void *get_write_object;
        } view_get_write_object;
        struct {
            unsigned char padding_add_write_info[128];
            AdxAddWriteInfo add_write_info;
        } view_add_write_info;
        struct {
            unsigned char padding_add_write_object[132];
            void *add_write_object;
        } view_add_write_object;
    } fields;
} AdxBasicDecoder;

typedef struct AhxDecoder AhxDecoder;

typedef struct AdxBasicDecoderExt AdxBasicDecoderExt;

typedef void (*AdxDecodeNotify)(void *, int, int);

struct AdxBasicDecoderExt {
    union {
        unsigned char padding_extent[216];
        struct {
            AdxBasicDecoder base;
        } view_base;
        struct {
            unsigned char padding_ainf_length[188];
            int ainf_length;
        } view_ainf_length;
        struct {
            unsigned char padding_ainf[192];
            unsigned char ainf[16];
        } view_ainf;
        struct {
            unsigned char padding_default_out_volume[208];
            short default_out_volume;
        } view_default_out_volume;
        struct {
            unsigned char padding_default_pan[210];
            short default_pan[2];
        } view_default_pan;
    } fields;
};

void fn_8004E278(AdxXpnd *decoder);

AdxXpnd *ADXPD_Create(void);

void *memset(void *destination, int value, unsigned long size);

extern AdxBasicDecoderExt lbl_8017A29C[16];

void ADXB_Destroy(AdxBasicDecoderExt *);

void fn_80045F58(void *, int, int);

short *fn_80045F74(void *, int *, int *, int *);

static inline void ADXB_Destroy(AdxBasicDecoderExt *decoder) {
    AdxXpnd *expander;
    if (decoder != 0) {
        expander = decoder->fields.view_base.base.fields.view_expander.expander;
        decoder->fields.view_base.base.fields.view_expander.expander = 0;
        fn_8004E278(expander);
        memset(decoder, 0, sizeof(*decoder));
        decoder->fields.view_base.base.fields.view_used.used = 0;
    }
}

void fn_80045F58(void *object, int data_length, int samples);

short *fn_80045F74(void *object, int *write_position, int *room, int *loop_samples);

AdxBasicDecoderExt *ADXB_Create(int max_channels, short *pcm_buffer, int pcm_size,
                                int pcm_distance) {
    AdxBasicDecoderExt *decoder;
    int i;
    for (i = 0; i < 16; i++) {
        if (lbl_8017A29C[i].fields.view_base.base.fields.view_used.used == 0)
            break;
    }
    if (i == 16)
        return 0;
    decoder = &lbl_8017A29C[i];
    memset(decoder, 0, sizeof(*decoder));
    decoder->fields.view_base.base.fields.view_used.used = 1;
    decoder->fields.view_base.base.fields.view_expander.expander = ADXPD_Create();
    if (decoder->fields.view_base.base.fields.view_expander.expander == 0) {
        ADXB_Destroy(decoder);
        return 0;
    }
    decoder->fields.view_base.base.fields.view_max_channels.max_channels = max_channels;
    decoder->fields.view_base.base.fields.view_pcm_buffer.pcm_buffer = pcm_buffer;
    decoder->fields.view_base.base.fields.view_pcm_size.pcm_size = pcm_size;
    decoder->fields.view_base.base.fields.view_pcm_distance.pcm_distance = pcm_distance;
    decoder->fields.view_base.base.fields.view_get_write_info.get_write_info =
        (AdxGetWriteInfo)fn_80045F74;
    decoder->fields.view_base.base.fields.view_get_write_object.get_write_object = decoder;
    decoder->fields.view_base.base.fields.view_add_write_info.add_write_info = fn_80045F58;
    decoder->fields.view_base.base.fields.view_add_write_object.add_write_object = decoder;
    decoder->fields.view_ainf_length.ainf_length = 0;
    decoder->fields.view_default_out_volume.default_out_volume = 0;
    decoder->fields.view_default_pan.default_pan[0] = -128;
    decoder->fields.view_default_pan.default_pan[1] = -128;
    memset(decoder->fields.view_ainf.ainf, 0, sizeof(decoder->fields.view_ainf.ainf));
    return decoder;
}
