// Forwards its argument to the function pointer at +0x68 of the engine's current world. The
// callee's role is UNKNOWN.
#include "game/rw_engine.h"

struct World80158928 {
	u8 pad0[0x68];
	void (*f68)(void* arg); // 0x68
};

extern "C" {
void fn_80158928(void* arg)
{
	((World80158928*)lbl_8042C9A4->curWorld)->f68(arg);
}
}
