#include "sofdec/mpvabdec.h"

#define MPV_PEEK_BITS(output_)                                              \
    do {                                                                    \
        (output_) = bit_buffer;                                             \
        if (bit_count != 0) {                                               \
            (output_) |= next_buffer >> (32 - bit_count);                   \
        }                                                                   \
    } while (0)

#define MPV_FINISH_FROM(input_, number_)                                    \
    do {                                                                    \
        if (bit_count >= 32) {                                              \
            bit_count -= 32;                                                \
            bit_buffer = next_buffer << bit_count;                          \
            next_buffer = *stream++;                                        \
        } else {                                                            \
            bit_buffer = (input_) << (number_);                             \
        }                                                                   \
    } while (0)

#define MPV_FINISH_BITS(number_) MPV_FINISH_FROM(bit_buffer, number_)

#define MPV_CONSUME_BITS(number_)                                           \
    do {                                                                    \
        u32 consumed_bits = (u32)(number_);                                 \
        bit_count += consumed_bits;                                         \
        MPV_FINISH_BITS(consumed_bits);                                     \
    } while (0)

#define MPV_STORE_CURRENT(level_, negative_, intra_)                        \
    do {                                                                    \
        s32 scaled_level;                                                   \
        s32 quantized;                                                      \
        scaled_level = (((s32)(level_) * 2) + ((intra_) ? 0 : 1)) *         \
                       block->quantizer_scale;                              \
        quantized =                                                         \
            ((scaled_level *                                                \
              (s32)block->quant_matrix[block->current_scan]) >> 4) - 1;     \
        quantized |= 1;                                                     \
        if (negative_) {                                                    \
            quantized = -quantized;                                         \
        }                                                                   \
        block->coefficients->values[block->current_scan] =                  \
            (f32)quantized *                                                \
            ctx->coefficient_scale[block->current_scan];                    \
    } while (0)

/* General table entries carry their level and sign in the coding block. */
#define MPV_STORE_DECODED(intra_)                                           \
    do {                                                                    \
        s32 level_factor = (block->level * 2) + ((intra_) ? 0 : 1);        \
        s32 quantized;                                                      \
        quantized =                                                         \
            (((s32)block->quant_matrix[block->current_scan] *               \
              (level_factor *                  \
               block->quantizer_scale)) >> 4) - 1;                          \
        quantized |= 1;                                                     \
        if (block->sign) {                                                  \
            quantized = -quantized;                                         \
        }                                                                   \
        block->coefficients->values[block->current_scan] =                  \
            (f32)quantized * ctx->coefficient_scale[block->current_scan];   \
    } while (0)

#define MPV_STORE_AT(offset_, level_, negative_, intra_)                    \
    do {                                                                    \
        block->current_scan = (s32)scan[(offset_)];                         \
        MPV_STORE_CURRENT(level_, negative_, intra_);                       \
    } while (0)

#define MPV_DIRECT1_CONT(offset_, level_, negative_, bits_, intra_)         \
    do {                                                                    \
        block->current_scan = (s32)scan[(offset_)];                         \
        bit_count += (bits_);                                               \
        MPV_STORE_CURRENT(level_, negative_, intra_);                       \
        scan += (offset_);                                                  \
        MPV_FINISH_BITS(bits_);                                             \
    } while (0)

#define MPV_DIRECT2_CONT(offset1_, level1_, negative1_,                     \
                         offset2_, level2_, negative2_, bits_, intra_)      \
    do {                                                                    \
        block->current_scan = (s32)scan[(offset1_)];                        \
        bit_count += (bits_);                                               \
        MPV_STORE_CURRENT(level1_, negative1_, intra_);                     \
        MPV_STORE_AT(offset2_, level2_, negative2_, intra_);                \
        scan += (offset2_);                                                 \
        MPV_FINISH_BITS(bits_);                                             \
    } while (0)

#define MPV_DIRECT1_TERM(offset_, level_, negative_, bits_, intra_)         \
    do {                                                                    \
        block->current_scan = (s32)scan[(offset_)];                         \
        bit_count += (bits_);                                               \
        MPV_STORE_CURRENT(level_, negative_, intra_);                       \
        MPV_FINISH_BITS(bits_);                                             \
    } while (0)

#define MPV_DIRECT2_TERM(offset1_, level1_, negative1_,                     \
                         offset2_, level2_, negative2_, bits_, intra_)      \
    do {                                                                    \
        block->current_scan = (s32)scan[(offset1_)];                        \
        bit_count += (bits_);                                               \
        MPV_STORE_CURRENT(level1_, negative1_, intra_);                     \
        MPV_STORE_AT(offset2_, level2_, negative2_, intra_);                \
        MPV_FINISH_BITS(bits_);                                             \
    } while (0)

#define MPV_DECODE_ESCAPE(bits_)                                            \
    do {                                                                    \
        s32 packed;                                                         \
        packed = (u16)((bits_) >> 11);                                      \
        packed >>= 2;                                                       \
        block->run = (s32)(s8)((u32)packed >> 8);                           \
        packed = (s8)packed;                                                \
        block->code_length = 20;                                            \
        if ((packed & 0x7F) == 0) {                                         \
            s32 extended_base = packed * 2;                                \
            packed = extended_base | (u8)((bits_) >> 5);                    \
            block->code_length += 8;                                        \
        }                                                                   \
        if (packed < 0) {                                                   \
            packed = -packed;                                               \
            block->sign = 1;                                                \
        } else {                                                            \
            block->sign = 0;                                                \
        }                                                                   \
        block->level = packed;                                              \
    } while (0)

/* Cache metadata before publishing run; index arguments must have no side effects.
 * The lookahead is dead after this decoder and is consumed into the sign. */
#define MPV_DECODE_LONG(index_, bits_)                                      \
    do {                                                                    \
        u32 packed_code = ctx->run_level_8[(index_)];                       \
        block->run = (s32)(u8)ctx->run_level_8[(index_)];                   \
        if (block->run != 0x40) {                                           \
            block->code_length = packed_code >> 16;                         \
            block->level = (s32)(s8)(packed_code >> 8);                     \
            (bits_) >>= 33 - block->code_length;                            \
            (bits_) &= 1;                                                   \
            block->sign = (s32)(bits_);                                     \
        } else {                                                            \
            MPV_DECODE_ESCAPE(bits_);                                       \
        }                                                                   \
    } while (0)

/* The low index bit carries the coefficient sign, not a table-address bit. */
#define MPV_DECODE_SHORT(table_, index_, length_)                           \
    do {                                                                    \
        s32 short_entry;                                                    \
        block->code_length = (length_);                                     \
        short_entry = (table_)[((index_) & ~1U) >> 1];                      \
        block->run = (s32)(u8)short_entry;                                  \
        block->level = (s32)(s8)((u32)short_entry >> 8);                    \
        block->sign = (s32)((index_) & 1);                                  \
    } while (0)

