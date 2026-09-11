#include "types.h"

typedef struct MovieTable {
    u8 pad_0000[0x144];
    int arg3;
    int arg4;
} MovieTable;

typedef struct MovieModule {
    u8 pad_0000[0x1aec];
    MovieTable *movie_table;
} MovieModule;

extern int fn_12_24990(void *module);
extern int fn_12_24A88(int arg0, u32 arg1);

#pragma opt_dead_assignments off
int fn_12_26734(MovieModule *module, int index, int value, int arg3, int arg4) {
    MovieTable *table;
    int *entry;

    if (fn_12_24990(module) != 0) {
        return fn_12_24A88(0, 0xff000171);
    }

    if (index < 0xbc || index > 0xff) {
        return 0;
    }

    table = module->movie_table;
    table->arg3 = arg3;
    table->arg4 = arg4;
    entry = (int *)table + index;
    entry[-0xaf] = value;
    return 0;
}
#pragma opt_dead_assignments reset

