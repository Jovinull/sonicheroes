#include "types.h"

// TObjWeightExt's destructor (weightExtDtor here): the object breakableWeightCtor
// makes beside the breakable weight. It restores the vtable, destroys its
// collision volume and the object base, and frees the object when the delete
// flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct WeightExt {
	TObject base;   // 0x00
	u8 volume[0x4]; // 0x28
} WeightExt;

extern "C" void* lbl_8042C148;
extern "C" void* weightExtVtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* volume, s32 flags);

extern "C" WeightExt* weightExtDtor(WeightExt* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = weightExtVtable;

		__dt__7C_COLLIFv(object->volume, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
