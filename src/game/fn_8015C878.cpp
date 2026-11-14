// Replaces the shared block referenced from the plugin slot of object (at the offset lbl_8042C930):
// drops one reference to the old block (freeing it with the engine memory function on the last
// one, as fn_8015C834 does), stores the new block and takes a reference to it. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Shared8015C878 {
	u8 pad0[0x16];
	u16 refCount; // 0x16
};

static inline void SharedRelease(Shared8015C878* shared)
{
	if (shared->refCount == 1) {
		lbl_8042C9A4->rwfree(shared);
	} else {
		shared->refCount--;
	}
}

extern "C" {
extern s32 lbl_8042C930;

void fn_8015C878(void* object, Shared8015C878* shared)
{
	s32 offset = lbl_8042C930;
	if (*(Shared8015C878**)((u8*)object + offset) != 0) {
		SharedRelease(*(Shared8015C878**)((u8*)object + offset));
	}
	*(Shared8015C878**)((u8*)object + offset) = shared;
	(*(Shared8015C878**)((u8*)object + offset))->refCount++;
}
}
