#include <dolphin/os.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/types.h>

enum OS_THREAD_STATE {
    OS_THREAD_STATE_NULL = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_WAITING = 4,
    OS_THREAD_STATE_MORIBUND = 8,
};

extern vu32 RunQueueBits;

// Hardware or OS state can change asynchronously.
extern volatile BOOL RunQueueHint; // fzgx-allow: S2 SDK asynchronous state

extern OSThreadQueue RunQueue[32];

static inline void SetRun(OSThread *thread) {
    thread->queue = &RunQueue[thread->priority];
    do {
        OSThread *prev;
        prev = (thread->queue)->tail;
        if (prev == ((void *)0))
            (thread->queue)->head = (thread);
        else
            prev->link.next = (thread);
        (thread)->link.prev = prev;
        (thread)->link.next = ((void *)0);
        (thread->queue)->tail = (thread);
    } while (0);
    RunQueueBits |= 1u << (31 - thread->priority);
    RunQueueHint = 1;
}

OSThread *SelectThread(BOOL yield);

static inline void __OSReschedule() {
    if (!RunQueueHint) {
        return;
    }
    SelectThread(0);
}

void OSWakeupThread(OSThreadQueue *queue) {
    BOOL enabled;
    OSThread *thread;
    enabled = OSDisableInterrupts();
    while (queue->head) {
        do {
            OSThread *__next;
            (thread) = (queue)->head;
            __next = (thread)->link.next;
            if (__next == ((void *)0))
                (queue)->tail = ((void *)0);
            else
                __next->link.prev = ((void *)0);
            (queue)->head = __next;
        } while (0);
        thread->state = OS_THREAD_STATE_READY;
        if (!(0 < thread->suspend)) {
            SetRun(thread);
        }
    }
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}
