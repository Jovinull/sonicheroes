#include "types.h"

// The bobsleigh collision object's reset hook (s08bobColliObjectReset here),
// installed by rel/s08bob_colli_object_register.cpp: like triSpringReset
// (rel/tri_spring_reset.cpp), it clears the object's per instance state block
// when it has one, here its first word.

typedef struct S08bobColliObject {
	u8 unk0[0x30]; // 0x00
	void* state;   // 0x30
} S08bobColliObject;

extern "C" void* memset(void* dst, s32 value, u32 size);

extern "C" void s08bobColliObjectReset(S08bobColliObject* object)
{
	void* state = object->state;

	if (state != NULL) {
		memset(state, 0, 4);
	}
}
