// Drops one reference to an object counted by the halfword at +0x16: the last reference frees it
// with the engine memory function. The object's type is UNKNOWN.
#include "game/rw_engine.h"

struct Object8015C834 {
	u8 pad0[0x16];
	u16 refCount; // 0x16
};

extern "C" {
void fn_8015C834(Object8015C834* object)
{
	if (object->refCount == 1) {
		lbl_8042C9A4->rwfree(object);
	} else {
		object->refCount--;
	}
}
}
