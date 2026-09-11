#include "types.h"

extern f64 lbl_12_rodata_60[12];

typedef struct MovieState {
    int pad0;
    int value;
} MovieState;

typedef struct MovieData {
    int mode;
    int value;
    unsigned char pad[0x3c];
    int field44;
    int field48;
} MovieData;

typedef struct MovieArgs {
    int a;
    int b;
    int c;
    int pad[3];
} MovieArgs;

extern int fn_12_3074(MovieData *, void *);
extern void fn_12_21C8(MovieState *, MovieData *, int);
extern void fn_12_1578(MovieState *, MovieData *, int);
extern void fn_12_3D738(MovieArgs *, MovieArgs *);
extern void fn_12_309C(MovieState *, MovieData *, void *);

void fn_12_2F04(MovieState *state, MovieData *data, int arg) {
    int value;
    char *pool;
    MovieArgs local1;
    MovieArgs local0;

    pool = (char *)lbl_12_rodata_60;
    value = data->mode;
    if (state->value == 0) {
        state->value = fn_12_3074(data, pool + 0x60);
    }

    switch (value) {
    case 3:
        fn_12_21C8(state, data, arg);
        break;
    case 1:
        fn_12_1578(state, data, arg);
        break;
    case 2:
        switch (state->value) {
        case 0x11:
            break;
        case 0x21:
            local0.a = data->value;
            local0.b = data->field44;
            local0.c = data->field48;
            local1.a = arg;
            local1.b = data->field44;
            local1.c = data->field48;
            fn_12_3D738(&local0, &local1);
            break;
        case 0x31:
        case 0x41:
        case 0xf1:
        case 0x101:
        case 0x1001:
        default:
            fn_12_309C(state, data, pool + 0x380);
            break;
        }
        break;
    default:
        fn_12_309C(state, data, pool + 0x3b0);
        break;
    }
}
