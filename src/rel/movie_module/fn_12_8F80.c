
#include "types.h"

typedef struct SJCK {
    union {
        unsigned char padding_extent[8];
        struct {
            unsigned char *data;
        } view_data;
        struct {
            unsigned char padding_len[4];
            int len;
        } view_len;
    } fields;
} SJCK;

typedef struct SJ SJ;

typedef struct SJInterface SJInterface;

typedef void (*SJErrorCallback)(void *object, int error);

struct SJInterface {
    union {
        unsigned char padding_extent[48];
        struct {
            unsigned char padding_get_chunk[24];
            void (*get_chunk)(SJ *sj, int channel, int max_size, SJCK *chunk);
        } view_get_chunk;
        struct {
            unsigned char padding_unget_chunk[28];
            void (*unget_chunk)(SJ *sj, int channel, SJCK *chunk);
        } view_unget_chunk;
        struct {
            unsigned char padding_put_chunk[32];
            void (*put_chunk)(SJ *sj, int channel, SJCK *chunk);
        } view_put_chunk;
    } fields;
};

struct SJ {
    union {
        unsigned char padding_extent[4];
        struct {
            const SJInterface *interface;
        } view_interface;
    } fields;
};

typedef union DctFsriBlock {
    s16 samples[64];
    u32 packed[32];
} DctFsriBlock;

typedef struct DctFsriParams {
    s8 block_nonzero[6];
    u8 field_06[0x22];
    int coded_block_pattern;
    float *coefficients;
    DctFsriBlock **output_blocks;
    u8 field_34[0x14];
    float *workspace;
    u8 field_4C[8];
} DctFsriParams;

typedef struct MPVContext MPVContext;

typedef void (*MPVErrorCallback)(int object, int error);

typedef struct MPVErrorInfo {
    union {
        unsigned char padding_extent[20];
        struct {
            MPVErrorCallback callback;
        } view_callback;
    } fields;
} MPVErrorInfo;

typedef struct MPVMCContext MPVMCContext;

typedef void (*MPVMCFunction)(MPVMCContext *context);

struct MPVMCContext {
    MPVMCFunction functions08[4];
    u8 field_10[8];
    u8 *destination;
    u32 field_1c;
    s32 reference_stride;
    const u8 *reference0;
    const u8 *reference1;
    u8 field_2c[8];
    MPVMCFunction functions16[4];
};

typedef struct MPVPlaneSet {
    u8 *planes[3];
    s16 chroma_stride;
    s16 luma_stride;
} MPVPlaneSet;

typedef struct MPVOutputBlock {
    u8 *destination;
    s32 stride;
} MPVOutputBlock;

typedef struct MPVOutputBlocks {
    s32 count;
    MPVOutputBlock blocks[6];
} MPVOutputBlocks;

typedef struct MPVMacroblockSources {
    void *field_00;
    s16 *residual;
    u8 *prediction0;
    u8 *prediction1;
} MPVMacroblockSources;

typedef struct MPVYccPlane {
    u8 *chroma0;
    u8 *chroma1;
    u8 *luma;
    s16 chroma_stride;
    s16 luma_stride;
} MPVYccPlane;

typedef struct MPVMotionInfo {
    union {
        unsigned char padding_extent[36];
        struct {
            unsigned char padding_previous_horizontal[16];
            s32 previous_horizontal;
        } view_previous_horizontal;
        struct {
            unsigned char padding_previous_vertical[20];
            s32 previous_vertical;
        } view_previous_vertical;
        struct {
            unsigned char padding_horizontal[24];
            s32 horizontal;
        } view_horizontal;
        struct {
            unsigned char padding_vertical[28];
            s32 vertical;
        } view_vertical;
    } fields;
} MPVMotionInfo;

typedef struct MPVPictureAttributes {
    union {
        unsigned char padding_extent[104];
        struct {
            unsigned char padding_macroblocks_per_row[8];
            int macroblocks_per_row;
        } view_macroblocks_per_row;
    } fields;
} MPVPictureAttributes;

typedef struct MPVPictureInfo {
    MPVPictureAttributes attributes;
    u8 decoder_state[0x18];
} MPVPictureInfo;

