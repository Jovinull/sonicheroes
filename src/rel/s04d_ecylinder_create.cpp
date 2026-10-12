#include "types.h"

// The factory rel/s04d_e_cylinder_register.cpp puts in the s04dECylinder's
// editor record. The factory allocates 0xFC bytes and hands them to the
// module's constructor (left as assembly and named s04dECylinderCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04dECylinderCtor(void* object, void* owner);

extern "C" void s04dECylinderCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		s04dECylinderCtor(memory, lbl_8042C110);
	}
}
