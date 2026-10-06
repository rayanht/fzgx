#include "types.h"

typedef struct Fn12_38340_Allocator {
    u8 pad_0[0x28];
    u32 (*alloc)(u32, s32);
    u8 pad_2C[0x4];
    u32 alloc_arg;
} Fn12_38340_Allocator;

typedef struct Fn12_38340_FramePool {
    u8 pad_0[0x158];
    u32 buffer;
    u32 limit;
    u32 cursor;
    u32 used;
    s32 count;
    u32 frames[32];
} Fn12_38340_FramePool;

typedef struct Fn12_38340_FrameSize {
    u8 pad_0[0x8];
    s32 width;
    s32 height;
} Fn12_38340_FrameSize;

extern char lbl_12_rodata_1DF4[];
extern void MWSFSVM_Error(const char *, ...);
extern Fn12_38340_Allocator *fn_12_38DBC(void);

static inline u32 fn_12_38340_AllocFrame(Fn12_38340_FramePool *pool, s32 size) {
    Fn12_38340_Allocator *allocator;
    u32 frame;

    if (pool->count >= 32) {
        MWSFSVM_Error(lbl_12_rodata_1DF4);
        return 0;
    }
    if (size < 0) {
        return 0;
    }
    if (pool->buffer != 0) {
        if (pool->used + size > pool->limit) {
            frame = 0;
        } else {
            frame = pool->cursor;
            pool->cursor = frame + size;
            pool->used += size;
        }
    } else {
        allocator = fn_12_38DBC();
        frame = allocator->alloc(allocator->alloc_arg, size);
    }
    if (frame != 0) {
        pool->frames[pool->count] = frame;
        pool->count++;
    }
    return frame;
}

s32 fn_12_38340(Fn12_38340_FramePool *pool, Fn12_38340_FrameSize *frame_size, u32 *frames) {
    s32 width;
    s32 height;
    s32 size;
    s32 result;

    result = 0;
    width = (frame_size->width + 15) / 16 * 16;
    height = (frame_size->height + 15) / 16 * 16;
    size = height * ((width + 31) / 32 * 32) + (height / 2) * ((width / 2 + 31) / 32 * 32) * 2 + 32;

    frames[0] = fn_12_38340_AllocFrame(pool, size);
    frames[1] = fn_12_38340_AllocFrame(pool, size);
    if (frames[0] == 0 || frames[1] == 0) {
        result = -1;
    }
    return result;
}