typedef struct MPVFrameBuffers {
    MPVPlaneSet forward;
    MPVPlaneSet backward;
    u8 *output_rfb;
    MPVPictureInfo *picture_info;
    s32 decoded_dct_count;
    s32 skipped_dct_count;
} MPVFrameBuffers;

typedef struct MPVBitReader {
    union {
        unsigned char padding_extent[16];
        struct {
            u32 bits;
        } view_bits;
        struct {
            unsigned char padding_next_bits[4];
            u32 next_bits;
        } view_next_bits;
        struct {
            unsigned char padding_bit_offset[8];
            s32 bit_offset;
        } view_bit_offset;
        struct {
            unsigned char padding_words[12];
            const u32 *words;
        } view_words;
    } fields;
} MPVBitReader;

typedef struct MPVDecoderFields {
    union {
        unsigned char padding_extent[168];
        struct {
            unsigned char padding_field_1AC[28];
            s32 field_1AC;
        } view_field_1AC;
        struct {
            unsigned char padding_callback[32];
            void (*callback)(void *argument);
        } view_callback;
        struct {
            unsigned char padding_callback_argument[36];
            void *callback_argument;
        } view_callback_argument;
        struct {
            unsigned char padding_picture[64];
            MPVPictureAttributes picture;
        } view_picture;
    } fields;
} MPVDecoderFields;

typedef union MPVConditionState {
    union {
        unsigned char padding_extent[168];
        struct {
            MPVDecoderFields decoder;
        } view_decoder;
    } fields;
} MPVConditionState;

typedef struct MPVDctCounters {
    u8 field_078[0x18];
    s32 decoded;
    s32 skipped;
    u8 field_098[0x34];
} MPVDctCounters;

typedef union MPVDctState {
    DctFsriParams params;
    MPVDctCounters counters;
} MPVDctState;

typedef union MPVTransformWorkspace {
    float coefficients[9][64];
    DctFsriBlock blocks[6];
} MPVTransformWorkspace;

typedef struct MPVCodingBlock {
    union {
        unsigned char padding_extent[48];
        struct {
            unsigned char padding_quantizer_scale[36];
            s32 quantizer_scale;
        } view_quantizer_scale;
    } fields;
} MPVCodingBlock;

typedef struct MPVCodingWorkspace {
    MPVCodingBlock block;
    s32 non_intra_mode;
} MPVCodingWorkspace;

typedef struct MPVUserStream {
    union {
        unsigned char padding_extent[12];
        struct {
            unsigned char padding_callback[4];
            void (*callback)(void *argument, int index);
        } view_callback;
        struct {
            unsigned char padding_callback_argument[8];
            void *callback_argument;
        } view_callback_argument;
    } fields;
} MPVUserStream;

typedef struct MPVPictureUserBuffer {
    void *buffer;
    s32 capacity;
    s32 size;
} MPVPictureUserBuffer;