/* Rare-code decoding consumes its lookahead word into the signed table index. */
#define MPV_DECODE_RARE(bits_, has_14_bit_)                                 \
    do {                                                                    \
        s32 short_entry;                                                    \
        if ((has_14_bit_) && ((bits_) >> 24) != 0) {                        \
            (bits_) = (bits_) >> 19;                                        \
            block->code_length = 14;                                        \
            short_entry = ctx->run_level_1[((bits_) & ~1U) >> 1];           \
        } else if ((s32)((bits_) << 8) < 0) {                               \
            (bits_) = ((bits_) >> 18) & 0x1F;                               \
            block->code_length = 15;                                        \
            short_entry = ctx->run_level_0a[((bits_) & ~1U) >> 1];          \
        } else if ((s32)((bits_) << 9) < 0) {                               \
            (bits_) = ((bits_) >> 17) & 0x1F;                               \
            block->code_length = 16;                                        \
            short_entry = ctx->run_level_0b[((bits_) & ~1U) >> 1];          \
        } else {                                                            \
            (bits_) = ((bits_) >> 16) & 0x1F;                               \
            block->code_length = 17;                                        \
            short_entry = ctx->run_level_0c[((bits_) & ~1U) >> 1];          \
        }                                                                   \
        block->run = (s32)(u8)short_entry;                                  \
        block->level = (s32)(s8)((u32)short_entry >> 8);                    \
        block->sign = (s32)((bits_) & 1);                                   \
    } while (0)

/* Align raw AC lookahead to the escape decoder's bit window. */
static inline u32 mpvabdec_AlignEscapeLookahead(u32 lookahead)
{
    return lookahead << 1;
}

/* Keep the first-code helper expanded into the large, call-free decoder. */
#pragma inline_max_size(100000)
#pragma inline_max_total_size(100000)
static inline void mpvabdec_DecodeFirst(MPVABDECContext* ctx,
                                      MPVABDECBlock* block, u32 initial_buffer,
                                      u32 next_buffer, s32 bit_count)
{
    u32 initial_peek = initial_buffer;
    u32 prefix;
    s32 short_entry;

    if (bit_count != 0) {
        initial_peek |= next_buffer >> (32 - bit_count);
    }
    if ((s32)initial_peek < 0) {
        block->sign = (s32)((initial_peek >> 30) & 1);
        block->level = 1;
        block->run = 0;
        block->code_length = 2;
        return;
    }
    initial_peek <<= 1;
    prefix = initial_peek >> 24;
    switch ((s32)prefix) {
    default:
        MPV_DECODE_LONG(prefix >> 1, initial_peek);
        return;
    case 4: case 5: case 6: case 7:
        initial_peek >>= 22;
        block->code_length = 11;
        short_entry = ctx->run_level_4[(initial_peek & ~1U) >> 1];
        break;
    case 2: case 3:
        initial_peek >>= 20;
        block->code_length = 13;
        short_entry = ctx->run_level_2[(initial_peek & ~1U) >> 1];
        break;
    case 1:
        initial_peek >>= 19;
        block->code_length = 14;
        short_entry = ctx->run_level_1[(initial_peek & ~1U) >> 1];
        break;
    case 0:
        if ((s32)(initial_peek << 8) < 0) {
            initial_peek = (initial_peek >> 18) & 0x1F;
            block->code_length = 15;
            short_entry = ctx->run_level_0a[(initial_peek & ~1U) >> 1];
        } else if ((s32)(initial_peek << 9) < 0) {
            initial_peek = (initial_peek >> 17) & 0x1F;
            block->code_length = 16;
            short_entry = ctx->run_level_0b[(initial_peek & ~1U) >> 1];
        } else {
            initial_peek = (initial_peek >> 16) & 0x1F;
            block->code_length = 17;
            short_entry = ctx->run_level_0c[(initial_peek & ~1U) >> 1];
        }
        break;
    }
    block->run = (s32)(u8)short_entry;
    block->level = (s32)(s8)((u32)short_entry >> 8);
    block->sign = (s32)(initial_peek & 1);
}

/* Advance the reader after decoding the first coefficient. */
static inline u32 mpvabdec_AdvanceFirst(u32 initial_buffer, u32 consumed_bits,
                                      s32* bit_count, u32* next_buffer,
                                      const u32** stream)
{
    u32 bit_buffer;
    *bit_count += consumed_bits;
    if (*bit_count >= 32) {
        *bit_count -= 32;
        bit_buffer = *next_buffer << *bit_count;
        *next_buffer = *(*stream)++;
    } else {
        bit_buffer = initial_buffer << consumed_bits;
    }
    return bit_buffer;
}

