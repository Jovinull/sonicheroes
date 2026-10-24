#include "types.h"

// The factory rel/traintrain_register.cpp puts in the traintrain's editor record. The factory allocates 0x918 bytes and hands them to the module's constructor (left as assembly and named traintrainCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* traintrainCtor(void* object, void* owner);

extern "C" void traintrainCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x918);

	if (memory != NULL) {
		traintrainCtor(memory, lbl_8042C110);
	}
}
