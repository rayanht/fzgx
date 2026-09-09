#include "types.h"

typedef struct Movie {
    void *value;
} Movie;

typedef struct MovieModuleState {
    u8 pad_a8[0xa8];
    void *movie;
} MovieModuleState;

extern int fn_12_3A36C(MovieModuleState *self);
extern char lbl_12_rodata_1BC0[49];
extern char lbl_12_rodata_1BF4[49];
extern void MWSFSVM_Error(const char *format, ...);
extern void fn_12_35B08(MovieModuleState *self, Movie *movie, void *out);
extern void fn_12_D88(void *movie_data, void *out, s32 arg2, s32 arg3);

void fn_12_35914(MovieModuleState *self, Movie *movie, s32 arg2, s32 arg3) {
    void *movie_data;
    u8 local[0x90];

    if (!fn_12_3A36C(self)) {
        MWSFSVM_Error(lbl_12_rodata_1BC0);
    } else if (movie->value == 0) {
        MWSFSVM_Error(lbl_12_rodata_1BF4);
    } else {
        movie_data = self->movie;
        fn_12_35B08(self, movie, local);
        fn_12_D88(movie_data, local, arg2, arg3);
    }
}
