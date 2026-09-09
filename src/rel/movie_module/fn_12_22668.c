#include "types.h"

struct fn_12_22668_Copy16 {
    u32 a[4];
};

struct fn_12_22668_Entry {
    u8 pad[0x1150];
};

void fn_12_22668(u8 *module, int index, int subindex, struct fn_12_22668_Copy16 *dst) {
    struct fn_12_22668_Entry *entry;

    entry = (struct fn_12_22668_Entry *)(module + index * 0x74);
    entry = (struct fn_12_22668_Entry *)((u8 *)entry + subindex * 0x10);
    *dst = *(struct fn_12_22668_Copy16 *)((u8 *)entry + 0x1150);
}