/* Store the first decoded coefficient, decode the rest, and publish reader state. */
static inline s32 mpvabdec_DecodeNonIntraAC(MPVABDECContext* ctx,
                                         MPVABDECBlock* block,
                                         u32 bit_buffer, u32 next_buffer,
                                         s32 bit_count, const u32* stream)
{
    const s8* scan;
    s32 scan_result;
    scan = ctx->scan + block->run;
    block->current_scan = block->first_scan = (s32)*scan;
    MPV_STORE_DECODED(0);

    do {
        u32 peek;
        u32 index;
        MPV_PEEK_BITS(peek);
        switch (peek >> 24) {
        case 0xFC:
        case 0xFD:
        case 0xFF:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 1, 1, 6, 0);
            continue;
        case 0xF8:
        case 0xF9:
        case 0xFB:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 1, 0, 6, 0);
            continue;
        case 0xEE:
        case 0xEF:
            MPV_DIRECT2_CONT(1, 1, 1, 3, 1, 1, 7, 0);
            continue;
        case 0xEC:
        case 0xED:
            MPV_DIRECT2_CONT(1, 1, 1, 3, 1, 0, 7, 0);
            continue;
        case 0xEB:
            MPV_DIRECT2_CONT(1, 1, 1, 4, 1, 1, 8, 0);
            continue;
        case 0xEA:
            MPV_DIRECT2_CONT(1, 1, 1, 4, 1, 0, 8, 0);
            continue;
        case 0xE9:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 2, 1, 8, 0);
            continue;
        case 0xE8:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 2, 0, 8, 0);
            continue;
        case 0xE0:
        case 0xE1:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
            MPV_DIRECT1_CONT(1, 1, 1, 3, 0);
            continue;
        case 0xDC:
        case 0xDD:
        case 0xDF:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 1, 1, 6, 0);
            continue;
        case 0xD8:
        case 0xD9:
        case 0xDB:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 1, 0, 6, 0);
            continue;
        case 0xCE:
        case 0xCF:
            MPV_DIRECT2_CONT(1, 1, 0, 3, 1, 1, 7, 0);
            continue;
        case 0xCC:
        case 0xCD:
            MPV_DIRECT2_CONT(1, 1, 0, 3, 1, 0, 7, 0);
            continue;
        case 0xCB:
            MPV_DIRECT2_CONT(1, 1, 0, 4, 1, 1, 8, 0);
            continue;
        case 0xCA:
            MPV_DIRECT2_CONT(1, 1, 0, 4, 1, 0, 8, 0);
            continue;
        case 0xC9:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 2, 1, 8, 0);
            continue;
        case 0xC8:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 2, 0, 8, 0);
            continue;
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC4:
        case 0xC5:
        case 0xC6:
        case 0xC7:
            MPV_DIRECT1_CONT(1, 1, 0, 3, 0);
            continue;
        case 0x7E:
        case 0x7F:
            MPV_DIRECT2_CONT(2, 1, 1, 3, 1, 1, 7, 0);
            continue;
        case 0x7C:
        case 0x7D:
            MPV_DIRECT2_CONT(2, 1, 1, 3, 1, 0, 7, 0);
            continue;
        case 0x77:
            MPV_DIRECT2_CONT(2, 1, 1, 4, 1, 1, 8, 0);
            continue;
        case 0x76:
            MPV_DIRECT2_CONT(2, 1, 1, 4, 1, 0, 8, 0);
            continue;
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
            MPV_DIRECT1_CONT(2, 1, 1, 4, 0);
            continue;
        case 0x6E:
        case 0x6F:
            MPV_DIRECT2_CONT(2, 1, 0, 3, 1, 1, 7, 0);
            continue;
        case 0x6C:
        case 0x6D:
            MPV_DIRECT2_CONT(2, 1, 0, 3, 1, 0, 7, 0);
            continue;
        case 0x67:
            MPV_DIRECT2_CONT(2, 1, 0, 4, 1, 1, 8, 0);
            continue;
        case 0x66:
            MPV_DIRECT2_CONT(2, 1, 0, 4, 1, 0, 8, 0);
            continue;
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
            MPV_DIRECT1_CONT(2, 1, 0, 4, 0);
            continue;
        case 0x5F:
            MPV_DIRECT2_CONT(3, 1, 1, 4, 1, 1, 8, 0);
            continue;
        case 0x5E:
            MPV_DIRECT2_CONT(3, 1, 1, 4, 1, 0, 8, 0);
            continue;
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
            MPV_DIRECT1_CONT(3, 1, 1, 5, 0);
            continue;
        case 0x57:
            MPV_DIRECT2_CONT(3, 1, 0, 4, 1, 1, 8, 0);
            continue;
        case 0x56:
            MPV_DIRECT2_CONT(3, 1, 0, 4, 1, 0, 8, 0);
            continue;
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
            MPV_DIRECT1_CONT(3, 1, 0, 5, 0);
            continue;
        case 0x4F:
            MPV_DIRECT2_CONT(1, 2, 1, 2, 1, 1, 8, 0);
            continue;
        case 0x4E:
            MPV_DIRECT2_CONT(1, 2, 1, 2, 1, 0, 8, 0);
            continue;
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
            MPV_DIRECT1_CONT(1, 2, 1, 5, 0);
            continue;
        case 0x47:
            MPV_DIRECT2_CONT(1, 2, 0, 2, 1, 1, 8, 0);
            continue;
        case 0x46:
            MPV_DIRECT2_CONT(1, 2, 0, 2, 1, 0, 8, 0);
            continue;
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            MPV_DIRECT1_CONT(1, 2, 0, 5, 0);
            continue;
        case 0x3C:
        case 0x3D:
        case 0x3F:
            MPV_DIRECT1_CONT(4, 1, 1, 6, 0);
            continue;
        case 0x38:
        case 0x39:
        case 0x3B:
            MPV_DIRECT1_CONT(4, 1, 0, 6, 0);
            continue;
        case 0x34:
        case 0x35:
        case 0x37:
            MPV_DIRECT1_CONT(5, 1, 1, 6, 0);
            continue;
        case 0x30:
        case 0x31:
        case 0x33:
            MPV_DIRECT1_CONT(5, 1, 0, 6, 0);
            continue;
        case 0x2C:
        case 0x2D:
        case 0x2F:
            MPV_DIRECT1_CONT(1, 3, 1, 6, 0);
            continue;
        case 0x28:
        case 0x29:
        case 0x2B:
            MPV_DIRECT1_CONT(1, 3, 0, 6, 0);
            continue;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
            peek <<= 1;
            index = peek >> 25;
            MPV_DECODE_LONG(index, peek);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(0);
            continue;
        case 0x1E:
        case 0x1F:
            MPV_DIRECT1_CONT(6, 1, 1, 7, 0);
            continue;
        case 0x1C:
        case 0x1D:
            MPV_DIRECT1_CONT(6, 1, 0, 7, 0);
            continue;
        case 0x1A:
        case 0x1B:
            MPV_DIRECT1_CONT(2, 2, 1, 7, 0);
            continue;
        case 0x18:
        case 0x19:
            MPV_DIRECT1_CONT(2, 2, 0, 7, 0);
            continue;
        case 0x16:
        case 0x17:
            MPV_DIRECT1_CONT(7, 1, 1, 7, 0);
            continue;
        case 0x14:
        case 0x15:
            MPV_DIRECT1_CONT(7, 1, 0, 7, 0);
            continue;
        case 0x12:
        case 0x13:
            MPV_DIRECT1_CONT(8, 1, 1, 7, 0);
            continue;
        case 0x10:
        case 0x11:
            MPV_DIRECT1_CONT(8, 1, 0, 7, 0);
            continue;
        case 0x0F:
            MPV_DIRECT1_CONT(9, 1, 1, 8, 0);
            continue;
        case 0x0E:
            MPV_DIRECT1_CONT(9, 1, 0, 8, 0);
            continue;
        case 0x0D:
            MPV_DIRECT1_CONT(1, 4, 1, 8, 0);
            continue;
        case 0x0C:
            MPV_DIRECT1_CONT(1, 4, 0, 8, 0);
            continue;
        case 0x0B:
            MPV_DIRECT1_CONT(10, 1, 1, 8, 0);
            continue;
        case 0x0A:
            MPV_DIRECT1_CONT(10, 1, 0, 8, 0);
            continue;
        case 0x09:
            MPV_DIRECT1_CONT(3, 2, 1, 8, 0);
            continue;
        case 0x08:
            MPV_DIRECT1_CONT(3, 2, 0, 8, 0);
            continue;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            {
                u32 escape_bits = mpvabdec_AlignEscapeLookahead(peek);
                MPV_DECODE_ESCAPE(escape_bits);
            }
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(0);
            MPV_CONSUME_BITS(block->code_length);
            continue;
        case 0x02:
        case 0x03:
            index = (peek >> 21) & 0x3FF;
            MPV_DECODE_SHORT(ctx->run_level_4, index, 11);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(0);
            continue;
        case 0x01:
            index = (peek >> 19) & 0xFFF;
            MPV_DECODE_SHORT(ctx->run_level_2, index, 13);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(0);
            continue;
        case 0x00:
            peek <<= 1;
            MPV_DECODE_RARE(peek, 1);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(0);
            continue;
        case 0xFE:
            MPV_DIRECT2_TERM(1, 1, 1, 2, 1, 1, 8, 0);
            break;
        case 0xFA:
            MPV_DIRECT2_TERM(1, 1, 1, 2, 1, 0, 8, 0);
            break;
        case 0xF0:
        case 0xF1:
        case 0xF2:
        case 0xF3:
        case 0xF4:
        case 0xF5:
        case 0xF6:
        case 0xF7:
            MPV_DIRECT1_TERM(1, 1, 1, 5, 0);
            break;
        case 0xDE:
            MPV_DIRECT2_TERM(1, 1, 0, 2, 1, 1, 8, 0);
            break;
        case 0xDA:
            MPV_DIRECT2_TERM(1, 1, 0, 2, 1, 0, 8, 0);
            break;
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            MPV_DIRECT1_TERM(1, 1, 0, 5, 0);
            break;
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
        case 0x86:
        case 0x87:
        case 0x88:
        case 0x89:
        case 0x8A:
        case 0x8B:
        case 0x8C:
        case 0x8D:
        case 0x8E:
        case 0x8F:
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x96:
        case 0x97:
        case 0x98:
        case 0x99:
        case 0x9A:
        case 0x9B:
        case 0x9C:
        case 0x9D:
        case 0x9E:
        case 0x9F:
        case 0xA0:
        case 0xA1:
        case 0xA2:
        case 0xA3:
        case 0xA4:
        case 0xA5:
        case 0xA6:
        case 0xA7:
        case 0xA8:
        case 0xA9:
        case 0xAA:
        case 0xAB:
        case 0xAC:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB0:
        case 0xB1:
        case 0xB2:
        case 0xB3:
        case 0xB4:
        case 0xB5:
        case 0xB6:
        case 0xB7:
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBB:
        case 0xBC:
        case 0xBD:
        case 0xBE:
        case 0xBF:
            MPV_CONSUME_BITS(2);
            break;
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
            MPV_DIRECT1_TERM(2, 1, 1, 6, 0);
            break;
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
            MPV_DIRECT1_TERM(2, 1, 0, 6, 0);
            break;
        case 0x5C:
        case 0x5D:
            MPV_DIRECT1_TERM(3, 1, 1, 7, 0);
            break;
        case 0x54:
        case 0x55:
            MPV_DIRECT1_TERM(3, 1, 0, 7, 0);
            break;
        case 0x4C:
        case 0x4D:
            MPV_DIRECT1_TERM(1, 2, 1, 7, 0);
            break;
        case 0x44:
        case 0x45:
            MPV_DIRECT1_TERM(1, 2, 0, 7, 0);
            break;
        case 0x3E:
            MPV_DIRECT1_TERM(4, 1, 1, 8, 0);
            break;
        case 0x3A:
            MPV_DIRECT1_TERM(4, 1, 0, 8, 0);
            break;
        case 0x36:
            MPV_DIRECT1_TERM(5, 1, 1, 8, 0);
            break;
        case 0x32:
            MPV_DIRECT1_TERM(5, 1, 0, 8, 0);
            break;
        case 0x2E:
            MPV_DIRECT1_TERM(1, 3, 1, 8, 0);
            break;
        case 0x2A:
            MPV_DIRECT1_TERM(1, 3, 0, 8, 0);
            break;
        }
        break;
    } while (1);

    ctx->bit_buffer = bit_buffer;
    ctx->next_buffer = next_buffer;
    ctx->bit_count = bit_count;
    ctx->stream = stream;

    scan_result = block->current_scan;
    if (scan_result != block->first_scan) {
        scan_result = -scan_result;
    }
    block->current_scan = scan_result;
    return block->current_scan;
}

