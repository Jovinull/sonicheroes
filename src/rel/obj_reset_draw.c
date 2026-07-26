#include "types.h"

// Puts an object's draw handle back to mode 0x10, the same value objSetMode
// writes for modes one and two.
//
// The claim is .text 0x4398 to 0x43D8 and nothing else. It reads no constant
// and no table, so there is no data to take.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.

typedef struct Object {
	u8 unk0[0xF4]; // 0x00
	void* draw;    // 0xF4
} Object;

extern "C" void fn_8005F670(void* draw);
extern "C" s32* fn_8005F490(void* draw);

extern "C" void objResetDraw(Object* object)
{
	s32* slot;

	fn_8005F670(object->draw);

	slot  = fn_8005F490(object->draw);
	*slot = 0x10;
}
