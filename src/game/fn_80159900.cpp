#include "types.h"

// Stores a callback at offset 0x68, using fn_801591D8 when the argument is null.
extern "C" {
struct Obj80159900 {
	u8 pad[0x68];
	void (*callback)();
};
void fn_801591D8();

void fn_80159900(Obj80159900* object, void (*callback)())
{
	if (callback == NULL) {
		callback = fn_801591D8;
	}
	object->callback = callback;
}
}