/* Decode and publish a non-intra block after its coefficient storage is cleared. */
static inline s32 mpvabdec_DecodeNonIntra(MPVABDECContext* ctx, MPVABDECBlock* block)
{
    u32 initial_buffer;
    const u32* stream;
    u32 bit_buffer;
    u32 next_buffer;
    s32 bit_count;

    {
        bit_count = ctx->bit_count;
        initial_buffer = ctx->bit_buffer;
        next_buffer = ctx->next_buffer;
        stream = ctx->stream;

        mpvabdec_DecodeFirst(ctx, block, initial_buffer, next_buffer, bit_count);
        bit_buffer = mpvabdec_AdvanceFirst(initial_buffer, block->code_length,
                                          &bit_count, &next_buffer, &stream);
    }

    return mpvabdec_DecodeNonIntraAC(ctx, block, bit_buffer, next_buffer,
                                     bit_count, stream);
}

s32 MPVABDEC_NintraBlock(MPVABDECContext* ctx, MPVABDECBlock* block)
{
    MPVABDECCoefficients* coefficients = block->coefficients;

    /* Clear the fixed 8x8 coefficient block with paired stores. */
    coefficients->pairs[0] = 0.0;
    coefficients->pairs[1] = 0.0;
    coefficients->pairs[2] = 0.0;
    coefficients->pairs[3] = 0.0;
    coefficients->pairs[4] = 0.0;
    coefficients->pairs[5] = 0.0;
    coefficients->pairs[6] = 0.0;
    coefficients->pairs[7] = 0.0;
    coefficients->pairs[8] = 0.0;
    coefficients->pairs[9] = 0.0;
    coefficients->pairs[10] = 0.0;
    coefficients->pairs[11] = 0.0;
    coefficients->pairs[12] = 0.0;
    coefficients->pairs[13] = 0.0;
    coefficients->pairs[14] = 0.0;
    coefficients->pairs[15] = 0.0;
    coefficients->pairs[16] = 0.0;
    coefficients->pairs[17] = 0.0;
    coefficients->pairs[18] = 0.0;
    coefficients->pairs[19] = 0.0;
    coefficients->pairs[20] = 0.0;
    coefficients->pairs[21] = 0.0;
    coefficients->pairs[22] = 0.0;
    coefficients->pairs[23] = 0.0;
    coefficients->pairs[24] = 0.0;
    coefficients->pairs[25] = 0.0;
    coefficients->pairs[26] = 0.0;
    coefficients->pairs[27] = 0.0;
    coefficients->pairs[28] = 0.0;
    coefficients->pairs[29] = 0.0;
    coefficients->pairs[30] = 0.0;
    coefficients->pairs[31] = 0.0;

    return mpvabdec_DecodeNonIntra(ctx, block);
}

#pragma inline_max_size reset
#pragma inline_max_total_size reset

