#include "Runtime.PPCEABI.H/NMWException.h"
#include "Runtime.PPCEABI.H/__ppc_eabi_linker.h"

static int fragmentID = -2;

// clang-format off
ASM static char* GetR2()
{
#ifdef __MWERKS__
	nofralloc
	mr r3, r2
	blr
#endif
}
// clang-format on

extern "C" {

// __fini_cpp_exceptions is defined first because this compiler emits functions
// in source order, and the original places it before __init_cpp_exceptions.
void __fini_cpp_exceptions()
{
	if ((s32)fragmentID != -2) {
		__unregister_fragment(fragmentID);
		fragmentID = -2;
	}
}

void __init_cpp_exceptions()
{
	if ((s32)fragmentID == -2) {
		char* R2   = GetR2();
		fragmentID = __register_fragment(_eti_init_info, R2);
	}
}
}

DECL_SECT(".ctors") extern void* const __init_cpp_exceptions_reference  = __init_cpp_exceptions;
DECL_SECT(".dtors") extern void* const __destroy_global_chain_reference = __destroy_global_chain;
DECL_SECT(".dtors") extern void* const __fini_cpp_exceptions_reference  = __fini_cpp_exceptions;
