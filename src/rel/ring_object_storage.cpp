#include "types.h"

// TObjSetRing::GetStragePointer (the PS2 build's name, by its place in the PS2
// order; ringObjectGetStragePointer here): the storage of the rings' taken
// flags, kept with the set object's placement.

typedef struct SetRingFrame {
	u8 unk00[0x30];
	void* storage; // 0x30
} SetRingFrame;

typedef struct SetRing {
	u8 unk00[0x50];
	SetRingFrame* frame; // 0x50, the set object's
} SetRing;

extern "C" void* ringObjectGetStragePointer(SetRing* object)
{
	return object->frame->storage;
}
