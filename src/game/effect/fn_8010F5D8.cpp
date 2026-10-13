#include "types.h"

// Flags the effect's child (bit 0x10 of its flags at 0x4), when it has one,
// and clears the effect's word at 0x1A8.

struct Fn8010F5D8Child {
	u8 unk0[0x4];
	s32 flags; // 0x4
};

struct Fn8010F5D8Effect {
	u8 unk000[0x70];
	Fn8010F5D8Child* child; // 0x070
	u8 unk074[0x134];
	s32 value; // 0x1A8
};

extern "C" void fn_8010F5D8(Fn8010F5D8Effect* effect)
{
	Fn8010F5D8Child* child = effect->child;
	if (child != NULL) {
		child->flags |= 0x10;
	}
	effect->value = 0;
}
