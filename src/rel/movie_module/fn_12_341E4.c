#include "types.h"

typedef struct MovieState {
    u8 pad0[0x40];
    void *field40;
    u8 pad44[0x2c];
    s8 state70;
    s8 state71;
} MovieState;

extern int fn_12_3A36C(MovieState *movie);
extern char lbl_12_rodata_12E0[43];
extern void MWSFSVM_Error(const char *message, ...);
extern int fn_12_23280(void *value);
extern char lbl_12_rodata_130C[42];

void fn_12_341E4(MovieState *movie, int value) {
    if (fn_12_3A36C(movie) == 0) {
        MWSFSVM_Error(lbl_12_rodata_12E0);
    } else {
        void *field = movie->field40;

        if (movie->state70 == 1 && value == 0) {
            movie->state71 = 1;
        }
        if ((s8)movie->state70 == 0 && value == 1 &&
            fn_12_23280(field) != 0) {
            MWSFSVM_Error(lbl_12_rodata_130C);
        }
        movie->state70 = value;
    }
}
