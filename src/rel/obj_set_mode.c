#include "types.h"

// The mode setter every stage object carries: record the mode and reconfigure
// the two draw handles to match it.
//
// The claim is .text 0x3170 to 0x321C and nothing else. It reads no constant
// and no table of its own, which is what makes the single function cuttable
// without taking any data with it.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// Both branches assign through a call, and the call has to come first: written
// as one statement the compiler evaluates the value before it, which costs a
// callee saved register the original does not spend.
//
// The three predicates just before this, at 0x2FD0, 0x3064 and 0x30F8, are the
// same size and shape but are still assembly. They walk one group's object list
// and differ only in what they demand of each entry's target. Everything about
// them reproduces except which register the walk runs on: the original keeps
// the node in r4 and the kind in r3, and every spelling tried puts the node in
// r3. Reading the list through an inlined helper does produce the copy the
// original makes from the temporary into the walk variable, but not that
// assignment.

typedef struct Handle {
	u8 unk0[0x18]; // 0x00
	u32 flags;     // 0x18
} Handle;

typedef struct Object {
	u8 unk0[0x28];  // 0x00
	Handle* handle; // 0x28
	u8 unk2C[0x90]; // 0x2C
	s32 mode;       // 0xBC
	u8 unkC0[0x30]; // 0xC0
	void* drawA;    // 0xF0
	u8 unkF4[0x4];  // 0xF4
	void* drawB;    // 0xF8
} Object;

extern "C" s32* fn_8005F490(void* draw);

extern "C" void objSetMode(Object* object, s32 mode)
{
	s32* slot;

	object->mode = mode;

	switch (object->mode) {
		case 0:
			slot  = fn_8005F490(object->drawA);
			*slot = ((object->handle->flags & 0x1C0000) >> 18) + 4;
			slot  = fn_8005F490(object->drawB);
			*slot = ((object->handle->flags & 0x1C0000) >> 18) + 4;
			break;
		case 1:
		case 2:
			slot  = fn_8005F490(object->drawA);
			*slot = 0x10;
			slot  = fn_8005F490(object->drawB);
			*slot = 0x10;
			break;
	}
}
