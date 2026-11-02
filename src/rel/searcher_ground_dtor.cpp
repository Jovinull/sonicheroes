#include "types.h"

// The destructor of the object each searcher builds into its +0x2F0 field (a
// TObject that moves on the ground and carries a collision volume at 0x60;
// searcherGroundDtor here), the same in the thirteen stage modules that share
// the engine core: it restores the vtable, destroys the collision volume and
// the object base, and frees the object when the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct SearcherGround {
	TObject base;          // 0x00
	u8 moveOnGround[0x38]; // 0x28
	u8 volume[0x4];        // 0x60
} SearcherGround;

extern "C" void* lbl_8042C148;
extern "C" void* searcherGroundVtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* volume, s32 flags);

extern "C" SearcherGround* searcherGroundDtor(SearcherGround* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = searcherGroundVtable;

		__dt__7C_COLLIFv(object->volume, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
