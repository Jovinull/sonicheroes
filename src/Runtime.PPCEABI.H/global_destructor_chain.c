#include "Runtime.PPCEABI.H/global_destructor_chain.h"

DestructorChain* __global_destructor_chain;

// Defined before __register_global_object because this compiler emits functions
// in source order and the original places it first.
void __destroy_global_chain(void)
{
	DestructorChain* iter;

	while ((iter = __global_destructor_chain) != 0) {
		__global_destructor_chain = iter->next;
		DTORCALL_COMPLETE(iter->destructor, iter->object);
	}
}

void* __register_global_object(void* object, void* destructor, void* regmem)
{
	((DestructorChain*)regmem)->next       = __global_destructor_chain;
	((DestructorChain*)regmem)->destructor = destructor;
	((DestructorChain*)regmem)->object     = object;
	__global_destructor_chain              = (DestructorChain*)regmem;

	return object;
}

DECL_SECT(".dtors") static void* const __destroy_global_chain_reference = __destroy_global_chain;
