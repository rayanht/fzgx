#include "types.h"

typedef struct Fn80028424Node Fn80028424Node;

struct Fn80028424Node {
    Fn80028424Node *next;
    Fn80028424Node *prev;
    void *data;
};

extern u32 OSDisableInterrupts(void);
extern Fn80028424Node *lbl_801A6B90;
extern void OSRestoreInterrupts(u32 level);
extern void fn_80026D70(void *data);

void fn_80028424(Fn80028424Node *node) {
    u32 level;

    level = OSDisableInterrupts();
    if (node == lbl_801A6B90) {
        lbl_801A6B90 = node->next;
        if (lbl_801A6B90 != 0) {
            lbl_801A6B90->prev = 0;
        }
    } else {
        Fn80028424Node *next;
        Fn80028424Node *prev;

        next = node->next;
        prev = node->prev;
        prev->next = next;
        if (next != 0) {
            next->prev = prev;
        }
    }
    OSRestoreInterrupts(level);
    fn_80026D70(node->data);
}
