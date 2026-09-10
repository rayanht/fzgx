#include "types.h"

extern u32 __DVDThreadQueue;
extern u32 OSWakeupThread(u32);

void fn_80019C24(void) {
    OSWakeupThread((u32)&__DVDThreadQueue);
}
