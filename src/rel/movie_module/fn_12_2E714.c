#include "types.h"

typedef struct MovieModuleState MovieModuleState;
typedef s32 (*MovieCallback)(MovieModuleState *, s32 *, s32 *);

struct MovieModuleState {
    u8 padding_000[0xcc0];
    MovieCallback callbacks[1];
    u8 padding_001[0x244];
    s32 state;
    s32 value;
};

extern void fn_12_24970(s32 *);
extern s32 fn_12_2D73C(MovieModuleState *, s32);
extern s32 fn_12_24950(s32 *);
extern s32 fn_12_2E6AC(MovieModuleState *, s32 *, s32 *);

s32 fn_12_2E714(MovieModuleState *movie, s32 *result, s32 *flag) {
    s32 local;
    s32 state;
    s32 index;
    struct { MovieCallback value; } callback;

    state = movie->state;
    if (state == -5) {
        fn_12_24970(&local);
        index = fn_12_2D73C(movie, 15);
        callback.value = movie->callbacks[index];
        if (callback.value == 0) {
            callback.value = fn_12_2E6AC;
        }
        state = callback.value(movie, result, flag);
        fn_12_24950(&local);
        return state;
    }

    *result = state;
    *flag = movie->value;
    return 0;
}
