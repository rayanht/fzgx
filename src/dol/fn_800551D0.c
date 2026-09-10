#include "types.h"

struct fn_800551D0_entry {
    u32 unk_0;
    char text[12];
};

struct fn_800551D0_state {
    void (*callback)(u32, u32, u32);
    u32 callback_arg;
    u8 unk_8[0x130];
    char buffer[0xc];
    struct fn_800551D0_entry entries[0x20];
};

extern struct fn_800551D0_state lbl_80187430;
extern char lbl_80091E70[37];
extern char lbl_80091E98[184];
extern size_t strlen(const char *);
extern s32 strncmp(const char *, const char *, size_t);
extern void *memcpy(void *, const void *, size_t);

static inline s32 fn_800551D0_find(char *arg0, struct fn_800551D0_entry *entry, u32 len) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (strncmp(arg0, entry->text, len) == 0) {
            return 1;
        }
        entry++;
    }
    return 0;
}

void fn_800551D0(char *arg0) {
    struct fn_800551D0_state *state;
    u32 len;
    u32 count;
    s32 i;

    state = &lbl_80187430;
    if (arg0 == 0) {
        if (state->callback != 0) {
            state->callback(state->callback_arg, (u32)&lbl_80091E70, 0);
        }
        return;
    }
    len = strlen(arg0);
    if (len == 0) {
        state->buffer[0] = 0;
        return;
    }
    count = strlen(arg0) + 1;
    for (i = 0; i < count; i++) {
        if (arg0[i] >= 'a' && arg0[i] <= 'z') {
            arg0[i] -= 0x20;
        }
    }
    if (fn_800551D0_find(arg0, state->entries, len) == 1) {
        memcpy(state->buffer, arg0, len + 1);
        return;
    }
    if (state->callback != 0) {
        state->callback(state->callback_arg, (u32)&lbl_80091E98, 0);
    }
}
