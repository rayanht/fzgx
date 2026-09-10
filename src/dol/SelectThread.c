#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/types.h>
#include "sdk_addresses.h"

typedef volatile s32 vs32; // fzgx-allow: S2 SDK state mutated by exception handlers

typedef void (*OSSwitchThreadCallback)(OSThread *from, OSThread *to);

enum OS_THREAD_STATE {
    OS_THREAD_STATE_NULL = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_WAITING = 4,
    OS_THREAD_STATE_MORIBUND = 8,
};

struct SDK_OSThread____bss_0 {
    OSThreadQueue sdk_RunQueue[32];
    unsigned char sdk_padding_256[1584];
    OSContext sdk_IdleContext;
};

u32 OSSaveContext(OSContext *context);

OSContext *fn_8000BE5C();

OSThread *OSGetCurrentThread();

extern vu32 RunQueueBits_801A67F8;

extern volatile BOOL RunQueueHint_801A67FC; // fzgx-allow: S2 SDK asynchronous state

extern vs32 Reschedule_801A6800;

extern OSSwitchThreadCallback SwitchThreadCallback_801A6440;

OSThread *__OSCurrentThread : FZGX_ADDR___OSCurrentThread;

extern struct SDK_OSThread____bss_0 RunQueue_8015C018;

static inline void OSSetCurrentThread(OSThread *thread) {
    SwitchThreadCallback_801A6440(__OSCurrentThread, thread);
    __OSCurrentThread = thread;
}

static inline OSThread *OSGetCurrentThread() { return __OSCurrentThread; }

static inline void __OSSwitchThread(OSThread *nextThread) {
    OSSetCurrentThread(nextThread);
    OSSetCurrentContext(&nextThread->context);
    OSLoadContext(&nextThread->context);
}

OSThread *SelectThread(BOOL yield) {
    struct SDK_OSThread____bss_0 *sdk_storage____bss_0 = &RunQueue_8015C018;

    OSContext *currentContext;
    OSThread *currentThread;
    OSThread *nextThread;
    OSPriority priority;
    OSThreadQueue *queue;
    if (0 < Reschedule_801A6800) {
        return 0;
    }
    currentContext = fn_8000BE5C();
    currentThread = OSGetCurrentThread();
    if (currentContext != &currentThread->context) {
        return 0;
    }
    if (currentThread) {
        if (currentThread->state == OS_THREAD_STATE_RUNNING) {
            if (!yield) {
                priority = __cntlzw(RunQueueBits_801A67F8);
                if (currentThread->priority <= priority) {
                    return 0;
                }
            }
            currentThread->state = OS_THREAD_STATE_READY;
            currentThread->queue = &(sdk_storage____bss_0->sdk_RunQueue)[currentThread->priority];
            do {
                OSThread *prev;
                prev = (currentThread->queue)->tail;
                if (prev == ((void *)0))
                    (currentThread->queue)->head = (currentThread);
                else
                    prev->link.next = (currentThread);
                (currentThread)->link.prev = prev;
                (currentThread)->link.next = ((void *)0);
                (currentThread->queue)->tail = (currentThread);
            } while (0);
            RunQueueBits_801A67F8 |= 1u << (31 - currentThread->priority);
            RunQueueHint_801A67FC = 1;
        }
        if (!(currentThread->context.state & 0x02u) && OSSaveContext(&currentThread->context)) {
            return 0;
        }
    }
    if (RunQueueBits_801A67F8 == 0) {
        SwitchThreadCallback_801A6440(__OSCurrentThread, 0);
        __OSCurrentThread = 0;
        OSSetCurrentContext(&(sdk_storage____bss_0->sdk_IdleContext));
        do {
            OSEnableInterrupts();
            while (RunQueueBits_801A67F8 == 0)
                ;
            OSDisableInterrupts();
        } while (RunQueueBits_801A67F8 == 0);
        OSClearContext(&(sdk_storage____bss_0->sdk_IdleContext));
    }
    RunQueueHint_801A67FC = 0;
    priority = __cntlzw(RunQueueBits_801A67F8);
    queue = &(sdk_storage____bss_0->sdk_RunQueue)[priority];
    do {
        OSThread *__next;
        (nextThread) = (queue)->head;
        __next = (nextThread)->link.next;
        if (__next == ((void *)0))
            (queue)->tail = ((void *)0);
        else
            __next->link.prev = ((void *)0);
        (queue)->head = __next;
    } while (0);
    if (queue->head == 0) {
        RunQueueBits_801A67F8 &= ~(1u << (31 - priority));
    }
    nextThread->queue = ((void *)0);
    nextThread->state = OS_THREAD_STATE_RUNNING;
    __OSSwitchThread(nextThread);
    return nextThread;
}
