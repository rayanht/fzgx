#include "types.h"

typedef struct Node Node;
struct Node {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0c;
    void (*callback)(Node *);
};

extern Node *fn_80020A0C(void);
extern void fn_80020A28(Node *);
extern void fn_800209DC(Node *);

void fn_80020800(void) {
    Node *node;

    node = fn_80020A0C();
    while (node != 0) {
        if (node->unk_0c != 0) {
            if (node->callback != 0) {
                node->callback(node);
            }
            fn_80020A28(node);
            fn_800209DC(node);
        }
        node = fn_80020A0C();
    }
}
