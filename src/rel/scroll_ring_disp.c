#include "types.h"

// TObjScrollRing's two display hooks. Both do the same thing: hand the work to
// whatever the object's second vtable points at.
//
// The claim is .text 0x8F98 to 0x8FF0 and nothing else. Neither reads a
// constant or a table, so there is no data to take.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// They are written PDisp first because that is the order they sit in: the
// vtable puts TDisp in slot five and PDisp in slot six, but PDisp is the lower
// address.
//
// The call has to be a real virtual call rather than an index into a function
// pointer array. Both compile to the same four instructions, but a virtual call
// puts the table pointer straight into r12, which is what the original does; an
// array read parks it in an argument register first. Getting the pointer to sit
// at 0xD8 is what the padding base is for: the compiler places the vtable
// pointer after a non polymorphic base's data, the same way TObject's lands at
// 0x18.

struct ScrollRingData {
	u8 unk0[0xD8]; // 0x00
};

struct ScrollRing : public ScrollRingData {
	virtual void draw(); // vtable pointer at 0xD8
};

extern "C" void scrollRingPDisp(ScrollRing* object)
{
	object->draw();
}

extern "C" void scrollRingTDisp(ScrollRing* object)
{
	object->draw();
}
