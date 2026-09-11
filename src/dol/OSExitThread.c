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

void OSWakeupThread(OSThreadQueue *queue);

// Hardware or OS state can change asynchronously.
extern volatile BOOL RunQueueHint; // fzgx-allow: S2 SDK asynchronous state

OSThread *__OSCurrentThread : FZGX_ADDR___OSCurrentThread;

OSThreadQueue __OSActiveThreadQueue : FZGX_ADDR___OSActiveThreadQueue;

OSThread *SelectThread(BOOL yield);

void OSWakeupThread(OSThreadQueue *queue);

void OSExitThread(void *val) {
    OSThread *thread;
    BOOL enable;
    enable = OSDisableInterrupts();
    thread = __OSCurrentThread;
    OSClearContext(&thread->context);
    if (thread->attr & 0x0001u) {
        do {
            OSThread *next, *prev;
            next = (thread)->linkActive.next;
            prev = (thread)->linkActive.prev;
            if (next == ((void *)0))
                (&__OSActiveThreadQueue)->tail = prev;
            else
                next->linkActive.prev = prev;
            if (prev == ((void *)0))
                (&__OSActiveThreadQueue)->head = next;
            else
                prev->linkActive.next = next;
        } while (0);
        thread->state = OS_THREAD_STATE_NULL;
    } else {
        thread->state = OS_THREAD_STATE_MORIBUND;
        thread->val = val;
    }
    __OSUnlockAllMutex(thread);
    OSWakeupThread(&thread->queueJoin);
    RunQueueHint = 1;
    if (RunQueueHint != 0) {
        SelectThread(0);
    }
    OSRestoreInterrupts(enable);
}
