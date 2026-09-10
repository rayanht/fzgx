#include "types.h"

extern void fn_12_24970(void *arg0);
extern int fn_12_2D73C(void *arg0, int arg1);
extern int fn_12_2DEB0(void *arg0, int arg1, int arg2);
extern void fn_12_24950(void *arg0);

typedef struct MovieEntry {
    int type;
    unsigned char _pad[4];
    int value;
    int value2;
    unsigned char _pad2[0x68];
} MovieEntry;

typedef struct MovieList {
    unsigned char _pad0[0x7c];
    int flag;
    unsigned char _pad1[0xb4];
    int count;
    MovieEntry entries[1];
} MovieList;

typedef struct MovieModule {
    unsigned char _pad0[0x48];
    int state;
    unsigned char _pad1[0x1ae4];
    MovieList *movie_list;
} MovieModule;

int fn_12_2A85C(MovieModule *arg0) {
    unsigned char local[8];
    int matches;
    MovieEntry *entry;
    MovieEntry *previous;
    MovieEntry *current;
    int count;
    MovieList *list;
    int choose;

    fn_12_24970(local);
    list = arg0->movie_list;
    previous = 0;
    current = 0;
    matches = 0;
    count = list->count;
    entry = list->entries;
    for (; count > 0; count--) {
        if (entry->type == 2 || entry->type == 4) {
            matches++;
            if (current == 0) {
                choose = 1;
            } else if (current->value > entry->value) {
                choose = 1;
            } else {
                choose = 0;
            }
            if (choose) {
                previous = current;
                current = entry;
            } else {
                if (previous == 0) {
                    choose = 1;
                } else if (previous->value > entry->value) {
                    choose = 1;
                } else {
                    choose = 0;
                }
                if (choose) {
                    previous = entry;
                }
            }
        }
        entry++;
    }

    if (arg0->state != 4) {
        previous = 0;
    } else if (matches <= 1) {
        previous = 0;
    } else if (matches == 2 && list->flag == 0) {
        previous = 0;
    } else if (fn_12_2D73C(arg0, 15) == 0) {
        previous = (MovieEntry *)1;
    } else if (fn_12_2DEB0(arg0, previous->value, previous->value2) != 0) {
        previous = (MovieEntry *)1;
    } else {
        previous = 0;
    }
    fn_12_24950(local);
    return (int)previous;
}
