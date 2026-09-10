#include "types.h"

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *movie_resource;
    u8 pad_ac[0x3c];
    u8 *movie_data;
    u8 pad_ec[0x18];
    u32 value_104;
    u32 value_108;
} MovieModuleState;

extern void mwsftag_GetAinfFromSj(MovieModuleState *self);
extern void fn_12_818(void *resource, u32 value0, u32 value1);
extern void *SJ_SearchTag(void *input, const f64 *constant, u8 *table, void *output);
extern const f64 lbl_12_rodata_1778;
extern u8 lbl_12_rodata_1780[64];

void fn_12_3530C(MovieModuleState *self) {
    u32 output[2];
    u32 input[2];
    void *resource;

    if (self->movie_data != 0) {
        mwsftag_GetAinfFromSj(self);
        resource = self->movie_resource;
        if (self->value_104 == 0) {
            fn_12_818(resource, 0, 0);
        } else {
            input[0] = self->value_104;
            input[1] = self->value_108;
            if (SJ_SearchTag(input, &lbl_12_rodata_1778,
                            lbl_12_rodata_1780, output) == 0) {
                fn_12_818(resource, 0, 0);
            } else {
                fn_12_818(resource, output[0], output[1]);
            }
        }
    }
}
