#include "types.h"

typedef struct FnEntry {
    u8 padding[8];
    s32 field_08;
    s32 field_0c;
    s32 field_10;
    s32 field_14;
    s32 field_18;
} FnEntry;

void fn_12_2E218(s32 value, FnEntry *entry, s32 *result, s32 *out) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = entry->field_0c * 3600000;
    b = entry->field_08 * 216000000;
    c = entry->field_10 * 60000;
    d = (entry->field_14 + entry->field_18) * 1000;
    *result = a + b + c + d;
    *out = 60000;
    *out = value;
}
