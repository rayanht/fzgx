
#include "types.h"

typedef struct AdxXpndParams {
    int channel_count;
    const signed char *input;
    int num_blocks;
    short *output_left;
    short *output_right;
} AdxXpndParams;

typedef struct AdxXpnd {
    int used;
    int index;
    int mode;
    int status;
    int num_decoded_blocks;
    AdxXpndParams params;
    short delay[2][2];
    short coefficients[2];
    short random_state;
    short random_multiplier;
    short random_increment;
    short reserved;
} AdxXpnd;

extern int fn_8004F55C(const signed char *input, int num_blocks, short *output, short delay[2],
                       short coefficient0, short coefficient1, short *random_state,
                       short random_multiplier, short random_increment);

extern int fn_8004EFA8(const signed char *input, int num_blocks, short *output_left,
                       short delay_left[2], short *output_right, short delay_right[2],
                       short coefficient0, short coefficient1, short *random_state,
                       short random_multiplier, short random_increment);

extern int lbl_8017E5B8;

void ADXPD_ExecHndl(AdxXpnd *decoder) {
    if (decoder->status == 1) {
        decoder->status = 2;
    }
    if (decoder->status == 2) {
        if (decoder->params.channel_count == 1) {
            decoder->num_decoded_blocks = fn_8004F55C(
                decoder->params.input, decoder->params.num_blocks, decoder->params.output_left,
                decoder->delay[0], decoder->coefficients[0], decoder->coefficients[1],
                &decoder->random_state, decoder->random_multiplier, decoder->random_increment);
        } else {
            decoder->num_decoded_blocks = fn_8004EFA8(
                decoder->params.input, decoder->params.num_blocks, decoder->params.output_left,
                decoder->delay[0], decoder->params.output_right, decoder->delay[1],
                decoder->coefficients[0], decoder->coefficients[1], &decoder->random_state,
                decoder->random_multiplier, decoder->random_increment);
            if ((decoder->num_decoded_blocks % 2) == 1) {
                lbl_8017E5B8 = 1;
            }
        }
        decoder->status = 3;
    }
}
