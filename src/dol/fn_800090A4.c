#include "types.h"

#define ALIGNMENT 32
#define MINOBJSIZE 64

#define InRange(cell, arenaStart, arenaEnd) ((u32)arenaStart <= (u32)cell) && ((u32)cell < (u32)arenaEnd)
#define OFFSET(n, a) (((u32)(n)) & ((a) - 1))

typedef struct Cell {
    struct Cell *prev;
    struct Cell *next;
    u32 size;
    u8 pad_C[0x14];
} Cell;

typedef struct HeapDesc {
    long size;
    Cell *free;
    Cell *allocated;
} HeapDesc;

extern HeapDesc *lbl_801A6744; /* HeapArray */
extern int lbl_801A6740;       /* NumHeaps */
extern void *lbl_801A673C;     /* ArenaStart */
extern void *lbl_801A6738;     /* ArenaEnd */
extern void OSReport(const char *msg, ...);
extern void fn_8000951C(int heap);
extern void fn_800095A4(void);

#define HeapArray lbl_801A6744
#define NumHeaps lbl_801A6740
#define ArenaStart lbl_801A673C
#define ArenaEnd lbl_801A6738

#define CHECK(line, condition)                                          \
    if (!(condition)) {                                                 \
        OSReport("OSCheckHeap: Failed " #condition " in %d", line);     \
        fn_800095A4();                                                  \
        return -1;                                                      \
    }

long fn_800090A4(int heap) {
    HeapDesc *hd;
    Cell *cell;
    long atotal = 0;
    long ftotal = 0;
    long free = 0;
    long total;

    fn_8000951C(heap);
    CHECK(0x350, HeapArray);
    CHECK(0x351, 0 <= heap && heap < NumHeaps);

    hd = &HeapArray[heap];
    CHECK(0x354, 0 <= hd->size);

    CHECK(0x356, hd->allocated == NULL || hd->allocated->prev == NULL);

    for (cell = hd->allocated; cell; cell = cell->next) {
        CHECK(0x359, InRange(cell, ArenaStart, ArenaEnd));
        CHECK(0x35A, OFFSET(cell, ALIGNMENT) == 0);
        CHECK(0x35B, cell->next == NULL || cell->next->prev == cell);
        CHECK(0x35C, MINOBJSIZE <= cell->size);
        CHECK(0x35D, OFFSET(cell->size, ALIGNMENT) == 0);

        atotal += cell->size;
        CHECK(0x360, 0 < atotal && atotal <= hd->size);
    }

    CHECK(0x368, hd->free == NULL || hd->free->prev == NULL);

    for (cell = hd->free; cell; cell = cell->next) {
        CHECK(0x36B, InRange(cell, ArenaStart, ArenaEnd));
        CHECK(0x36C, OFFSET(cell, ALIGNMENT) == 0);
        CHECK(0x36D, cell->next == NULL || cell->next->prev == cell);
        CHECK(0x36E, MINOBJSIZE <= cell->size);
        CHECK(0x36F, OFFSET(cell->size, ALIGNMENT) == 0);
        CHECK(0x370, cell->next == NULL || (char*) cell + cell->size < (char*) cell->next);

        ftotal += cell->size;
        free += cell->size - sizeof(Cell);
        CHECK(0x374, 0 < ftotal && ftotal <= hd->size);
    }

    total = ftotal + atotal;
    CHECK(0x37C, total == hd->size);

    fn_800095A4();
    return free;
}
