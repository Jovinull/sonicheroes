#include "types.h"

// ENEMY_MGUN's destructor (the PS2 build's ENEMY_MGUN::__dt): it restores the
// vtable, frees the flash model, destroys the collision and the object base,
// and frees the object when the delete flag asks for it.

#include "src/rel/enemy_mgun.inc"

extern "C" void* lbl_8042C148;
extern "C" void* __vt__10ENEMY_MGUN[];

extern "C" void fn_80150958(struct RpClump* clump);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" ENEMY_MGUN* __dt__10ENEMY_MGUNFv(ENEMY_MGUN* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = __vt__10ENEMY_MGUN;
		if (object->clump != NULL) {
			fn_80150958(object->clump);
			object->clump = NULL;
		}
		__dt__7C_COLLIFv(object->colli, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
