#ifndef DOLPHIN_OS_OSCACHE_H
#define DOLPHIN_OS_OSCACHE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void DCFlushRange(void* address, u32 size);

#ifdef __cplusplus
}
#endif

#endif
