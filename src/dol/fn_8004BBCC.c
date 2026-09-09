#include "types.h"

extern char lbl_80090A28[45];
extern void fn_800474E4(void *arg);

typedef struct {
    u8 _pad[0x72];
    s8 value;
} Fn8004BBCCObject;

s32 fn_8004BBCC(Fn8004BBCCObject *object) {
    if (object == 0) {
        fn_800474E4(lbl_80090A28);
        return 0;
    }
    return object->value;
}
