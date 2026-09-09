#ifndef DOLPHIN_OS_OSMODULE_H
#define DOLPHIN_OS_OSMODULE_H
#include <dolphin/types.h>

typedef struct OSModuleHeader OSModuleHeader;

typedef u32 OSModuleID;

typedef struct OSModuleLink OSModuleLink;

typedef struct OSModuleInfo OSModuleInfo;

typedef struct OSSectionInfo OSSectionInfo;

typedef struct OSImportInfo OSImportInfo;

typedef struct OSRel OSRel;

struct OSModuleLink {
    OSModuleInfo *next;
    OSModuleInfo *prev;
};

struct OSModuleInfo {
    OSModuleID id;
    OSModuleLink link;
    u32 numSections;
    u32 sectionInfoOffset;
    u32 nameOffset;
    u32 nameSize;
    u32 version;
};

struct OSModuleHeader {
    OSModuleInfo info;
    u32 bssSize;
    u32 relOffset;
    u32 impOffset;
    u32 impSize;
    u8 prologSection;
    u8 epilogSection;
    u8 unresolvedSection;
    u8 bssSection;
    u32 prolog;
    u32 epilog;
    u32 unresolved;
    u32 align;
    u32 bssAlign;
    u32 fixSize;
};

struct OSSectionInfo {
    u32 offset;
    u32 size;
};

struct OSImportInfo {
    OSModuleID id;
    u32 offset;
};

struct OSRel {
    u16 offset;
    u8 type;
    u8 section;
    u32 addend;
};

typedef struct OSModuleQueue OSModuleQueue;

struct OSModuleQueue {
    OSModuleInfo *head;
    OSModuleInfo *tail;
};
#endif
