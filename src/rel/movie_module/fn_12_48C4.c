#include "types.h"

extern u32 lbl_12_bss_568[140];
extern const f32 lbl_12_rodata_4E8;

typedef struct MovieEntry {
    s32 active;
    u8 unk04[0x38];
    f32 unk3c;
    f32 unk40;
} MovieEntry;

MovieEntry *fn_12_48C4(void) {
    s32 count;
    MovieEntry *entry;
    MovieEntry *result;

    count = lbl_12_bss_568[2];
    entry = (MovieEntry *)&lbl_12_bss_568[3];
    for (; count > 0; count--) {
        if (entry->active == 0) {
            result = entry;
            goto found; // early hit on a free slot; must skip the clear below
        }
        entry++;
    }
    result = 0;
found:
    if (result != 0) {
        result->unk3c = lbl_12_rodata_4E8;
        result->unk40 = lbl_12_rodata_4E8;
        lbl_12_bss_568[0]++;
        result->active = 1;
    }
    return result;
}
