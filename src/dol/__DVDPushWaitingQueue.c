#include "types.h"

typedef struct DVDCommandBlock {
    struct DVDCommandBlock *next;
    struct DVDCommandBlock *prev;
} DVDCommandBlock;

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern DVDCommandBlock WaitingQueue_8015CED8[];

u32 __DVDPushWaitingQueue(u32 index, DVDCommandBlock *block) {
    u32 interrupts;
    DVDCommandBlock *queue;

    interrupts = OSDisableInterrupts();
    queue = &WaitingQueue_8015CED8[index];
    queue->prev->next = block;
    block->prev = queue->prev;
    block->next = queue;
    queue->prev = block;
    OSRestoreInterrupts(interrupts);
    return 1;
}
