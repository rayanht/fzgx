#include "types.h"

extern u8 __files[320];
extern u32 fn_8007A1C0(u32);
extern void *memset(void *, u32, u32);

typedef struct FileNode {
    u8 pad0[4];
    u16 flags;
    u8 pad6[6];
    u8 active;
    u8 padd[0x3f];
    struct FileNode *next;
} FileNode;

typedef struct FileRoot {
    u8 pad0[0xec];
    FileNode *next;
} FileRoot;

u32 fn_8007B2A8(void) {
    FileNode *node;
    FileNode *new_node;
    FileNode *last;

    node = ((FileRoot *)__files)->next;
    while (node != 0) {
        if (!(((node->flags >> 6) & 7) != 0)) {
            return (u32)node;
        } else {
            last = node;
            node = node->next;
        }
    }
    new_node = (FileNode *)fn_8007A1C0(0x50);
    if (new_node != 0) {
        memset(new_node, 0, 0x50);
        new_node->active = 1;
        last->next = new_node;
        return (u32)new_node;
    }
    return 0;
}
