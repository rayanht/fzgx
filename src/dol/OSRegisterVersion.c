#include <dolphin/os.h>
#pragma peephole off

void OSReport(const char *msg, ...);

void OSRegisterVersion(const char *id) { OSReport("%s\n", id); }
