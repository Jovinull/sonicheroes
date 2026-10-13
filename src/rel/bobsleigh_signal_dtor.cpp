#include "types.h"

// TObjBobsleighSignal's destructor (the PS2 build's TObjBobsleighSignal::__dt):
// it frees the signal's model, runs the collision and object bases down and
// frees the object when the delete flag asks for it.

typedef struct RpClump RpClump;

typedef struct BobsleighSignal {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
	u8 colli[0xB0]; // 0x28, C_COLLI
	RpClump* clump; // 0xD8
} BobsleighSignal;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__19TObjBobsleighSignal[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" BobsleighSignal* __dt__19TObjBobsleighSignalFv(BobsleighSignal* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = __vt__19TObjBobsleighSignal;
		fn_80150958(object->clump);
		object->clump = NULL;

		__dt__7C_COLLIFv(object->colli, 0);
		__dt__7TObjectFv(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
