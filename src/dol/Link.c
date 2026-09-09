#include <dolphin/os.h>
#include <dolphin/os/OSModule.h>
#include "sdk_addresses.h"

void *__OSStringTable : FZGX_ADDR___OSStringTable;

void *memset(void *dest, int val, size_t count);

OSModuleQueue __OSModuleInfoList : FZGX_ADDR___OSModuleInfoList;

void fn_8000DD60(OSModuleInfo *module);

BOOL Relocate(OSModuleHeader *newModule, OSModuleHeader *module);

BOOL Link(OSModuleInfo *newModule, void *bss, BOOL fixed) {
    u32 i;
    OSSectionInfo *si;
    OSModuleHeader *moduleHeader;
    OSModuleInfo *moduleInfo;
    OSImportInfo *imp;
    moduleHeader = (OSModuleHeader *)newModule;
    moduleHeader->bssSection = 0;
    if (3 < newModule->version ||
        2 <= newModule->version &&
            (moduleHeader->align && (u32)newModule % moduleHeader->align != 0 ||
             moduleHeader->bssAlign && (u32)bss % moduleHeader->bssAlign != 0)) {
        return 0;
    }
    do {
        OSModuleInfo *__prev;
        __prev = (&__OSModuleInfoList)->tail;
        if (__prev == ((void *)0))
            (&__OSModuleInfoList)->head = (newModule);
        else
            __prev->link.next = (newModule);
        (newModule)->link.prev = __prev;
        (newModule)->link.next = ((void *)0);
        (&__OSModuleInfoList)->tail = (newModule);
    } while (0);
    newModule->sectionInfoOffset += (u32)moduleHeader;
    moduleHeader->relOffset += (u32)moduleHeader;
    moduleHeader->impOffset += (u32)moduleHeader;
    if (3 <= newModule->version) {
        moduleHeader->fixSize += (u32)moduleHeader;
    }
    for (i = 1; i < newModule->numSections; i++) {
        si = &((OSSectionInfo *)(((OSModuleInfo *)(newModule))->sectionInfoOffset))[i];
        if (si->offset != 0) {
            si->offset += (u32)moduleHeader;
        } else if (si->size != 0) {
            moduleHeader->bssSection = (u8)i;
            si->offset = (u32)bss;
        }
    }
    for (imp = (OSImportInfo *)moduleHeader->impOffset;
         imp < (OSImportInfo *)(moduleHeader->impOffset + moduleHeader->impSize); imp++) {
        imp->offset += (u32)moduleHeader;
    }
    if (moduleHeader->prologSection != 0) {
        moduleHeader->prolog +=
            ((((OSSectionInfo *)(((OSModuleInfo *)(newModule))
                                     ->sectionInfoOffset))[moduleHeader->prologSection]
                  .offset) &
             ~0x1);
    }
    if (moduleHeader->epilogSection != 0) {
        moduleHeader->epilog +=
            ((((OSSectionInfo *)(((OSModuleInfo *)(newModule))
                                     ->sectionInfoOffset))[moduleHeader->epilogSection]
                  .offset) &
             ~0x1);
    }
    if (moduleHeader->unresolvedSection != 0) {
        moduleHeader->unresolved +=
            ((((OSSectionInfo *)(((OSModuleInfo *)(newModule))
                                     ->sectionInfoOffset))[moduleHeader->unresolvedSection]
                  .offset) &
             ~0x1);
    }
    if (__OSStringTable) {
        newModule->nameOffset += (u32)__OSStringTable;
    }
    Relocate(0, moduleHeader);
    for (moduleInfo = __OSModuleInfoList.head; moduleInfo; moduleInfo = moduleInfo->link.next) {
        Relocate(moduleHeader, (OSModuleHeader *)moduleInfo);
        if (moduleInfo != newModule) {
            Relocate((OSModuleHeader *)moduleInfo, moduleHeader);
        }
    }
    if (fixed) {
        for (imp = (OSImportInfo *)moduleHeader->impOffset;
             imp < (OSImportInfo *)(moduleHeader->impOffset + moduleHeader->impSize); imp++) {
            if (imp->id == 0 || imp->id == newModule->id) {
                moduleHeader->impSize = (u32)((u8 *)imp - (u8 *)moduleHeader->impOffset);
                break;
            }
        }
    }
    memset(bss, 0, moduleHeader->bssSize);
    fn_8000DD60(newModule);
    return 1;
}
