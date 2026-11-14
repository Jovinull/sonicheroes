// Destructor of the 0x12F atomic plugin registered by fn_801FC470 through fn_801520D0
// (HYPOTHESIS: RpAtomicRegisterPlugin): when the atomic carries plugin data, releases the
// reference held in the slot reached through its object at 0x18 (fn_8015498C with null), frees
// the data's buffer and the data itself, and clears the plugin pointer. Returns the atomic.
// Field names are inferred from this function only.
#include "game/rw_engine.h"

struct Ref801FC3D8;

struct Holder801FC3D8 {
	Ref801FC3D8** slot; // 0x0
};

struct Object801FC3D8 {
	u8 pad0[0x20];
	Holder801FC3D8* holder; // 0x20
};

struct Atomic801FC3D8 {
	u8 pad0[0x18];
	Object801FC3D8* object; // 0x18
};

// Plugin data allocated by the plugin (only the buffer field is known).
struct Data801FC3D8 {
	u8 pad0[0xC];
	void* buffer; // 0xC
};

extern "C" {
// Offset of the plugin data inside an atomic (fn_801520D0 result).
extern s32 lbl_8042CF48;

Ref801FC3D8** fn_8015498C(Ref801FC3D8** slot, Ref801FC3D8* ref);

#define PLUGIN_DATA(atomic) (*(Data801FC3D8**)((u8*)(atomic) + lbl_8042CF48))

Atomic801FC3D8* fn_801FC3D8(Atomic801FC3D8* atomic, s32, s32)
{
	if (PLUGIN_DATA(atomic)) {
		fn_8015498C(atomic->object->holder->slot, 0);
		if (PLUGIN_DATA(atomic)->buffer) {
			lbl_8042C9A4->rwfree(PLUGIN_DATA(atomic)->buffer);
		}
		lbl_8042C9A4->rwfree(PLUGIN_DATA(atomic));
		PLUGIN_DATA(atomic) = 0;
	}
	return atomic;
}
}
