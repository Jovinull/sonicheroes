#ifndef MSL_C_STDIO_H
#define MSL_C_STDIO_H

#include "Runtime.PPCEABI.H/__va_arg.h"

#ifdef __cplusplus
extern "C" {
#endif

s32 vsprintf(char* destination, const char* format, __va_list arguments);

#ifdef __cplusplus
}
#endif

#endif
