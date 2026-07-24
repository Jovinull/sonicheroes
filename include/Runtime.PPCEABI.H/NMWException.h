#ifndef NMWEXCEPTION_H
#define NMWEXCEPTION_H

#include "types.h"
#include "Runtime.PPCEABI.H/__ppc_eabi_linker.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void __destroy_global_chain(void);

typedef s16 vbase_ctor_arg_type;
typedef char local_cond_type;

typedef struct CatchInfo {
	void* location;
	void* typeinfo;
	void* dtor;
	void* sublocation;
	s32 pointercopy;
	void* stacktop;
} CatchInfo;

extern char __throw_catch_compare(
    const char* throwtype, const char* catchtype, long* offset_result);
extern int __register_fragment(struct __eti_init_info* info, char* TOC);
extern void __unregister_fragment(int fragmentID);

#ifdef __cplusplus
}
#endif

#endif
