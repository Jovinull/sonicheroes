// Destructor of the 0x12F atomic plugin registered by fn_801FC470 through fn_801520D0
// (HYPOTHESIS: RpAtomicRegisterPlugin): when the atomic carries plugin data, releases the
// reference held in the slot reached through its object at 0x18 (fn_8015498C with null), frees
// the data's buffer and the data itself, and clears the plugin pointer. Returns the atomic.
#include "game/atomic_plugin_12f.h"
#include "game/rw_engine.h"

extern "C" {
Atomic12FRef** fn_8015498C(Atomic12FRef** slot, Atomic12FRef* ref);

Atomic12F* fn_801FC3D8(Atomic12F* atomic, s32, s32)
{
	if (ATOMIC_12F_DATA(atomic)) {
		fn_8015498C(atomic->object->holder->slot, 0);
		if (ATOMIC_12F_DATA(atomic)->buffer) {
			lbl_8042C9A4->rwfree(ATOMIC_12F_DATA(atomic)->buffer);
		}
		lbl_8042C9A4->rwfree(ATOMIC_12F_DATA(atomic));
		ATOMIC_12F_DATA(atomic) = 0;
	}
	return atomic;
}
}
