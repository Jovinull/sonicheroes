#ifndef MSL_C_STRING_H
#define MSL_C_STRING_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void* memset(void* destination, s32 value, u32 size);
char* strncpy(char* destination, const char* source, u32 size);

#ifdef __cplusplus
}
#endif

#endif
