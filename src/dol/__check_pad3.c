#include "types.h"

extern void OSResetSystem(int, u32, int);

__declspec(section ".init") void __check_pad3(void) {
    if ((*(volatile u16 *)0x800030E4 & 0xEEF) == 0xEEF) {  /* fzgx-allow: A1,A2 unnamed OS memory */
        OSResetSystem(0, 0, 0);
    }
}
