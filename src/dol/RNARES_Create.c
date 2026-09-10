
#include "types.h"

typedef struct RNAResource {
    int used;
    u32 buffer;
    u32 size;
} RNAResource;

void fn_8005A5BC(const char *message);

extern RNAResource lbl_80192BE4[32];

RNAResource *RNARES_Create(void) {
    int i;
    RNAResource *resource;
    for (i = 0; i < 32; i++) {
        if (lbl_80192BE4[i].used == 0) {
            break;
        }
    }
    if (i == 32) {
        fn_8005A5BC("E1070313:Not enough RNARES handle.\n");
        return 0;
    }
    resource = &lbl_80192BE4[i];
    resource->used = 1;
    return resource;
}