struct MPVContext {
    union {
        unsigned char padding_extent[4992];
        struct {
            MPVBitReader bit_reader;
        } view_bit_reader;
        struct {
            unsigned char padding_condition_state[400];
            MPVConditionState condition_state;
        } view_condition_state;
        struct {
            unsigned char padding_skip_macroblocks[664];
            void (*skip_macroblocks)(MPVContext *, int);
        } view_skip_macroblocks;
        struct {
            unsigned char padding_decode_intra_blocks[668];
            int (*decode_intra_blocks)(void *);
        } view_decode_intra_blocks;
        struct {
            unsigned char padding_decode_nonintra_blocks[672];
            int (*decode_nonintra_blocks)(void *);
        } view_decode_nonintra_blocks;
        struct {
            unsigned char padding_motion_intra[676];
            void (*motion_intra)(MPVContext *);
        } view_motion_intra;
        struct {
            unsigned char padding_motion_skipped[680];
            void (*motion_skipped)(MPVContext *);
        } view_motion_skipped;
        struct {
            unsigned char padding_quantizer_scale[700];
            u32 quantizer_scale;
        } view_quantizer_scale;
        struct {
            unsigned char padding_forward_motion[704];
            MPVMotionInfo forward_motion;
        } view_forward_motion;
        struct {
            unsigned char padding_backward_motion[740];
            MPVMotionInfo backward_motion;
        } view_backward_motion;
        struct {
            unsigned char padding_macroblock_index[776];
            s32 macroblock_index;
        } view_macroblock_index;
        struct {
            unsigned char padding_macroblock_row[824];
            s32 macroblock_row;
        } view_macroblock_row;
        struct {
            unsigned char padding_macroblock_column[828];
            s32 macroblock_column;
        } view_macroblock_column;
        struct {
            unsigned char padding_last_macroblock_index[780];
            s32 last_macroblock_index;
        } view_last_macroblock_index;
        struct {
            unsigned char padding_field_344[784];
            u32 field_344;
        } view_field_344;
        struct {
            unsigned char padding_cbp_mask[788];
            s32 cbp_mask;
        } view_cbp_mask;
        struct {
            unsigned char padding_dc_predictor_y[792];
            s32 dc_predictor_y;
        } view_dc_predictor_y;
        struct {
            unsigned char padding_dc_predictor_cb[796];
            s32 dc_predictor_cb;
        } view_dc_predictor_cb;
        struct {
            unsigned char padding_dc_predictor_cr[800];
            s32 dc_predictor_cr;
        } view_dc_predictor_cr;
        struct {
            unsigned char padding_header_chunk[4808];
            SJCK header_chunk;
        } view_header_chunk;
        struct {
            unsigned char padding_field_12d0[4816];
            s32 field_12d0;
        } view_field_12d0;
        struct {
            unsigned char padding_field_1310[4880];
            s32 field_1310;
        } view_field_1310;
        struct {
            unsigned char padding_field_1324[4852];
            s32 field_1324;
        } view_field_1324;
    } fields;
};

void fn_12_8F80(MPVContext *context, SJ *stream);

void fn_800589BC(const SJCK *source, int nbyte, SJCK *first, SJCK *remainder);

extern s16 *lbl_12_bss_6934;

extern s16 *lbl_12_bss_6930;

extern s16 *lbl_12_bss_6928;

extern s16 *lbl_12_bss_691C;

extern int MPV_GoNextDelimSj(SJ *stream);

int fn_12_9594(MPVBitReader *reader, MPVMotionInfo *motion, s32 *output, s32 *predictor);

static inline void mpvdec_InitMacroblockReader(const u8 *data, int extra_offset, const u32 **words,
                                               u32 *bits, u32 *next_bits, int *bit_offset) {
    *words = (const u32 *)((unsigned long)data & ~3UL);
    *bit_offset = (int)(data - (const u8 *)*words) * 8;
    *bits = (*words)[0];
    *next_bits = (*words)[1];
    *bits <<= *bit_offset;
    *words += 2;
    *bit_offset += extra_offset;
    if (*bit_offset >= 32) {
        *bit_offset -= 32;
        *bits = *next_bits << *bit_offset;
        *next_bits = *(*words)++;
    } else {
        *bits <<= extra_offset;
    }
}

