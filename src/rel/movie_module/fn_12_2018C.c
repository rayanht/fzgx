#include "types.h"

typedef struct MovieState {
    void *object;
    u8 unk_04[0x30];
    s32 active;
    u8 unk_38[4];
    void (*callback)(void);
    s32 count;
} MovieState;

typedef struct MovieRequest {
    s32 ready;
    u8 unk_04[8];
    void *arg1;
    void *arg2;
    void *arg3;
} MovieRequest;

typedef struct MovieModule {
    u8 unk_0000[0x1b74];
    MovieState *state;
    u8 unk_1b78[0xd90];
    MovieRequest *request;
} MovieModule;

extern void ADXT_InsertHdrSfa(void *, void *, void *, void *);
extern void fn_8004BA38(void *, int);
extern void fn_12_20A7C(void);

s32 fn_12_2018C(MovieModule *module) {
    MovieRequest *request;
    MovieState *state;
    MovieRequest *data;
    void *object;

    request = module->request;
    state = module->state;
    if (request == 0) {
        data = 0;
    } else if (state->count > 0) {
        data = 0;
    } else {
        data = (MovieRequest *)((u8 *)request + 0xcfc);
    }
    if (data == 0) {
        return 0;
    }
    object = state->object;
    if (state->active != 0) {
        return 0;
    }
    if (data->ready == 0) {
        return 0;
    }
    ADXT_InsertHdrSfa(object, data->arg1, data->arg2, data->arg3);
    fn_8004BA38(object, 0);
    state->active = 1;
    state->callback = fn_12_20A7C;
    return 0;
}