s32 MPVABDEC_IntraBlock(MPVABDECContext* ctx, MPVABDECBlock* block)
{
    u32 bit_buffer = ctx->bit_buffer;
    u32 next_buffer = ctx->next_buffer;
    s32 bit_count = ctx->bit_count;
    const u32* stream = ctx->stream;
    const s8* scan;
    s32 result;

    u32 peek16;
    u32 dc_code;
    u32 dc_length;
    s32 dc_value;

    peek16 = bit_buffer >> 16;
    if (bit_count > 16) {
        peek16 |= next_buffer >> (48 - bit_count);
    }
    dc_code = block->dc_size_lut[peek16 >> 9];
    dc_value = (s32)(dc_code >> 4);
    dc_length = dc_code & 0xF;
    if (dc_value != 0) {
        u32 sign_bit;

        peek16 &= ctx->dc_sign_masks[dc_length];
        dc_length += dc_value;
        peek16 >>= 16 - dc_length;
        sign_bit = 1U << (dc_value - 1);
        if ((peek16 & sign_bit) == 0) {
            peek16 += 1 - (s32)(sign_bit * 2);
        }
        dc_value = (s32)peek16 * 8;
    }
    MPV_CONSUME_BITS(dc_length);
    dc_value += *block->dc_predictor;
    *block->dc_predictor = dc_value;
    block->coefficients->values[0] = 0.125f * (f32)dc_value;
    block->first_scan = 0;
    block->current_scan = 0;
    scan = ctx->scan;

    if (ctx->decode_mode != 4) {
        do {
            u32 peek;
            u32 index;

            MPV_PEEK_BITS(peek);
            switch (peek >> 24) {
            case 0xFC:
            case 0xFD:
            case 0xFF:
                MPV_DIRECT2_CONT(1, 1, 1, 2, 1, 1, 6, 1);
                continue;
            case 0xF8:
            case 0xF9:
            case 0xFB:
                MPV_DIRECT2_CONT(1, 1, 1, 2, 1, 0, 6, 1);
                continue;
            case 0xEE:
            case 0xEF:
                MPV_DIRECT2_CONT(1, 1, 1, 3, 1, 1, 7, 1);
                continue;
            case 0xEC:
            case 0xED:
                MPV_DIRECT2_CONT(1, 1, 1, 3, 1, 0, 7, 1);
                continue;
            case 0xEB:
                MPV_DIRECT2_CONT(1, 1, 1, 4, 1, 1, 8, 1);
                continue;
            case 0xEA:
                MPV_DIRECT2_CONT(1, 1, 1, 4, 1, 0, 8, 1);
                continue;
            case 0xE9:
                MPV_DIRECT2_CONT(1, 1, 1, 2, 2, 1, 8, 1);
                continue;
            case 0xE8:
                MPV_DIRECT2_CONT(1, 1, 1, 2, 2, 0, 8, 1);
                continue;
            case 0xE0:
            case 0xE1:
            case 0xE2:
            case 0xE3:
            case 0xE4:
            case 0xE5:
            case 0xE6:
            case 0xE7:
                MPV_DIRECT1_CONT(1, 1, 1, 3, 1);
                continue;
            case 0xDC:
            case 0xDD:
            case 0xDF:
                MPV_DIRECT2_CONT(1, 1, 0, 2, 1, 1, 6, 1);
                continue;
            case 0xD8:
            case 0xD9:
            case 0xDB:
                MPV_DIRECT2_CONT(1, 1, 0, 2, 1, 0, 6, 1);
                continue;
            case 0xCE:
            case 0xCF:
                MPV_DIRECT2_CONT(1, 1, 0, 3, 1, 1, 7, 1);
                continue;
            case 0xCC:
            case 0xCD:
                MPV_DIRECT2_CONT(1, 1, 0, 3, 1, 0, 7, 1);
                continue;
            case 0xCB:
                MPV_DIRECT2_CONT(1, 1, 0, 4, 1, 1, 8, 1);
                continue;
            case 0xCA:
                MPV_DIRECT2_CONT(1, 1, 0, 4, 1, 0, 8, 1);
                continue;
            case 0xC9:
                MPV_DIRECT2_CONT(1, 1, 0, 2, 2, 1, 8, 1);
                continue;
            case 0xC8:
                MPV_DIRECT2_CONT(1, 1, 0, 2, 2, 0, 8, 1);
                continue;
            case 0xC0:
            case 0xC1:
            case 0xC2:
            case 0xC3:
            case 0xC4:
            case 0xC5:
            case 0xC6:
            case 0xC7:
                MPV_DIRECT1_CONT(1, 1, 0, 3, 1);
                continue;
            case 0x7E:
            case 0x7F:
                MPV_DIRECT2_CONT(2, 1, 1, 3, 1, 1, 7, 1);
                continue;
            case 0x7C:
            case 0x7D:
                MPV_DIRECT2_CONT(2, 1, 1, 3, 1, 0, 7, 1);
                continue;
            case 0x77:
                MPV_DIRECT2_CONT(2, 1, 1, 4, 1, 1, 8, 1);
                continue;
            case 0x76:
                MPV_DIRECT2_CONT(2, 1, 1, 4, 1, 0, 8, 1);
                continue;
            case 0x70:
            case 0x71:
            case 0x72:
            case 0x73:
            case 0x74:
            case 0x75:
                MPV_DIRECT1_CONT(2, 1, 1, 4, 1);
                continue;
            case 0x6E:
            case 0x6F:
                MPV_DIRECT2_CONT(2, 1, 0, 3, 1, 1, 7, 1);
                continue;
            case 0x6C:
            case 0x6D:
                MPV_DIRECT2_CONT(2, 1, 0, 3, 1, 0, 7, 1);
                continue;
            case 0x67:
                MPV_DIRECT2_CONT(2, 1, 0, 4, 1, 1, 8, 1);
                continue;
            case 0x66:
                MPV_DIRECT2_CONT(2, 1, 0, 4, 1, 0, 8, 1);
                continue;
            case 0x60:
            case 0x61:
            case 0x62:
            case 0x63:
            case 0x64:
            case 0x65:
                MPV_DIRECT1_CONT(2, 1, 0, 4, 1);
                continue;
            case 0x5F:
                MPV_DIRECT2_CONT(3, 1, 1, 4, 1, 1, 8, 1);
                continue;
            case 0x5E:
                MPV_DIRECT2_CONT(3, 1, 1, 4, 1, 0, 8, 1);
                continue;
            case 0x58:
            case 0x59:
            case 0x5A:
            case 0x5B:
                MPV_DIRECT1_CONT(3, 1, 1, 5, 1);
                continue;
            case 0x57:
                MPV_DIRECT2_CONT(3, 1, 0, 4, 1, 1, 8, 1);
                continue;
            case 0x56:
                MPV_DIRECT2_CONT(3, 1, 0, 4, 1, 0, 8, 1);
                continue;
            case 0x50:
            case 0x51:
            case 0x52:
            case 0x53:
                MPV_DIRECT1_CONT(3, 1, 0, 5, 1);
                continue;
            case 0x4F:
                MPV_DIRECT2_CONT(1, 2, 1, 2, 1, 1, 8, 1);
                continue;
            case 0x4E:
                MPV_DIRECT2_CONT(1, 2, 1, 2, 1, 0, 8, 1);
                continue;
            case 0x48:
            case 0x49:
            case 0x4A:
            case 0x4B:
                MPV_DIRECT1_CONT(1, 2, 1, 5, 1);
                continue;
            case 0x47:
                MPV_DIRECT2_CONT(1, 2, 0, 2, 1, 1, 8, 1);
                continue;
            case 0x46:
                MPV_DIRECT2_CONT(1, 2, 0, 2, 1, 0, 8, 1);
                continue;
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
                MPV_DIRECT1_CONT(1, 2, 0, 5, 1);
                continue;
            case 0x3C:
            case 0x3D:
            case 0x3F:
                MPV_DIRECT1_CONT(4, 1, 1, 6, 1);
                continue;
            case 0x38:
            case 0x39:
            case 0x3B:
                MPV_DIRECT1_CONT(4, 1, 0, 6, 1);
                continue;
            case 0x34:
            case 0x35:
            case 0x37:
                MPV_DIRECT1_CONT(5, 1, 1, 6, 1);
                continue;
            case 0x30:
            case 0x31:
            case 0x33:
                MPV_DIRECT1_CONT(5, 1, 0, 6, 1);
                continue;
            case 0x2C:
            case 0x2D:
            case 0x2F:
                MPV_DIRECT1_CONT(1, 3, 1, 6, 1);
                continue;
            case 0x28:
            case 0x29:
            case 0x2B:
                MPV_DIRECT1_CONT(1, 3, 0, 6, 1);
                continue;
            case 0x20:
            case 0x21:
            case 0x22:
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x27:
                peek <<= 1;
                index = peek >> 25;
                MPV_DECODE_LONG(index, peek);
                MPV_CONSUME_BITS(block->code_length);
                scan += block->run + 1;
                block->current_scan = (s32)*scan;
                MPV_STORE_DECODED(1);
                continue;
            case 0x1E:
            case 0x1F:
                MPV_DIRECT1_CONT(6, 1, 1, 7, 1);
                continue;
            case 0x1C:
            case 0x1D:
                MPV_DIRECT1_CONT(6, 1, 0, 7, 1);
                continue;
            case 0x1A:
            case 0x1B:
                MPV_DIRECT1_CONT(2, 2, 1, 7, 1);
                continue;
            case 0x18:
            case 0x19:
                MPV_DIRECT1_CONT(2, 2, 0, 7, 1);
                continue;
            case 0x16:
            case 0x17:
                MPV_DIRECT1_CONT(7, 1, 1, 7, 1);
                continue;
            case 0x14:
            case 0x15:
                MPV_DIRECT1_CONT(7, 1, 0, 7, 1);
                continue;
            case 0x12:
            case 0x13:
                MPV_DIRECT1_CONT(8, 1, 1, 7, 1);
                continue;
            case 0x10:
            case 0x11:
                MPV_DIRECT1_CONT(8, 1, 0, 7, 1);
                continue;
            case 0x0F:
                MPV_DIRECT1_CONT(9, 1, 1, 8, 1);
                continue;
            case 0x0E:
                MPV_DIRECT1_CONT(9, 1, 0, 8, 1);
                continue;
            case 0x0D:
                MPV_DIRECT1_CONT(1, 4, 1, 8, 1);
                continue;
            case 0x0C:
                MPV_DIRECT1_CONT(1, 4, 0, 8, 1);
                continue;
            case 0x0B:
                MPV_DIRECT1_CONT(10, 1, 1, 8, 1);
                continue;
            case 0x0A:
                MPV_DIRECT1_CONT(10, 1, 0, 8, 1);
                continue;
            case 0x09:
                MPV_DIRECT1_CONT(3, 2, 1, 8, 1);
                continue;
            case 0x08:
                MPV_DIRECT1_CONT(3, 2, 0, 8, 1);
                continue;
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x07:
                peek <<= 1;
                MPV_DECODE_ESCAPE(peek);
                scan += block->run + 1;
                block->current_scan = (s32)*scan;
                MPV_STORE_DECODED(1);
                MPV_CONSUME_BITS(block->code_length);
                continue;
            case 0x02:
            case 0x03:
                index = (peek >> 21) & 0x3FF;
                MPV_DECODE_SHORT(ctx->run_level_4, index, 11);
                MPV_CONSUME_BITS(block->code_length);
                scan += block->run + 1;
                block->current_scan = (s32)*scan;
                MPV_STORE_DECODED(1);
                continue;
            case 0x01:
                index = (peek >> 19) & 0xFFF;
                MPV_DECODE_SHORT(ctx->run_level_2, index, 13);
                MPV_CONSUME_BITS(block->code_length);
                scan += block->run + 1;
                block->current_scan = (s32)*scan;
                MPV_STORE_DECODED(1);
                continue;
        case 0x00:
            peek <<= 1;
            MPV_DECODE_RARE(peek, 1);
            MPV_CONSUME_BITS(block->code_length);
                scan += block->run + 1;
                block->current_scan = (s32)*scan;
                MPV_STORE_DECODED(1);
                continue;
            case 0xFE:
                MPV_DIRECT2_TERM(1, 1, 1, 2, 1, 1, 8, 1);
                break;
            case 0xFA:
                MPV_DIRECT2_TERM(1, 1, 1, 2, 1, 0, 8, 1);
                break;
            case 0xF0:
            case 0xF1:
            case 0xF2:
            case 0xF3:
            case 0xF4:
            case 0xF5:
            case 0xF6:
            case 0xF7:
                MPV_DIRECT1_TERM(1, 1, 1, 5, 1);
                break;
            case 0xDE:
                MPV_DIRECT2_TERM(1, 1, 0, 2, 1, 1, 8, 1);
                break;
            case 0xDA:
                MPV_DIRECT2_TERM(1, 1, 0, 2, 1, 0, 8, 1);
                break;
            case 0xD0:
            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
            case 0xD5:
            case 0xD6:
            case 0xD7:
                MPV_DIRECT1_TERM(1, 1, 0, 5, 1);
                break;
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0x89:
            case 0x8A:
            case 0x8B:
            case 0x8C:
            case 0x8D:
            case 0x8E:
            case 0x8F:
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
            case 0x95:
            case 0x96:
            case 0x97:
            case 0x98:
            case 0x99:
            case 0x9A:
            case 0x9B:
            case 0x9C:
            case 0x9D:
            case 0x9E:
            case 0x9F:
            case 0xA0:
            case 0xA1:
            case 0xA2:
            case 0xA3:
            case 0xA4:
            case 0xA5:
            case 0xA6:
            case 0xA7:
            case 0xA8:
            case 0xA9:
            case 0xAA:
            case 0xAB:
            case 0xAC:
            case 0xAD:
            case 0xAE:
            case 0xAF:
            case 0xB0:
            case 0xB1:
            case 0xB2:
            case 0xB3:
            case 0xB4:
            case 0xB5:
            case 0xB6:
            case 0xB7:
            case 0xB8:
            case 0xB9:
            case 0xBA:
            case 0xBB:
            case 0xBC:
            case 0xBD:
            case 0xBE:
            case 0xBF:
                MPV_CONSUME_BITS(2);
                break;
            case 0x78:
            case 0x79:
            case 0x7A:
            case 0x7B:
                MPV_DIRECT1_TERM(2, 1, 1, 6, 1);
                break;
            case 0x68:
            case 0x69:
            case 0x6A:
            case 0x6B:
                MPV_DIRECT1_TERM(2, 1, 0, 6, 1);
                break;
            case 0x5C:
            case 0x5D:
                MPV_DIRECT1_TERM(3, 1, 1, 7, 1);
                break;
            case 0x54:
            case 0x55:
                MPV_DIRECT1_TERM(3, 1, 0, 7, 1);
                break;
            case 0x4C:
            case 0x4D:
                MPV_DIRECT1_TERM(1, 2, 1, 7, 1);
                break;
            case 0x44:
            case 0x45:
                MPV_DIRECT1_TERM(1, 2, 0, 7, 1);
                break;
            case 0x3E:
                MPV_DIRECT1_TERM(4, 1, 1, 8, 1);
                break;
            case 0x3A:
                MPV_DIRECT1_TERM(4, 1, 0, 8, 1);
                break;
            case 0x36:
                MPV_DIRECT1_TERM(5, 1, 1, 8, 1);
                break;
            case 0x32:
                MPV_DIRECT1_TERM(5, 1, 0, 8, 1);
                break;
            case 0x2E:
                MPV_DIRECT1_TERM(1, 3, 1, 8, 1);
                break;
            case 0x2A:
                MPV_DIRECT1_TERM(1, 3, 0, 8, 1);
                break;
            }
            break;
        } while (1);

    }

    ctx->bit_buffer = bit_buffer;
    ctx->next_buffer = next_buffer;
    ctx->bit_count = bit_count;
    ctx->stream = stream;

    result = block->current_scan;
    if (result != block->first_scan) {
        result = -result;
    }
    block->current_scan = result;
    return block->current_scan;
}

