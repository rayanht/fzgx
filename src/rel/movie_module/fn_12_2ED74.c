#include "types.h"

typedef struct MovieModuleState {
    u8 padding_000[0x250];
    s32 field_250;
    s32 field_254;
    s32 field_258;
} MovieModuleState;

s32 fn_12_2ED74(MovieModuleState *state, s32 value) {
    s32 first = state->field_250;
    s32 second = state->field_254;
    s32 third = state->field_258;
    s32 first_sum;
    s32 second_sum;

    first_sum = first + second;
    second_sum = first + third;
    if (value < first_sum) {
        return first_sum;
    }
    if (value < second_sum) {
        return second_sum;
    }
    return 0x7fffffff;
}
