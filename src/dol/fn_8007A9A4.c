#include "types.h"

typedef struct Node {
    u32 pad0;
    struct Node *next;
    u32 size;
} Node;

extern u32 fn_8007AC0C(Node *, u32);

u32 fn_8007A9A4(Node **head, u32 size, u32 *remaining) {
    Node *node;
    u32 result;

    size = (size + 15) & ~7;
    if (size < 0x50) {
        size = 0x50;
    }
    *remaining = 0;
    node = *head;
    if (node == 0) {
        return 0;
    }
    do {
        if (size <= node->size) {
            result = fn_8007AC0C(node, size);
            if (result != 0) {
                *head = node;
                /* both exits leave through the single return below */
                goto found;
            }
        }
        if (node->size > 8 && *remaining < node->size - 8) {
            *remaining = node->size - 8;
        }
        node = node->next;
    } while (node != *head);
    return 0;
found:
    return result + 8;
}
