#include "types.h"

typedef struct DVDCommandBlock {
    struct DVDCommandBlock *next;
    struct DVDCommandBlock *prev;
} DVDCommandBlock;

extern DVDCommandBlock WaitingQueue_8015CED8[4];

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 interrupts);

DVDCommandBlock *__DVDPopWaitingQueue(void) {
    u32 interrupts;
    s32 i;
    DVDCommandBlock *block;

    interrupts = OSDisableInterrupts();
    for (i = 0; i < 4; i++) {
        if (WaitingQueue_8015CED8[i].next != &WaitingQueue_8015CED8[i]) {
            OSRestoreInterrupts(interrupts);
            interrupts = OSDisableInterrupts();
            block = WaitingQueue_8015CED8[i].next;
            WaitingQueue_8015CED8[i].next = block->next;
            block->next->prev = &WaitingQueue_8015CED8[i];
            OSRestoreInterrupts(interrupts);
            block->next = NULL;
            block->prev = NULL;
            return block;
        }
    }
    OSRestoreInterrupts(interrupts);
    return NULL;
}
