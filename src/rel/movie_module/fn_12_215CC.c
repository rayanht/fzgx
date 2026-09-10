#include "types.h"

typedef struct MovieModule {
    u8 pad_0[0x1b74];
    void *field_1b74;
} MovieModule;

extern void ADXT_SetOutPan(void *);

void fn_12_215CC(MovieModule *movie) {
    ADXT_SetOutPan(*(void **)movie->field_1b74);
}
