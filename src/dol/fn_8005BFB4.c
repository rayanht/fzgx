#include "types.h"

typedef struct Fn8005BFB4_Handle {
    s32 used;
    u32 unk_4;
    u32 unk_8;
} Fn8005BFB4_Handle;

typedef struct Fn8005BFB4_Work {
    s32 init_count;
    u32 unk_4;
    u32 unk_8;
    u32 unk_C;
    u32 unk_10;
    Fn8005BFB4_Handle handles[32];
} Fn8005BFB4_Work;

extern Fn8005BFB4_Work lbl_80192BD0;
extern char lbl_800929AC[];
extern void *memset(void *, int, u32);
extern u32 fn_8001E9BC(u32 *);
extern void fn_8005A5BC(const char *);

static inline void fn_8005BFB4_Destroy(Fn8005BFB4_Handle *handle) {
    if (handle != NULL) {
        handle->used = 0;
    }
}

void fn_8005BFB4(void) {
    Fn8005BFB4_Work *work = &lbl_80192BD0;
    Fn8005BFB4_Handle *handle;
    s32 i;
    u32 time;

    if (--work->init_count != 0) {
        return;
    }

    handle = work->handles;
    for (i = 0; i < 32; i++) {
        if (handle->used == 1) {
            fn_8005BFB4_Destroy(handle);
        }
        handle++;
    }
    memset(work->handles, 0, sizeof(work->handles));

    if (work->unk_4 == 0) {
        fn_8001E9BC(&time);
        if (time != work->unk_C) {
            fn_8005A5BC(lbl_800929AC);
        }
        work->unk_8 = 0;
        work->unk_C = 0;
        work->unk_10 = 0;
    }
}
