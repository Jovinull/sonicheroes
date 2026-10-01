#ifndef MSL_C_STRING_H
#define MSL_C_STRING_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void* memset(void* destination, s32 value, u32 size);
void* memcpy(void* destination, const void* source, u32 size);
s32 strncmp(const char* lhs, const char* rhs, u32 count);
char* strncpy(char* destination, const char* source, u32 size);

#ifdef __cplusplus
}
#endif

#endif
