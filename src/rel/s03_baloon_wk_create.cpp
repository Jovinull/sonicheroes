#include "types.h"

// The factory rel/s03_baloon_wk_register.cpp puts in the s03BaloonWK's editor
// record. The factory allocates 0xC4 bytes and hands them to the module's
// constructor (left as assembly and named s03BaloonWKCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03BaloonWKCtor(void* object, void* owner);

extern "C" void s03BaloonWKCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xC4);

	if (memory != NULL) {
		s03BaloonWKCtor(memory, lbl_8042C110);
	}
}
