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

extern vu32 RunQueueBits_801A67F8;

// Hardware or OS state can change asynchronously.
extern volatile BOOL RunQueueHint_801A67FC; // fzgx-allow: S2 SDK asynchronous state

extern OSThreadQueue RunQueue_8015C018[32];

static inline void SetRun(OSThread *thread) {
    thread->queue = &RunQueue_8015C018[thread->priority];
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
    RunQueueBits_801A67F8 |= 1u << (31 - thread->priority);
    RunQueueHint_801A67FC = 1;
}

OSThread *SelectThread(BOOL yield);

static inline void __OSReschedule() {
    if (!RunQueueHint_801A67FC) {
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
