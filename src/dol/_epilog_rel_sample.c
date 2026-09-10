#include "types.h"

extern u32 DVDLowRequestError(u32);
extern void cbForStateGettingError(void);

u32 _epilog_rel_sample(void) {
    return DVDLowRequestError((u32)cbForStateGettingError);
}
