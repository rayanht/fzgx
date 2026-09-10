#include <dolphin/os.h>
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

void fn_8001036C(OSThread *thread);

OSThread *fn_80010410(OSThread *thread, OSPriority priority) {
    switch (thread->state) {
    case OS_THREAD_STATE_READY:
        fn_8001036C(thread);
        thread->priority = priority;
        SetRun(thread);
        break;
    case OS_THREAD_STATE_WAITING:
        do {
            OSThread *next, *prev;
            next = (thread)->link.next;
            prev = (thread)->link.prev;
            if (next == ((void *)0))
                (thread->queue)->tail = prev;
            else
                next->link.prev = prev;
            if (prev == ((void *)0))
                (thread->queue)->head = next;
            else
                prev->link.next = next;
        } while (0);
        thread->priority = priority;
        do {
            OSThread *prev, *next;
            for (next = (thread->queue)->head; next && next->priority <= thread->priority;
                 next = next->link.next)
                ;
            if (next == ((void *)0))
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
            else {
                (thread)->link.next = next;
                prev = next->link.prev;
                next->link.prev = (thread);
                (thread)->link.prev = prev;
                if (prev == ((void *)0))
                    (thread->queue)->head = (thread);
                else
                    prev->link.next = (thread);
            }
        } while (0);
        if (thread->mutex) {
            return thread->mutex->thread;
        }
        break;
    case OS_THREAD_STATE_RUNNING:
        RunQueueHint_801A67FC = 1;
        thread->priority = priority;
        break;
    }
    return ((void *)0);
}