#pragma opt_common_subs off
void fn_12_8F80(MPVContext *context, SJ *stream) {
    SJCK refill_remainder;
    SJCK final_remainder;
    int bit_offset;
    u32 bits;
    u32 next_bits;
    const u32 *words;
    u32 peek;
    u32 delta;
    u32 quantizer;
    int residual_offset;
    int consumed;
    int first_macroblock = 1;
    stream->fields.view_interface.interface->fields.view_get_chunk.get_chunk(
        stream, 1, 0x7FFFFFFF, &context->fields.view_header_chunk.header_chunk);
    mpvdec_InitMacroblockReader(
        context->fields.view_header_chunk.header_chunk.fields.view_data.data,
        context->fields.view_field_12d0.field_12d0, &words, &bits, &next_bits, &bit_offset);
    for (;;) {
        int old_index;
        s16 descriptor;
        peek = bits;
        peek = peek >> 9;
        if (bit_offset > 9) {
            peek |= next_bits >> (41 - bit_offset);
        }
        if (((0) == (peek))) {
            break;
        }
        old_index = context->fields.view_macroblock_index.macroblock_index;
        for (;;) {
            int descriptor;
            u8 code_length;
            u8 encoded_increment;
            int increment;
            peek = bits >> 21;
            if (bit_offset > 21) {
                peek |= next_bits >> (53 - bit_offset);
            }
            if ((peek >> 7) == 0) {
                descriptor = lbl_12_bss_6934[peek];
            } else {
                descriptor = lbl_12_bss_6930[peek >> 6];
            }
            code_length = descriptor & 0xF;
            bit_offset += code_length;
            if (bit_offset >= 32) {
                bit_offset -= 32;
                bits = next_bits << bit_offset;
                next_bits = *words++;
            } else {
                bits <<= code_length;
            }
            encoded_increment = (u32)descriptor >> 2;
            increment = encoded_increment >> 2;
            if (increment == 34) {
                continue;
            }
            if (increment == 35) {
                context->fields.view_macroblock_index.macroblock_index += 33;
                continue;
            }
            if (increment == 36) {
                delta = (u32)-2;
            } else {
                context->fields.view_macroblock_index.macroblock_index += increment;
                context->fields.view_field_344.field_344 = (u32)descriptor >> 10;
                if (context->fields.view_macroblock_index.macroblock_index >
                    context->fields.view_last_macroblock_index.last_macroblock_index) {
                    delta = (u32)-2;
                } else {
                    delta = context->fields.view_macroblock_index.macroblock_index - old_index;
                }
            }
            break;
        }
        if (delta == (u32)-2) {
            break;
        }
        if (!first_macroblock && delta > 1) {
            context->fields.view_skip_macroblocks.skip_macroblocks(context, delta);
            context->fields.view_dc_predictor_y.dc_predictor_y = 0x400;
            context->fields.view_dc_predictor_cr.dc_predictor_cr = 0x400;
            context->fields.view_dc_predictor_cb.dc_predictor_cb = 0x400;
        }
        if ((context->fields.view_field_344.field_344 & 0x20) == 0) {
            int descriptor;
            peek = bits >> 26;
            if (bit_offset > 26) {
                peek |= next_bits >> (58 - bit_offset);
            }
            descriptor = lbl_12_bss_6928[peek];
            context->fields.view_field_344.field_344 = (u32)descriptor >> 8;
            bit_offset += ((0xff) & (descriptor));
            if (bit_offset >= 32) {
                bit_offset -= 32;
                bits = next_bits << bit_offset;
                next_bits = *words++;
            } else {
                bits <<= descriptor & 0xff;
            }
        }
        if ((context->fields.view_field_344.field_344 & 0x10) != 0) {
            if (bit_offset >= 27) {
                bit_offset -= 27;
                if (bit_offset != 0) {
                    bits |= next_bits >> (5 - bit_offset);
                    quantizer = bits >> 27;
                    bits = next_bits << bit_offset;
                } else {
                    quantizer = bits >> 27;
                    bits = next_bits;
                }
                next_bits = *words++;
            } else {
                quantizer = bits >> 27;
                bits <<= 5;
                bit_offset += 5;
            }
            context->fields.view_quantizer_scale.quantizer_scale = quantizer;
        }
        if ((context->fields.view_field_344.field_344 & 8) != 0) {
            int horizontal_result;
            int vertical_result;
            context->fields.view_bit_reader.bit_reader.fields.view_bits.bits = bits;
            context->fields.view_bit_reader.bit_reader.fields.view_next_bits.next_bits = next_bits;
            context->fields.view_bit_reader.bit_reader.fields.view_bit_offset.bit_offset =
                bit_offset;
            context->fields.view_bit_reader.bit_reader.fields.view_words.words = words;
            horizontal_result =
                fn_12_9594(&context->fields.view_bit_reader.bit_reader,
                           &context->fields.view_forward_motion.forward_motion,
                           &context->fields.view_forward_motion.forward_motion.fields
                                .view_horizontal.horizontal,
                           &context->fields.view_forward_motion.forward_motion.fields
                                .view_previous_horizontal.previous_horizontal);
            vertical_result = fn_12_9594(
                &context->fields.view_bit_reader.bit_reader,
                &context->fields.view_forward_motion.forward_motion,
                &context->fields.view_forward_motion.forward_motion.fields.view_vertical.vertical,
                &context->fields.view_forward_motion.forward_motion.fields.view_previous_vertical
                     .previous_vertical);
            bits = context->fields.view_bit_reader.bit_reader.fields.view_bits.bits;
            next_bits = context->fields.view_bit_reader.bit_reader.fields.view_next_bits.next_bits;
            bit_offset =
                context->fields.view_bit_reader.bit_reader.fields.view_bit_offset.bit_offset;
            words = context->fields.view_bit_reader.bit_reader.fields.view_words.words;
            if ((horizontal_result | vertical_result) != 0) {
                break;
            }
        }
        if ((context->fields.view_field_344.field_344 & 4) != 0) {
            int horizontal_result;
            int vertical_result;
            context->fields.view_bit_reader.bit_reader.fields.view_bits.bits = bits;
            context->fields.view_bit_reader.bit_reader.fields.view_next_bits.next_bits = next_bits;
            context->fields.view_bit_reader.bit_reader.fields.view_bit_offset.bit_offset =
                bit_offset;
            context->fields.view_bit_reader.bit_reader.fields.view_words.words = words;
            horizontal_result =
                fn_12_9594(&context->fields.view_bit_reader.bit_reader,
                           &context->fields.view_backward_motion.backward_motion,
                           &context->fields.view_backward_motion.backward_motion.fields
                                .view_horizontal.horizontal,
                           &context->fields.view_backward_motion.backward_motion.fields
                                .view_previous_horizontal.previous_horizontal);
            vertical_result = fn_12_9594(
                &context->fields.view_bit_reader.bit_reader,
                &context->fields.view_backward_motion.backward_motion,
                &context->fields.view_backward_motion.backward_motion.fields.view_vertical.vertical,
                &context->fields.view_backward_motion.backward_motion.fields.view_previous_vertical
                     .previous_vertical);
            bits = context->fields.view_bit_reader.bit_reader.fields.view_bits.bits;
            next_bits = context->fields.view_bit_reader.bit_reader.fields.view_next_bits.next_bits;
            bit_offset =
                context->fields.view_bit_reader.bit_reader.fields.view_bit_offset.bit_offset;
            words = context->fields.view_bit_reader.bit_reader.fields.view_words.words;
            if ((horizontal_result | vertical_result) != 0) {
                break;
            }
        }
        if ((context->fields.view_field_344.field_344 & 2) != 0) {
            s16 descriptor;
            u8 code_length;
            peek = bits >> 23;
            if (bit_offset > 23) {
                peek |= next_bits >> (55 - bit_offset);
            }
            descriptor = lbl_12_bss_691C[peek];
            context->fields.view_cbp_mask.cbp_mask = ((u32)(u16)descriptor << 16) & 0xFFF00000;
            bit_offset += ((0xff) & (descriptor));
            if (bit_offset >= 32) {
                bit_offset -= 32;
                bits = next_bits << bit_offset;
                next_bits = *words++;
            } else {
                bits <<= ((0xff) & (descriptor));
            }
        } else {
            context->fields.view_cbp_mask.cbp_mask = 0;
        }
        context->fields.view_bit_reader.bit_reader.fields.view_bits.bits = bits;
        context->fields.view_bit_reader.bit_reader.fields.view_next_bits.next_bits = next_bits;
        context->fields.view_bit_reader.bit_reader.fields.view_bit_offset.bit_offset = bit_offset;
        context->fields.view_bit_reader.bit_reader.fields.view_words.words = words;
        if ((context->fields.view_field_344.field_344 & 1) != 0) {
            context->fields.view_decode_intra_blocks.decode_intra_blocks(context);
            context->fields.view_motion_intra.motion_intra(context);
            context->fields.view_forward_motion.forward_motion.fields.view_previous_horizontal
                .previous_horizontal = 0;
            context->fields.view_forward_motion.forward_motion.fields.view_previous_vertical
                .previous_vertical = 0;
            context->fields.view_forward_motion.forward_motion.fields.view_horizontal.horizontal =
                0;
            context->fields.view_forward_motion.forward_motion.fields.view_vertical.vertical = 0;
            context->fields.view_backward_motion.backward_motion.fields.view_previous_horizontal
                .previous_horizontal = 0;
            context->fields.view_backward_motion.backward_motion.fields.view_previous_vertical
                .previous_vertical = 0;
            context->fields.view_backward_motion.backward_motion.fields.view_horizontal.horizontal =
                0;
            context->fields.view_backward_motion.backward_motion.fields.view_vertical.vertical = 0;
        } else {
            void (**motion_modes)(MPVContext *) =
                &context->fields.view_motion_skipped.motion_skipped;
            context->fields.view_motion_skipped.motion_skipped =
                motion_modes[(context->fields.view_field_344.field_344 & 0xC) >> 2];
            if (context->fields.view_cbp_mask.cbp_mask != 0) {
                context->fields.view_decode_nonintra_blocks.decode_nonintra_blocks(context);
            }
            context->fields.view_motion_skipped.motion_skipped(context);
            context->fields.view_dc_predictor_y.dc_predictor_y = 0x400;
            context->fields.view_dc_predictor_cr.dc_predictor_cr = 0x400;
            context->fields.view_dc_predictor_cb.dc_predictor_cb = 0x400;
        }
        if (--context->fields.view_field_1324.field_1324 <= 0) {
            context->fields.view_field_1324.field_1324 =
                context->fields.view_condition_state.condition_state.fields.view_decoder.decoder
                    .fields.view_field_1AC.field_1AC;
            context->fields.view_condition_state.condition_state.fields.view_decoder.decoder.fields
                .view_callback.callback(
                    context->fields.view_condition_state.condition_state.fields.view_decoder.decoder
                        .fields.view_callback_argument.callback_argument);
        }
        bits = context->fields.view_bit_reader.bit_reader.fields.view_bits.bits;
        next_bits = context->fields.view_bit_reader.bit_reader.fields.view_next_bits.next_bits;
        bit_offset = context->fields.view_bit_reader.bit_reader.fields.view_bit_offset.bit_offset;
        words = context->fields.view_bit_reader.bit_reader.fields.view_words.words;
        residual_offset = ((7) & (bit_offset));
        consumed = ((const u8 *)(words - 2) + ((bit_offset - residual_offset + 7) >> 3)) -
                   (const u8 *)context->fields.view_header_chunk.header_chunk.fields.view_data.data;
        if (context->fields.view_header_chunk.header_chunk.fields.view_len.len - consumed <=
            0x800) {
            fn_800589BC(&context->fields.view_header_chunk.header_chunk, consumed,
                        &context->fields.view_header_chunk.header_chunk, &refill_remainder);
            stream->fields.view_interface.interface->fields.view_put_chunk.put_chunk(
                stream, 0, &context->fields.view_header_chunk.header_chunk);
            stream->fields.view_interface.interface->fields.view_unget_chunk.unget_chunk(
                stream, 1, &refill_remainder);
            stream->fields.view_interface.interface->fields.view_get_chunk.get_chunk(
                stream, 1, 0x7FFFFFFF, &context->fields.view_header_chunk.header_chunk);
            mpvdec_InitMacroblockReader(
                context->fields.view_header_chunk.header_chunk.fields.view_data.data,
                residual_offset, &words, &bits, &next_bits, &bit_offset);
        }
        first_macroblock = 0;
    }
    context->fields.view_field_12d0.field_12d0 = ((7) & (bit_offset));
    consumed = ((const u8 *)(words - 2) +
                ((bit_offset - context->fields.view_field_12d0.field_12d0 + 7) >> 3)) -
               (const u8 *)context->fields.view_header_chunk.header_chunk.fields.view_data.data;
    fn_800589BC(&context->fields.view_header_chunk.header_chunk, consumed,
                &context->fields.view_header_chunk.header_chunk, &final_remainder);
    stream->fields.view_interface.interface->fields.view_put_chunk.put_chunk(
        stream, 0, &context->fields.view_header_chunk.header_chunk);
    stream->fields.view_interface.interface->fields.view_unget_chunk.unget_chunk(stream, 1,
                                                                                 &final_remainder);
    MPV_GoNextDelimSj(stream);
}
#pragma opt_common_subs reset

