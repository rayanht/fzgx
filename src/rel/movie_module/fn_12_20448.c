#include "types.h"

extern void ADXT_Stop(void *arg0);

typedef struct MovieModule {
    u8 pad_0000[0x1b74];
    void *field_1b74;
} MovieModule;

int fn_12_20448(MovieModule *arg0) {
    ADXT_Stop(*(void **)arg0->field_1b74);
    return 0;
}
