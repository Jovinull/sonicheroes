#ifndef __PPC_EABI_LINKER_H
#define __PPC_EABI_LINKER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

DECL_SECT(".init") extern char _stack_addr[];
DECL_SECT(".init") extern char _stack_end[];
DECL_SECT(".init") extern char _SDA_BASE_[];
DECL_SECT(".init") extern char _SDA2_BASE_[];

typedef struct __rom_copy_info {
	char* rom;
	char* addr;
	u32 size;
} __rom_copy_info;

DECL_SECT(".init") extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
	char* addr;
	u32 size;
} __bss_init_info;

DECL_SECT(".init") extern __bss_init_info _bss_init_info[];

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
