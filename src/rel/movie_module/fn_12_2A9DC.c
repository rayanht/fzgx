#include "types.h"

typedef struct MovieEntry {
    int type;
    char pad[4];
    int priority;
    char tail[0x6c];
} MovieEntry;

typedef struct MovieManager {
    char pad0[0x7c];
    int flag_a;
    int flag_b;
    char pad1[0xb0];
    int count;
    MovieEntry entries[1];
} MovieManager;

typedef struct MovieObject {
    char pad[0x1b30];
    MovieManager *manager;
} MovieObject;

extern void fn_12_24970(void *);
extern void fn_12_24950(void *);

MovieEntry *fn_12_2A9DC(MovieObject *movie, int *result) {
    MovieEntry *best;
    int selected;
    MovieEntry *entry;
    MovieManager *manager;
    int count;
    int i;
    int scratch;
    int replace;

    fn_12_24970(&scratch);
    manager = movie->manager;
    best = 0;
    selected = 0;
    count = manager->count;
    entry = manager->entries;
    *result = 0;
    for (i = 0; i < count; i++) {
        if (entry->type == 2 || entry->type == 4) {
            selected++;
            if (best == 0) {
                replace = 1;
            } else if (best->priority > entry->priority) {
                replace = 1;
            } else {
                replace = 0;
            }
            if (replace) {
                best = entry;
            }
        }
        entry++;
    }
    if (selected == 1) {
        if (manager->flag_a != 0) {
            *result = 1;
        } else if (manager->flag_b == 0) {
            best = 0;
        }
    }
    fn_12_24950(&scratch);
    return best;
}
