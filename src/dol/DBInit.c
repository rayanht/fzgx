#include "types.h"

extern u32 __DBInterface;
extern u32 DBVerbose;
extern void __DBExceptionDestination(void);
void DBInit(void) {
    u32 *base;
    u32 t0;

    // fzgx-allow: A1 DB hardware register
    base = (u32 *)0x80000000;  /* fzgx-allow: A2 unnamed OS/hardware memory */
    t0 = (u32)base + 0x40;
    __DBInterface = t0;
    // fzgx-allow: A1 DB hardware register
    base[0x12] = (u32)__DBExceptionDestination + (u32)base;
    DBVerbose = 1;
}
