#include "types.h"

extern u32 RunQueueHint;
extern u32 SelectThread(u32);

void __OSReschedule(void) {
    if ((s32)RunQueueHint != 0) {
    SelectThread(0);
    }
}
