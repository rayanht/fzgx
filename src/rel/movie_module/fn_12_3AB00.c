#include "types.h"

typedef struct MovieObject {
    u8 pad[0x68];
} MovieObject;

typedef struct MovieManager {
    u8 pad40[0x40];
    void (*callback0)(void *);
    void *callback0_arg;
    void (*callback1)(void *);
    void *callback1_arg;
    u8 pad50[0x4];
    s32 state;
} MovieManager;

extern s32 lbl_12_bss_1B9DC[52];
extern MovieManager *fn_12_38DBC(void);
extern s32 fn_12_34C44(s32 *state);
extern u32 fn_12_3AA58(MovieObject *self);
extern s32 SFD_IsSvrWait(void);

#pragma opt_lifetimes off
u32 fn_12_3AB00(void) {
    MovieManager *manager;
    MovieManager *manager2;
    MovieObject *movie;
    register s32 result;
    void (*callback)(void *);
    void *arg;

    if (lbl_12_bss_1B9DC[0] != 1) {
        return 0;
    }

    manager = fn_12_38DBC();
    if (fn_12_34C44(&manager->state) == 0) {
        return 0;
    }

    manager2 = fn_12_38DBC();
    callback = manager2->callback0;
    arg = manager2->callback0_arg;
    if (callback != 0) {
        callback(arg);
    }

    result = 0;
    movie = (MovieObject *)manager;
    do {
        if ((u8 *)movie + 0x68 != 0) {
            fn_12_3AA58((MovieObject *)((u8 *)movie + 0x68));
        }
        result++;
        movie = (MovieObject *)((u8 *)movie + 0x228);
    } while (result < 8);

    manager2 = fn_12_38DBC();
    manager2->state = 0;
    {
        u32 raw = SFD_IsSvrWait();
        result = ((1 - raw) | (raw - 1)) >> 31;
    }
    manager2 = fn_12_38DBC();
    callback = manager2->callback1;
    arg = manager2->callback1_arg;
    if (callback != 0) {
        callback(arg);
    }
    return result;
}
#pragma opt_lifetimes reset
