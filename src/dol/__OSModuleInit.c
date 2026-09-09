#include <dolphin/os.h>
#include <dolphin/os/OSModule.h>
#include "sdk_addresses.h"

OSModuleQueue __OSModuleInfoList : FZGX_ADDR___OSModuleInfoList;

const void *__OSStringTable : FZGX_ADDR___OSStringTable;

void __OSModuleInit(void) {
    __OSModuleInfoList.head = __OSModuleInfoList.tail = 0;
    __OSStringTable = 0;
}
