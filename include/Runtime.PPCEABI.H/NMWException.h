#ifndef NMWEXCEPTION_H
#define NMWEXCEPTION_H

#include "types.h"
#include "Runtime.PPCEABI.H/__ppc_eabi_linker.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void __destroy_global_chain(void);

extern int __register_fragment(struct __eti_init_info* info, char* TOC);
extern void __unregister_fragment(int fragmentID);

#ifdef __cplusplus
}
#endif

#endif
