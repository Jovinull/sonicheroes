#include "types.h"

// The factory the SCROLL RING OBJECT class registration installs in its create
// slot. The claim is .text 0x8D68 to 0x8DB0, the same in all thirteen stage
// modules that share the engine core.
//
// It takes 0xF8 bytes from the object heap and hands them to the constructor
// along with the current owner. The allocator can fail, and the original checks
// for it rather than trusting the result.

extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C110;

extern "C" void* fn_80018A34(void* heap, s32 size);
extern "C" void scrollRingCtor(void* object, void* owner);

extern "C" void scrollRingCreate(void)
{
	void* object = fn_80018A34(lbl_8042C148, 0xF8);

	if (object != NULL) {
		scrollRingCtor(object, lbl_8042C110);
	}
}
