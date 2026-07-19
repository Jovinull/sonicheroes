#ifndef __VA_ARG_H
#define __VA_ARG_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __va_list_struct {
	char gpr;
	char fpr;
	char reserved[2];
	char* input_arg_area;
	char* reg_save_area;
} _va_list_struct;

typedef _va_list_struct __va_list[1];

void* __va_arg(_va_list_struct* list, int type);

#ifdef __cplusplus
}
#endif

#endif
