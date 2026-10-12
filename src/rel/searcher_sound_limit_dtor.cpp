#include "types.h"

// TObjEnemySearcherSoundLimit's destructor (searcherSoundLimitDtor here): it
// restores the vtable, clears the instance pointer the constructor set, runs the
// object base down and frees the object when the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct SearcherSoundLimit {
	TObject base; // 0x00
} SearcherSoundLimit;

extern "C" void* lbl_8042C148;
extern "C" void* searcherSoundLimitVtable[];
extern "C" void* searcherSoundLimitInstance;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" SearcherSoundLimit* searcherSoundLimitDtor(SearcherSoundLimit* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = searcherSoundLimitVtable;

		searcherSoundLimitInstance = NULL;
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
