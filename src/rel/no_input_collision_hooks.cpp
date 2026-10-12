#include "types.h"

// The unload and load hooks and the factory rel/no_input_collision_register.cpp
// puts in the no-input collision's editor record. The empty hooks have nothing
// to do: the object loads nothing. The factory allocates 0xEC bytes and hands
// them to the module's constructor (left as assembly and named
// noInputCollisionObjectCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* noInputCollisionObjectCtor(void* object, void* owner);

extern "C" void noInputCollisionObjectUnload(void) { }

extern "C" void noInputCollisionObjectLoad(void) { }

extern "C" void noInputCollisionObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xEC);

	if (memory != NULL) {
		noInputCollisionObjectCtor(memory, lbl_8042C110);
	}
}
