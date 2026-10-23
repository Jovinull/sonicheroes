#include "types.h"

// TObjTarget::DestroyClump (the PS2 build's name, by its place in the PS2
// order; targetDestroyClump here): the target's model is released.

typedef struct RpClump RpClump;

typedef struct Target {
	u8 unk00[0xEC];
	RpClump* model; // 0xEC
} Target;

extern "C" void fn_80150958(RpClump* clump);

extern "C" void targetDestroyClump(Target* object)
{
	if (object->model != NULL) {
		fn_80150958(object->model);
		object->model = NULL;
	}
}
