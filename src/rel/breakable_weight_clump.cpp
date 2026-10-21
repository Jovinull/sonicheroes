#include "types.h"

// The breakable weight's DestroyClump and CloneClump (the PS2 build's
// TObjWeightExt names; breakableWeightDestroyClump and breakableWeightCloneClump
// here): unlike the weight's (rel/weight_clump.cpp), the model is only
// destroyed or cloned, without the world's object scene.

typedef struct RpClump RpClump;

typedef struct BreakableWeight {
	u8 unk00[0xF4]; // 0x00
	RpClump* model; // 0xF4
} BreakableWeight;

extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" void breakableWeightDestroyClump(BreakableWeight* object)
{
	if (object->model != NULL) {
		fn_80150958(object->model);
		object->model = NULL;
	}
}

extern "C" void breakableWeightCloneClump(BreakableWeight* object, RpClump* source)
{
	object->model = fn_80150588(source);
}
