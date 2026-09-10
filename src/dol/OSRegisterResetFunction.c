#include <dolphin/os.h>
#include <dolphin/os/OSReset.h>

typedef struct OSResetQueue {
    OSResetFunctionInfo *first;
    OSResetFunctionInfo *last;
} OSResetQueue;

extern OSResetQueue ResetFunctionQueue_801A67D0;

void OSRegisterResetFunction(OSResetFunctionInfo *func) {
    OSResetFunctionInfo *tmp;
    OSResetFunctionInfo *iter;
    for (iter = ResetFunctionQueue_801A67D0.first; iter && iter->priority <= func->priority;
         iter = iter->next)
        ;
    if (iter == ((void *)0)) {
        tmp = ResetFunctionQueue_801A67D0.last;
        if (tmp == ((void *)0)) {
            ResetFunctionQueue_801A67D0.first = func;
        } else {
            tmp->next = func;
        }
        func->prev = tmp;
        func->next = ((void *)0);
        ResetFunctionQueue_801A67D0.last = func;
        return;
    }
    func->next = iter;
    tmp = iter->prev;
    iter->prev = func;
    func->prev = tmp;
    if (tmp == ((void *)0)) {
        ResetFunctionQueue_801A67D0.first = func;
        return;
    }
    tmp->next = func;
}
