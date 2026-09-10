#include <types.h>
#include <dolphin/dsp.h>

extern DSPTaskInfo *lbl_801A6BBC;

extern DSPTaskInfo *lbl_801A6BB4;

extern DSPTaskInfo *lbl_801A6BB8;

void fn_80029790(DSPTaskInfo *task) {
    task->flags = 0x00000000;
    task->state = 3;
    if (lbl_801A6BB8 == task) {
        if (task->next) {
            lbl_801A6BB8 = (task->next);
            task->next->prev = 0;
        } else {
            lbl_801A6BB8 = lbl_801A6BB4 = lbl_801A6BBC = 0;
        }
    } else if (lbl_801A6BB4 == task) {
        lbl_801A6BB4 = (task->prev);
        task->prev->next = 0;
        lbl_801A6BBC = lbl_801A6BB8;
    } else {
        lbl_801A6BBC = task->next;
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}
