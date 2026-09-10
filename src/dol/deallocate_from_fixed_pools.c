
#include "types.h"

typedef struct Block Block;

typedef struct FixBlock FixBlock;

typedef struct FixSubBlock FixSubBlock;

struct Block {
    Block *prev;
    Block *next;
    unsigned long max_size;
    unsigned long size;
};

struct FixBlock {
    FixBlock *prev;
    FixBlock *next;
    unsigned long client_size;
    FixSubBlock *free;
    unsigned long allocated;
};

struct FixSubBlock {
    FixBlock *block;
    FixSubBlock *next;
};

typedef struct FixStart {
    FixBlock *tail;
    FixBlock *head;
} FixStart;

typedef struct MemPoolObj {
    Block *start;
    FixStart fixed[6];
} MemPoolObj;

void free(void *allocation);

extern const unsigned long lbl_80094EC0[];

void fn_8007A710(MemPoolObj *pool, void *ptr);

void deallocate_from_fixed_pools(MemPoolObj *pool, void *ptr, unsigned long size) {
    unsigned long index = 0;
    FixSubBlock *subblock;
    FixBlock *block;
    FixStart *start;
    while (size > lbl_80094EC0[index]) {
        index++;
    }
    start = &pool->fixed[index];
    subblock = (FixSubBlock *)((unsigned char *)ptr - 4);
    block = subblock->block;
    if (block->free == ((void *)0) && start->head != block) {
        if (start->tail == block) {
            start->head = start->head->prev;
            start->tail = start->tail->prev;
        } else {
            block->prev->next = block->next;
            block->next->prev = block->prev;
            block->next = start->head;
            block->prev = block->next->prev;
            block->prev->next = block;
            block->next->prev = block;
            start->head = block;
        }
    }
    subblock->next = block->free;
    block->free = subblock;
    if (--block->allocated == 0) {
        if (start->head == block) {
            start->head = block->next;
        }
        if (start->tail == block) {
            start->tail = block->prev;
        }
        block->prev->next = block->next;
        block->next->prev = block->prev;
        if (start->head == block) {
            start->head = ((void *)0);
        }
        if (start->tail == block) {
            start->tail = ((void *)0);
        }
        fn_8007A710(pool, block);
    }
}
