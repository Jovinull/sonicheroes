#include "types.h"

// The reset hook of the triple spring, installed by rel/tri_spring_assets.cpp.
// The claim is .text 0x2C9C to 0x2CD0, the same in all thirteen stage modules
// that share the engine core.
//
// The object may not have its per instance state block yet, so the clear is
// guarded. Only the first byte is cleared: the rest of the block is rebuilt on
// the next load, and this is the flag that says it has to be.

typedef struct TriSpring {
	u8 unk0[0x30]; // 0x00
	void* state;   // 0x30
} TriSpring;

extern "C" void* memset(void* dst, s32 value, u32 size);

extern "C" void triSpringReset(TriSpring* object)
{
	void* state = object->state;

	if (state != NULL) {
		memset(state, 0, 1);
	}
}
