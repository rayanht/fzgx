#include "types.h"

extern void *fn_12_57F0(void *value, const void *unused, u32 frames);
extern void fn_800589BC(int *a, int frames, int *b, int *c);

typedef void (*MoviePrepareFn)(void *, int, int, void *);
typedef void (*MovieUpdateFn)(void *, int, void *);
typedef void (*MovieProcessFn)(void *, int, void *);

typedef struct MovieVTable {
    void *unused[6];
    MoviePrepareFn prepare;
    MovieUpdateFn update;
    MovieProcessFn process;
} MovieVTable;

typedef struct MovieData {
    MovieVTable *vtable;
} MovieData;

typedef union MovieResult {
    f64 real;
    struct {
        int value;
        int duration;
    } words;
} MovieResult;

typedef struct MovieState {
    char pad0000[4];
    MovieData *movie;
    int field8;
    char pad000c[0x3c];
    int elapsed;
} MovieState;

typedef struct MovieModule {
    char pad0000[0x1b74];
    MovieState *state;
} MovieModule;

void fn_12_20F4C(MovieModule *module, void *unused, int frames, int *result) {
    int local8;
    f64 local10;
    int frame_count = frames;
    MovieState *state = module->state;
    MovieData *movie = state->movie;
    int duration;
    void *value;
    int *words;

    movie->vtable->prepare(movie, 0, state->field8, &local10);
    words = (int *)&local10;
    value = (void *)words[0];
    duration = words[1];
    if (frame_count < duration) {
        duration = frame_count;
    }
    frame_count = 0x19000;
    if (duration < frame_count) {
        frame_count = duration;
    }

    fn_12_57F0(value, unused, frame_count);
    if (frame_count == 0) {
        movie->vtable->update(movie, 0, &local10);
    } else {
        fn_800589BC((int *)&local10, frame_count, (int *)&local10, &local8);
        movie->vtable->process(movie, 1, &local10);
        movie->vtable->update(movie, 0, &local8);
    }
    state->elapsed += frame_count;
    *result = frame_count;
}
