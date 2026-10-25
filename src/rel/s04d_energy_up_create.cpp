#include "types.h"

// The factory rel/s04d_energy_up_register.cpp puts in the energy up's editor
// record. The factory allocates 0xFC bytes and hands them to the module's
// constructor (left as assembly and named s04dEnergyUpCtor here) with 1 and
// the task at lbl_8042C110 as its owner.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04dEnergyUpCtor(void* object, s32 kind, void* owner);

extern "C" void s04dEnergyUpCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		s04dEnergyUpCtor(memory, 1, lbl_8042C110);
	}
}
