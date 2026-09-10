#include "types.h"

typedef struct MovieValues {
    u32 value_00;
    u32 value_04;
    u32 value_08;
    u32 value_0c;
    u32 value_10;
    u32 value_14;
    u32 value_18;
    u32 value_1c;
} MovieValues;

typedef struct MovieModule {
    u8 _pad00[0x20];
    MovieValues values;
} MovieModule;

extern int fn_12_6C78(MovieModule *module);
extern int fn_12_6D5C(int arg0, int arg1);

int fn_12_68D4(MovieModule *module, MovieValues *result) {
    if (fn_12_6C78(module)) {
        return fn_12_6D5C(0, 0xff020202);
    }
    *result = module->values;
    return 0;
}
