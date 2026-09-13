#include "types.h"

extern u32 fn_8000951C(u32);
extern s32 lbl_801A6740;
extern u32 lbl_801A6744;
extern u32 fn_800095A4(void);

typedef struct FreeBlock {
    s32 size;
    struct FreeBlock *prev;
    s32 next;
} FreeBlock;

#pragma opt_propagation off
u32 fn_80008FB0(u32 arg0, u32 arg1) {
    s32 i;
    FreeBlock *block;

    fn_8000951C(arg0);
    arg0 = (arg0 + 31) & ~31;
    arg1 &= ~31;
    block = (FreeBlock *)lbl_801A6744;
    i = 0;
    while (i < lbl_801A6740) {
        if (block->size < 0) {
            block->size = arg1 - arg0;
            ((FreeBlock *)arg0)->size = 0;
            ((FreeBlock *)arg0)->prev = 0;
            ((FreeBlock *)arg0)->next = block->size;
            block->prev = (FreeBlock *)arg0;
            block->next = 0;
            fn_800095A4();
            return i;
        }
        block++;
        i++;
    }
    fn_800095A4();
    return -1;
}
#pragma opt_propagation reset

