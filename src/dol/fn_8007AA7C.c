#include "types.h"

typedef struct Block {
    u32 reserved;
    struct Block *next;
    u32 size;
} Block;

typedef struct Pool {
    Block *head;
} Pool;

extern Block *fn_8007AB58(Pool *, u32);
extern u32 fn_8007AC0C(Block *, u32);

u32 fn_8007AA7C(Pool *pool, u32 arg1) {
    Block *block;
    u32 size;
    u32 result;

    size = (arg1 + 15) & ~7;
    if (size < 80) {
        size = 80;
    }
    if (pool->head != 0) {
        block = pool->head;
    } else {
        block = fn_8007AB58(pool, size);
    }
    if (block == 0) {
        return 0;
    }
    do {
        if (size <= block->size) {
            result = fn_8007AC0C(block, size);
            if (result != 0) {
                pool->head = block;
                /* both search paths leave through the single return below */
                goto found;
            }
        }
        block = block->next;
    } while (block != pool->head);
    block = fn_8007AB58(pool, size);
    if (block == 0) {
        return 0;
    }
    result = fn_8007AC0C(block, size);
found:
    return result + 8;
}
