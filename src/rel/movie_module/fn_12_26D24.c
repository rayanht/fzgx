#include "types.h"

typedef void (*Sig_fn_12_24A88_MovieCallback)(void *, s32);

typedef struct Sig_fn_12_24A88_MovieObject {
    u8 pad_0000[0x48];
    s32 state;
    u8 pad_004c[0x940];
    Sig_fn_12_24A88_MovieCallback callback;
    void *callback_context;
    s32 callback_data;
} Sig_fn_12_24A88_MovieObject;

extern s32 fn_12_24A88(Sig_fn_12_24A88_MovieObject *movie, s32 code);

void fn_12_26D24(Sig_fn_12_24A88_MovieObject *movie, s32 code) {
    switch (code) {
    case -3:
    case -2:
    case 0:
        break;
    default:
        fn_12_24A88(movie, code);
        break;
    }
}
