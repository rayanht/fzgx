#ifndef DOLPHIN_OS_OSTHREAD_H
#define DOLPHIN_OS_OSTHREAD_H

#include <dolphin/os/OSContext.h>

typedef struct OSThread OSThread;

typedef struct OSThreadQueue OSThreadQueue;

typedef struct OSThreadLink OSThreadLink;

typedef s32 OSPriority;

typedef struct OSMutex OSMutex;

typedef struct OSMutexQueue OSMutexQueue;

typedef struct OSMutexLink OSMutexLink;

struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
};

struct OSThreadLink {
    OSThread *next;
    OSThread *prev;
};

struct OSMutexQueue {
    OSMutex *head;
    OSMutex *tail;
};

struct OSMutexLink {
    OSMutex *next;
    OSMutex *prev;
};

struct OSThread {
    OSContext context;
    u16 state;
    u16 attr;
    s32 suspend;
    OSPriority priority;
    OSPriority base;
    void *val;
    OSThreadQueue *queue;
    OSThreadLink link;
    OSThreadQueue queueJoin;
    OSMutex *mutex;
    OSMutexQueue queueMutex;
    OSThreadLink linkActive;
    u8 *stackBase;
    u32 *stackEnd;
    s32 error;
    void *specific[2];
};

struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    OSMutexLink link;
};

#endif
