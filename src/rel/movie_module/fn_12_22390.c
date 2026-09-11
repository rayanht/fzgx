#include "types.h"

typedef struct MovieObject MovieObject;

typedef struct MovieVtable {
    char padding[0x18];
    u32 (*fn18)(MovieObject *, int, int, void *);
    u32 (*fn1c)(MovieObject *, int, void *);
    char padding2[4];
    u32 (*fn24)(MovieObject *, int);
} MovieVtable;

struct MovieObject {
    MovieVtable *vtable;
};

typedef struct MovieEntry {
    char padding0[0x1144];
    int field;
    char padding1[0xc];
    MovieObject *obj;
} MovieEntry;

typedef struct MovieState {
    u8 data[4];
} MovieState;

extern void fn_12_24970(MovieState *state);
extern void fn_12_24950(MovieState *state);

int fn_12_22390(u8 *module, int index, u32 *out) {
    MovieState state;
    u32 w[2];
    u32 v[2];
    MovieEntry *entry;
    MovieObject *obj;
    int result;

    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;
    out[5] = 0;
    out[6] = 0;
    entry = (MovieEntry *)(module + index * 0x74);
    obj = entry->obj;
    if (entry->field == 0 || obj == 0) {
        return 0;
    }
    fn_12_24970(&state);
    result = obj->vtable->fn24(obj, 1);
    obj->vtable->fn18(obj, 1, 0x7fffffff, v);
    if ((int)v[1] < result) {
        obj->vtable->fn18(obj, 1, 0x7fffffff, w);
        obj->vtable->fn1c(obj, 1, w);
    } else {
        w[0] = 0;
        w[1] = 0;
    }
    obj->vtable->fn1c(obj, 1, v);
    out[0] = v[0];
    out[1] = v[1];
    out[2] = w[0];
    out[3] = w[1];
    fn_12_24950(&state);
    return 0;
}
