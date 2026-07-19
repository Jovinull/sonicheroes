#ifndef GLOBAL_DESTRUCTOR_CHAIN_H
#define GLOBAL_DESTRUCTOR_CHAIN_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DestructorChain {
	struct DestructorChain* next;
	void* destructor;
	void* object;
} DestructorChain;

// Metrowerks calls a complete-object destructor with -1 as the second argument.
#define DTORCALL_COMPLETE(dtor, obj) (*(void (*)(void*, int))(dtor))((obj), -1)

extern DestructorChain* __global_destructor_chain;

extern void __destroy_global_chain(void);
extern void* __register_global_object(void* object, void* destructor, void* regmem);

#ifdef __cplusplus
}
#endif

#endif
