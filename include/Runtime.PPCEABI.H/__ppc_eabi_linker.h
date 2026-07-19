#ifndef __PPC_EABI_LINKER_H
#define __PPC_EABI_LINKER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __eti_init_info {
	void* eti_start;
	void* eti_end;
	void* code_start;
	u32 code_size;
} __eti_init_info;

DECL_SECT(".init") extern __eti_init_info _eti_init_info[];

#ifdef __cplusplus
}
#endif

#endif
