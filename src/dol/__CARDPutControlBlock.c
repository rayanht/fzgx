#include "types.h"

extern u32 OSDisableInterrupts(void);
extern u32 OSRestoreInterrupts(u32);

typedef struct CARDControlBlock {
    s32 attached;
    s32 callback;
} CARDControlBlock;

u32 __CARDPutControlBlock(CARDControlBlock *block, u32 callback) {
    u32 irq;
    irq = OSDisableInterrupts();
    if (block->attached != 0) {
        block->callback = callback;
    } else if (block->callback == -1) {
        block->callback = callback;
    }
    OSRestoreInterrupts(irq);
    return callback;
}
