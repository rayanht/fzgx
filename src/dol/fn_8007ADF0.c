#include "types.h"

typedef struct Block Block;

typedef struct SubBlock SubBlock;

struct Block {
    Block *prev;
    Block *next;
    unsigned long max_size;
    unsigned long size;
};

typedef struct BlockEnd {
    unsigned long size;
    SubBlock *start;
} BlockEnd;

struct SubBlock {
    unsigned long size;
    Block *block;
    SubBlock *prev;
    SubBlock *next;
};

#define Block_size(bp) ((bp)->size & ~7)
#define Block_start(bp) (*(SubBlock **)((char *)(bp) + Block_size(bp) - sizeof(unsigned long)))
#define SubBlock_size(sb) ((sb)->size & ~7)
#define SubBlock_is_free(sb) (!((sb)->size & 2))
#define SubBlock_is_prev_allocated(sb) ((sb)->size & 4)

#define SubBlock_set_size(sb, sz)                                                     \
    (sb)->size &= 7;                                                                  \
    (sb)->size |= (sz) & ~7;                                                          \
    if (SubBlock_is_free(sb)) {                                                       \
        *(unsigned long *)((char *)(sb) + (sz) - sizeof(unsigned long)) = (sz);      \
    }

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

static inline void SubBlock_set_free(SubBlock *sb) {
    unsigned long this_size = SubBlock_size(sb);

    sb->size &= ~2;
    *(unsigned long *)((char *)sb + this_size) &= ~4;
    *(unsigned long *)((char *)sb + this_size - sizeof(unsigned long)) = this_size;
}

static inline SubBlock *SubBlock_merge_prev(SubBlock *sb, SubBlock **start) {
    unsigned long prev_size;
    SubBlock *prev;

    if (!SubBlock_is_prev_allocated(sb)) {
        prev_size = *(unsigned long *)((char *)sb - sizeof(unsigned long));
        if (prev_size & 2) {
            return sb;
        }
        prev = (SubBlock *)((char *)sb - prev_size);
        SubBlock_set_size(prev, prev_size + SubBlock_size(sb));
        if (*start == sb) {
            *start = (*start)->next;
        }
        sb->next->prev = sb->prev;
        sb->next->prev->next = sb->next;
        return prev;
    }
    return sb;
}

static inline void SubBlock_merge_next(SubBlock *sb, SubBlock **start) {
    SubBlock *next;
    unsigned long this_size;

    next = (SubBlock *)((char *)sb + SubBlock_size(sb));
    if (SubBlock_is_free(next)) {
        this_size = SubBlock_size(sb) + SubBlock_size(next);
        SubBlock_set_size(sb, this_size);
        if (SubBlock_is_free(sb)) {
            *(unsigned long *)((char *)sb + this_size) &= ~4;
        } else {
            *(unsigned long *)((char *)sb + this_size) |= 4;
        }
        if (*start == next) {
            *start = (*start)->next;
        }
        if (*start == next) {
            *start = NULL;
        }
        next->next->prev = next->prev;
        next->prev->next = next->next;
    }
}

static inline void Block_link(Block *bp, SubBlock *sb) {
    SubBlock **start;

    SubBlock_set_free(sb);
    start = &Block_start(bp);
    if (*start != NULL) {
        sb->prev = (*start)->prev;
        sb->prev->next = sb;
        sb->next = *start;
        (*start)->prev = sb;
        *start = sb;
        *start = SubBlock_merge_prev(*start, start);
        SubBlock_merge_next(*start, start);
    } else {
        *start = sb;
        sb->prev = sb;
        sb->next = sb;
    }
    if (bp->max_size < SubBlock_size(*start)) {
        bp->max_size = SubBlock_size(*start);
    }
}

void fn_8007ADF0(Block *bp, unsigned long size) {
    SubBlock *sb;

    bp->size = size | 3;
    ((BlockEnd *)((char *)bp + size - sizeof(BlockEnd)))->size = bp->size;
    sb = (SubBlock *)((char *)bp + sizeof(Block));
    SubBlock_construct(sb, size - sizeof(Block) - sizeof(BlockEnd), bp, 0, 0);
    bp->max_size = size - sizeof(Block) - sizeof(BlockEnd);
    Block_start(bp) = NULL;
    Block_link(bp, sb);
}
