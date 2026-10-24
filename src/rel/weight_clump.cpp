#include "types.h"

// TObjWeight's DestroyClump and CloneClump (the PS2 build's names;
// weightDestroyClump and weightCloneClump here): the weight's model leaves the
// world's object scene and is destroyed, or is cloned from the shared model and
// added to the scene.

typedef struct RpClump RpClump;

typedef struct Weight {
	u8 unk00[0xD8]; // 0x00
	RpClump* model; // 0xD8
} Weight;

extern "C" u8* lbl_8042C1D0;

extern "C" void fn_8015BBF8(void* scene, RpClump* clump);
extern "C" void fn_8015BB08(void* scene, RpClump* clump);
extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" void weightDestroyClump(Weight* object)
{
	if (object->model != NULL) {
		fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x725C), object->model);
		fn_80150958(object->model);
		object->model = NULL;
	}
}

extern "C" void weightCloneClump(Weight* object, RpClump* source)
{
	object->model = fn_80150588(source);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), object->model);
}
