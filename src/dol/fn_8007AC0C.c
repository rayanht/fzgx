#include "types.h"

typedef struct Block Block;

typedef struct SubBlock SubBlock;

struct Block {
    Block *prev;
    Block *next;
    unsigned long max_size;
    unsigned long size;
};

struct SubBlock {
    unsigned long size;
    Block *block;
    SubBlock *prev;
    SubBlock *next;
};

#define BLOCK_MIN_SIZE 0x50

#define Block_size(bp) ((bp)->size & ~7)
#define Block_start(bp) (*(SubBlock **)((char *)(bp) + Block_size(bp) - sizeof(unsigned long)))
#define SubBlock_size(sb) ((sb)->size & ~7)
#define SubBlock_block(sb) ((Block *)((unsigned long)(sb)->block & ~1))
#define SubBlock_is_free(sb) (!((sb)->size & 2))
#define SubBlock_is_prev_allocated(sb) ((sb)->size & 4)

static inline void SubBlock_construct(SubBlock *sb, unsigned long size, Block *bp, int prev_alloc, int this_alloc) {
    sb->block = (Block *)((unsigned long)bp | 1);
    sb->size = size;
    if (prev_alloc) {
        sb->size |= 4;
    }
    if (this_alloc) {
        sb->size |= 2;
        *(unsigned long *)((char *)sb + size) |= 4;
    } else {
        *(unsigned long *)((char *)sb + size - sizeof(unsigned long)) = size;
    }
}

static inline void SubBlock_split(SubBlock *sb, unsigned long size) {
    SubBlock *np = (SubBlock *)((char *)sb + size);
    Block *bp = SubBlock_block(sb);
    int is_free = SubBlock_is_free(sb);
    int is_prev_alloc = SubBlock_is_prev_allocated(sb);
    unsigned long orig_size = SubBlock_size(sb);

    SubBlock_construct(sb, size, bp, is_prev_alloc, !is_free);
    SubBlock_construct(np, orig_size - size, bp, !is_free, !is_free);
    if (is_free) {
        np->next = sb->next;
        np->next->prev = np;
        np->prev = sb;
        sb->next = np;
    }
}

static inline void SubBlock_set_not_free(SubBlock *sb) {
    unsigned long this_size = SubBlock_size(sb);

    sb->size |= 2;
    *(unsigned long *)((char *)sb + this_size) |= 4;
}

SubBlock *fn_8007AC0C(Block *bp, unsigned long size) {
    SubBlock *start;
    SubBlock *sb;
    unsigned long sb_size;
    unsigned long max_found;
    SubBlock **start_slot;

    start = Block_start(bp);
    if (start == NULL) {
        bp->max_size = 0;
        return NULL;
    }

    sb = start;
    sb_size = SubBlock_size(sb);
    max_found = sb_size;
    while (sb_size < size) {
        sb = sb->next;
        sb_size = SubBlock_size(sb);
        if (max_found < sb_size) {
            max_found = sb_size;
        }
        if (sb == start) {
            bp->max_size = max_found;
            return NULL;
        }
    }

    if (sb_size - size >= BLOCK_MIN_SIZE) {
        SubBlock_split(sb, size);
    }
    Block_start(bp) = sb->next;
    SubBlock_set_not_free(sb);
    start_slot = &Block_start(bp);
    if (*start_slot == sb) {
        *start_slot = sb->next;
    }
    if (*start_slot == sb) {
        *start_slot = NULL;
        bp->max_size = 0;
    } else {
        sb->next->prev = sb->prev;
        sb->prev->next = sb->next;
    }
    return sb;
}
