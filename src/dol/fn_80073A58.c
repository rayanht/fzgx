#include "dol/globals.h"

typedef struct Entry {
    u8 unk_00[0x18];
    s8 unk_18;
    u8 unk_19[0x03];
} Entry;

extern int fn_8008023C(Entry *entry, void *arg, int size);
extern void fn_80036AC4(int index, void *arg, s8 value);
extern void fn_800794F0(Entry *entry, void *arg, int size);

void fn_80073A58(int index, void *arg, s8 value) {
    Entry *entry;

    if (index == 0) {
        return;
    }

    if (index <= 3) {
        entry = (Entry *)((u8 *)lbl_801A6D38 + (index - 1) * 0x1c + 0x894);
    } else if (index <= 7) {
        entry = (Entry *)((u8 *)lbl_801A6D38 + (index - 5) * 0x1c + 0x894);
    } else if (index <= 11) {
        entry = (Entry *)((u8 *)lbl_801A6D38 + (index - 9) * 0x1c + 0x894);
    }

    if (entry->unk_18 == value) {
        if (fn_8008023C(entry, arg, 0x18) == 0) {
            return;
        }
    }

    fn_80036AC4(index, arg, value);
    fn_800794F0(entry, arg, 0x18);
    entry->unk_18 = value;
}
