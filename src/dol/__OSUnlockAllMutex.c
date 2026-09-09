#include "types.h"

typedef struct OSMutex OSMutex;
typedef struct OSThread OSThread;

struct OSMutex {
    u8 pad0[0x8];
    OSMutex *queueHead;
    OSMutex *queueTail;
    OSMutex *next;
    OSMutex *prev;
};

struct OSThread {
    u8 pad0[0x2F4];
    OSMutex *mutexQueueHead;
    OSMutex *mutexQueueTail;
};

extern void fn_80011194(OSMutex *);

void __OSUnlockAllMutex(OSThread *thread) {
    OSMutex *mutex;
    OSMutex *next;
    OSMutex *zero = 0;

    while (thread->mutexQueueHead != NULL) {
        mutex = thread->mutexQueueHead;
        next = mutex->next;
        if (next == NULL) {
            thread->mutexQueueTail = zero;
        } else {
            next->prev = zero;
        }
        thread->mutexQueueHead = next;
        mutex->queueTail = zero;
        mutex->queueHead = zero;
        fn_80011194(mutex);
    }
}
