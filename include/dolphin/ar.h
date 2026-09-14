#ifndef DOLPHIN_AR_H
#define DOLPHIN_AR_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

u32 ARAlloc(u32 size);
u32 ARFree(u32* size);

#ifdef __cplusplus
}
#endif

#endif
