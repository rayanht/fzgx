#include <dolphin/os.h>
#include <dolphin/os/OSThread.h>

BOOL OSIsThreadTerminated(OSThread *thread) {
    return thread->state == 8 || thread->state == 0 ? 1 : 0;
}
