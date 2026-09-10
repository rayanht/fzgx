#include "types.h"

extern u32 __DVDThreadQueue;
extern u32 OSWakeupThread(u32);

void fn_800176D8(void) {
    OSWakeupThread((u32)&__DVDThreadQueue);
}