s32 MPVABDEC_IntraBlockDc11(MPVABDECContext* ctx, MPVABDECBlock* block)
{
    u32 initial_buffer = ctx->bit_buffer;
    u32 bit_buffer;
    u32 next_buffer = ctx->next_buffer;
    s32 bit_count = ctx->bit_count;
    const u32* stream = ctx->stream;
    const s8* scan;
    u32 peek;
    u32 index;
    s32 result;

    u32 dc_code;
    u32 dc_length;
    s32 dc_value;

    peek = initial_buffer;
    if (bit_count != 0) {
        peek |= next_buffer >> (32 - bit_count);
    }
    dc_code = block->dc_size_lut[peek >> 22];
    dc_value = (s32)(dc_code >> 4);
    dc_length = dc_code & 0xF;
    if (dc_value != 0) {
        peek <<= dc_length;
        dc_length += dc_value;
        peek = (u32)(((s32)peek >> 1) ^ (s32)0x80000000);
        dc_value =
            ((s32)peek >> (31 - dc_value)) +
            (s32)(peek >> 31);
    }
    bit_count += dc_length;
    MPV_FINISH_FROM(initial_buffer, dc_length);
    dc_value += *block->dc_predictor;
    *block->dc_predictor = dc_value;
    block->coefficients->values[0] = 0.125f * (f32)dc_value;
    block->first_scan = 0;
    block->current_scan = 0;
    scan = ctx->scan;

    do {
        MPV_PEEK_BITS(peek);
        switch (peek >> 24) {
        case 0xFC:
        case 0xFD:
        case 0xFF:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 1, 1, 6, 1);
            continue;
        case 0xF8:
        case 0xF9:
        case 0xFB:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 1, 0, 6, 1);
            continue;
        case 0xEE:
        case 0xEF:
            MPV_DIRECT2_CONT(1, 1, 1, 3, 1, 1, 7, 1);
            continue;
        case 0xEC:
        case 0xED:
            MPV_DIRECT2_CONT(1, 1, 1, 3, 1, 0, 7, 1);
            continue;
        case 0xEB:
            MPV_DIRECT2_CONT(1, 1, 1, 4, 1, 1, 8, 1);
            continue;
        case 0xEA:
            MPV_DIRECT2_CONT(1, 1, 1, 4, 1, 0, 8, 1);
            continue;
        case 0xE9:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 2, 1, 8, 1);
            continue;
        case 0xE8:
            MPV_DIRECT2_CONT(1, 1, 1, 2, 2, 0, 8, 1);
            continue;
        case 0xE0:
        case 0xE1:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
            MPV_DIRECT1_CONT(1, 1, 1, 3, 1);
            continue;
        case 0xDC:
        case 0xDD:
        case 0xDF:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 1, 1, 6, 1);
            continue;
        case 0xD8:
        case 0xD9:
        case 0xDB:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 1, 0, 6, 1);
            continue;
        case 0xCE:
        case 0xCF:
            MPV_DIRECT2_CONT(1, 1, 0, 3, 1, 1, 7, 1);
            continue;
        case 0xCC:
        case 0xCD:
            MPV_DIRECT2_CONT(1, 1, 0, 3, 1, 0, 7, 1);
            continue;
        case 0xCB:
            MPV_DIRECT2_CONT(1, 1, 0, 4, 1, 1, 8, 1);
            continue;
        case 0xCA:
            MPV_DIRECT2_CONT(1, 1, 0, 4, 1, 0, 8, 1);
            continue;
        case 0xC9:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 2, 1, 8, 1);
            continue;
        case 0xC8:
            MPV_DIRECT2_CONT(1, 1, 0, 2, 2, 0, 8, 1);
            continue;
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC4:
        case 0xC5:
        case 0xC6:
        case 0xC7:
            MPV_DIRECT1_CONT(1, 1, 0, 3, 1);
            continue;
        case 0x7E:
        case 0x7F:
            MPV_DIRECT2_CONT(2, 1, 1, 3, 1, 1, 7, 1);
            continue;
        case 0x7C:
        case 0x7D:
            MPV_DIRECT2_CONT(2, 1, 1, 3, 1, 0, 7, 1);
            continue;
        case 0x77:
            MPV_DIRECT2_CONT(2, 1, 1, 4, 1, 1, 8, 1);
            continue;
        case 0x76:
            MPV_DIRECT2_CONT(2, 1, 1, 4, 1, 0, 8, 1);
            continue;
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
            MPV_DIRECT1_CONT(2, 1, 1, 4, 1);
            continue;
        case 0x6E:
        case 0x6F:
            MPV_DIRECT2_CONT(2, 1, 0, 3, 1, 1, 7, 1);
            continue;
        case 0x6C:
        case 0x6D:
            MPV_DIRECT2_CONT(2, 1, 0, 3, 1, 0, 7, 1);
            continue;
        case 0x67:
            MPV_DIRECT2_CONT(2, 1, 0, 4, 1, 1, 8, 1);
            continue;
        case 0x66:
            MPV_DIRECT2_CONT(2, 1, 0, 4, 1, 0, 8, 1);
            continue;
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
            MPV_DIRECT1_CONT(2, 1, 0, 4, 1);
            continue;
        case 0x5F:
            MPV_DIRECT2_CONT(3, 1, 1, 4, 1, 1, 8, 1);
            continue;
        case 0x5E:
            MPV_DIRECT2_CONT(3, 1, 1, 4, 1, 0, 8, 1);
            continue;
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
            MPV_DIRECT1_CONT(3, 1, 1, 5, 1);
            continue;
        case 0x57:
            MPV_DIRECT2_CONT(3, 1, 0, 4, 1, 1, 8, 1);
            continue;
        case 0x56:
            MPV_DIRECT2_CONT(3, 1, 0, 4, 1, 0, 8, 1);
            continue;
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
            MPV_DIRECT1_CONT(3, 1, 0, 5, 1);
            continue;
        case 0x4F:
            MPV_DIRECT2_CONT(1, 2, 1, 2, 1, 1, 8, 1);
            continue;
        case 0x4E:
            MPV_DIRECT2_CONT(1, 2, 1, 2, 1, 0, 8, 1);
            continue;
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
            MPV_DIRECT1_CONT(1, 2, 1, 5, 1);
            continue;
        case 0x47:
            MPV_DIRECT2_CONT(1, 2, 0, 2, 1, 1, 8, 1);
            continue;
        case 0x46:
            MPV_DIRECT2_CONT(1, 2, 0, 2, 1, 0, 8, 1);
            continue;
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            MPV_DIRECT1_CONT(1, 2, 0, 5, 1);
            continue;
        case 0x3C:
        case 0x3D:
        case 0x3F:
            MPV_DIRECT1_CONT(4, 1, 1, 6, 1);
            continue;
        case 0x38:
        case 0x39:
        case 0x3B:
            MPV_DIRECT1_CONT(4, 1, 0, 6, 1);
            continue;
        case 0x34:
        case 0x35:
        case 0x37:
            MPV_DIRECT1_CONT(5, 1, 1, 6, 1);
            continue;
        case 0x30:
        case 0x31:
        case 0x33:
            MPV_DIRECT1_CONT(5, 1, 0, 6, 1);
            continue;
        case 0x2C:
        case 0x2D:
        case 0x2F:
            MPV_DIRECT1_CONT(1, 3, 1, 6, 1);
            continue;
        case 0x28:
        case 0x29:
        case 0x2B:
            MPV_DIRECT1_CONT(1, 3, 0, 6, 1);
            continue;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
            peek <<= 1;
            index = peek >> 25;
            MPV_DECODE_LONG(index, peek);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(1);
            continue;
        case 0x1E:
        case 0x1F:
            MPV_DIRECT1_CONT(6, 1, 1, 7, 1);
            continue;
        case 0x1C:
        case 0x1D:
            MPV_DIRECT1_CONT(6, 1, 0, 7, 1);
            continue;
        case 0x1A:
        case 0x1B:
            MPV_DIRECT1_CONT(2, 2, 1, 7, 1);
            continue;
        case 0x18:
        case 0x19:
            MPV_DIRECT1_CONT(2, 2, 0, 7, 1);
            continue;
        case 0x16:
        case 0x17:
            MPV_DIRECT1_CONT(7, 1, 1, 7, 1);
            continue;
        case 0x14:
        case 0x15:
            MPV_DIRECT1_CONT(7, 1, 0, 7, 1);
            continue;
        case 0x12:
        case 0x13:
            MPV_DIRECT1_CONT(8, 1, 1, 7, 1);
            continue;
        case 0x10:
        case 0x11:
            MPV_DIRECT1_CONT(8, 1, 0, 7, 1);
            continue;
        case 0x0F:
            MPV_DIRECT1_CONT(9, 1, 1, 8, 1);
            continue;
        case 0x0E:
            MPV_DIRECT1_CONT(9, 1, 0, 8, 1);
            continue;
        case 0x0D:
            MPV_DIRECT1_CONT(1, 4, 1, 8, 1);
            continue;
        case 0x0C:
            MPV_DIRECT1_CONT(1, 4, 0, 8, 1);
            continue;
        case 0x0B:
            MPV_DIRECT1_CONT(10, 1, 1, 8, 1);
            continue;
        case 0x0A:
            MPV_DIRECT1_CONT(10, 1, 0, 8, 1);
            continue;
        case 0x09:
            MPV_DIRECT1_CONT(3, 2, 1, 8, 1);
            continue;
        case 0x08:
            MPV_DIRECT1_CONT(3, 2, 0, 8, 1);
            continue;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            {
                u32 escape_bits = mpvabdec_AlignEscapeLookahead(peek);
                MPV_DECODE_ESCAPE(escape_bits);
            }
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(1);
            MPV_CONSUME_BITS(block->code_length);
            continue;
        case 0x02:
        case 0x03:
            index = (peek >> 21) & 0x3FF;
            MPV_DECODE_SHORT(ctx->run_level_4, index, 11);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(1);
            continue;
        case 0x01:
            index = (peek >> 19) & 0xFFF;
            MPV_DECODE_SHORT(ctx->run_level_2, index, 13);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(1);
            continue;
        case 0x00:
            peek <<= 1;
            MPV_DECODE_RARE(peek, 1);
            MPV_CONSUME_BITS(block->code_length);
            scan += block->run + 1;
            block->current_scan = (s32)*scan;
            MPV_STORE_DECODED(1);
            continue;
        case 0xFE:
            MPV_DIRECT2_TERM(1, 1, 1, 2, 1, 1, 8, 1);
            break;
        case 0xFA:
            MPV_DIRECT2_TERM(1, 1, 1, 2, 1, 0, 8, 1);
            break;
        case 0xF0:
        case 0xF1:
        case 0xF2:
        case 0xF3:
        case 0xF4:
        case 0xF5:
        case 0xF6:
        case 0xF7:
            MPV_DIRECT1_TERM(1, 1, 1, 5, 1);
            break;
        case 0xDE:
            MPV_DIRECT2_TERM(1, 1, 0, 2, 1, 1, 8, 1);
            break;
        case 0xDA:
            MPV_DIRECT2_TERM(1, 1, 0, 2, 1, 0, 8, 1);
            break;
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            MPV_DIRECT1_TERM(1, 1, 0, 5, 1);
            break;
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
        case 0x86:
        case 0x87:
        case 0x88:
        case 0x89:
        case 0x8A:
        case 0x8B:
        case 0x8C:
        case 0x8D:
        case 0x8E:
        case 0x8F:
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x96:
        case 0x97:
        case 0x98:
        case 0x99:
        case 0x9A:
        case 0x9B:
        case 0x9C:
        case 0x9D:
        case 0x9E:
        case 0x9F:
        case 0xA0:
        case 0xA1:
        case 0xA2:
        case 0xA3:
        case 0xA4:
        case 0xA5:
        case 0xA6:
        case 0xA7:
        case 0xA8:
        case 0xA9:
        case 0xAA:
        case 0xAB:
        case 0xAC:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB0:
        case 0xB1:
        case 0xB2:
        case 0xB3:
        case 0xB4:
        case 0xB5:
        case 0xB6:
        case 0xB7:
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBB:
        case 0xBC:
        case 0xBD:
        case 0xBE:
        case 0xBF:
            MPV_CONSUME_BITS(2);
            break;
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
            MPV_DIRECT1_TERM(2, 1, 1, 6, 1);
            break;
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
            MPV_DIRECT1_TERM(2, 1, 0, 6, 1);
            break;
        case 0x5C:
        case 0x5D:
            MPV_DIRECT1_TERM(3, 1, 1, 7, 1);
            break;
        case 0x54:
        case 0x55:
            MPV_DIRECT1_TERM(3, 1, 0, 7, 1);
            break;
        case 0x4C:
        case 0x4D:
            MPV_DIRECT1_TERM(1, 2, 1, 7, 1);
            break;
        case 0x44:
        case 0x45:
            MPV_DIRECT1_TERM(1, 2, 0, 7, 1);
            break;
        case 0x3E:
            MPV_DIRECT1_TERM(4, 1, 1, 8, 1);
            break;
        case 0x3A:
            MPV_DIRECT1_TERM(4, 1, 0, 8, 1);
            break;
        case 0x36:
            MPV_DIRECT1_TERM(5, 1, 1, 8, 1);
            break;
        case 0x32:
            MPV_DIRECT1_TERM(5, 1, 0, 8, 1);
            break;
        case 0x2E:
            MPV_DIRECT1_TERM(1, 3, 1, 8, 1);
            break;
        case 0x2A:
            MPV_DIRECT1_TERM(1, 3, 0, 8, 1);
            break;
        }
        break;
    } while (1);

    ctx->bit_buffer = bit_buffer;
    ctx->next_buffer = next_buffer;
    ctx->bit_count = bit_count;
    ctx->stream = stream;

    result = block->current_scan;
    if (result != block->first_scan) {
        result = -result;
    }
    block->current_scan = result;
    return block->current_scan;
}
