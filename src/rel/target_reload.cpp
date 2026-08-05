#include "types.h"

// TObjTarget's model reload. It drops whatever model the object is holding and
// builds a fresh one from the stage's target resource.
//
// The claim is .text 0x00023BD4 to 0x00023C28 and nothing else. It reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where targetDtor
// begins, and it touches the same model field at +0xEC that the destructor
// clears.
//
// The run is the same in the twelve stage modules that carry it, checked by
// normalising the disassembly and comparing across modules.

typedef struct Target {
	u8 unk0[0xEC]; // 0x00
	void* model;   // 0xEC
} Target;          // 0xF0

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* targetResource;

extern "C" void fn_80150958(void* model);
extern "C" void* fn_80150588(void* source);

extern "C" void targetReloadModel(Target* object)
{
	if (object->model != NULL) {
		fn_80150958(object->model);
		object->model = NULL;
	}

	object->model = fn_80150588(targetResource);
}
