#include <dolphin/os.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include "sdk_addresses.h"

enum OS_THREAD_STATE {
    OS_THREAD_STATE_NULL = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_WAITING = 4,
    OS_THREAD_STATE_MORIBUND = 8,
};

OSThread *OSGetCurrentThread();

// Hardware or OS state can change asynchronously.
extern volatile BOOL RunQueueHint_801A67FC; // fzgx-allow: S2 SDK asynchronous state

OSThread *__OSCurrentThread : FZGX_ADDR___OSCurrentThread;

static inline OSThread *OSGetCurrentThread() { return __OSCurrentThread; }

OSThread *SelectThread(BOOL yield);

static inline void __OSReschedule() {
    if (!RunQueueHint_801A67FC) {
        return;
    }
    SelectThread(0);
}

void OSSleepThread(OSThreadQueue *queue) {
    BOOL enabled;
    OSThread *currentThread;
    enabled = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();
    currentThread->state = OS_THREAD_STATE_WAITING;
    currentThread->queue = queue;
    do {
        OSThread *prev, *next;
        for (next = (queue)->head; next && next->priority <= currentThread->priority;
             next = next->link.next)
            ;
        if (next == ((void *)0))
            do {
                OSThread *prev;
                prev = (queue)->tail;
                if (prev == ((void *)0))
                    (queue)->head = (currentThread);
                else
                    prev->link.next = (currentThread);
                (currentThread)->link.prev = prev;
                (currentThread)->link.next = ((void *)0);
                (queue)->tail = (currentThread);
            } while (0);
        else {
            (currentThread)->link.next = next;
            prev = next->link.prev;
            next->link.prev = (currentThread);
            (currentThread)->link.prev = prev;
            if (prev == ((void *)0))
                (queue)->head = (currentThread);
            else
                prev->link.next = (currentThread);
        }
    } while (0);
    RunQueueHint_801A67FC = 1;
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}
