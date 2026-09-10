#include <types.h>
#include <dolphin/dsp.h>

extern DSPTaskInfo *lbl_801A6BBC;

extern DSPTaskInfo *lbl_801A6BB4;

extern DSPTaskInfo *lbl_801A6BB8;

void fn_800296F0(DSPTaskInfo *task) {
    DSPTaskInfo *temp;
    if (lbl_801A6BB8 == 0) {
        lbl_801A6BB8 = lbl_801A6BB4 = lbl_801A6BBC = task;
        task->next = task->prev = 0;
    } else {
        temp = lbl_801A6BB8;
        while (temp) {
            if (task->priority < temp->priority) {
                task->prev = temp->prev;
                temp->prev = task;
                task->next = temp;
                if (task->prev == 0) {
                    lbl_801A6BB8 = task;
                } else {
                    (task->prev)->next = task;
                }
                break;
            }
            temp = temp->next;
        }
        if (temp == 0) {
            lbl_801A6BB4->next = task;
            task->next = 0;
            task->prev = lbl_801A6BB4;
            lbl_801A6BB4 = task;
        }
    }
}
