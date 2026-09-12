#include "types.h"

typedef struct MovieBlob {
    s32 field_0000[10];
} MovieBlob;

typedef struct MovieData {
    s32 ready;
    u8 pad04[8];
    MovieBlob blob;
    u8 pad34[0x200];
    s32 field_0234;
} MovieData;

typedef struct MovieState {
    void *field_0000;
    u8 pad04[0x70];
    s32 field_0074;
    s32 field_0078;
    u8 pad7c[0xc];
    s32 field_0088;
} MovieState;

typedef struct MovieObject {
    u8 pad_0000[0xcdc];
    MovieBlob blob;
    u8 pad_0d04[0xe2c];
    MovieState *state;
    u8 pad_1b34[0xdd4];
    MovieData *movie;
} MovieObject;

typedef struct MovieArgs {
    u32 field_0000;
    u32 field_0004;
} MovieArgs;

extern s32 fn_12_C218(void *base, MovieArgs *args, s32 *out);
extern s32 fn_12_24A88(MovieObject *self, u32 code);
extern s32 fn_12_2D73C(MovieObject *self, int value);

#pragma opt_propagation off
int fn_12_267C0(MovieObject *self) {
    MovieData * fzgx_live;
    u32 fzgx_value;
    MovieData *movie;
    MovieState *state;
    MovieData *data;
    void *ctx;
    MovieArgs args;
    s32 out;
    s32 result;
    s32 success;

    success = 0;
    fzgx_live = self->movie;
    movie = fzgx_live;
    state = self->state;
    if (movie == 0) {
        data = 0;
    } else if (state->field_0088 > 0) {
        data = 0;
    } else {
        data = (MovieData *)((u8 *)movie + 0xac4);
    }
    if (data == 0) {
        result = 0;
    } else if (data->ready == 0) {
        result = 0;
    } else {
        ctx = state->field_0000;
        self->blob = data->blob;
        fzgx_value = (u32)((u8 *)data + 0x34);
        args.field_0000 = fzgx_value;
        args.field_0004 = (u32)data->field_0234;
        if (fn_12_C218(ctx, &args, &out) != 0) {
            result = fn_12_24A88(self, 0xff000f1b);
        } else {
            success = 1;
            result = 0;
        }
    }
    if (result != 0) {
        return result;
    }
    state->field_0074 = 2;
    if (success == 0 || fn_12_2D73C(self, 0x30) == 0) {
        state->field_0078 = 0xc0;
    } else {
        state->field_0078 = 0xc8;
    }
    return 0;
}
#pragma opt_propagation reset

