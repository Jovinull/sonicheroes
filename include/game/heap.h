#ifndef GAME_HEAP_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

void* MAlloc_BW(u32 size);
void Free_BW(void* ptr);

#ifdef __cplusplus
};
#endif


#endif
