#include "types.h"

// CSkySphereStage04's destructor (skySphereStage04Dtor here; the class name is
// the string its constructor stores in the class-name word). It restores the
// vtable, runs the base CSkySphereStage down (its destructor stays assembly)
// and frees the object when the delete flag asks for it, the shape of
// rel/shield_splinter_dtor.cpp. It is in stage01D and stage03D.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

extern "C" void* lbl_8042C148;
extern "C" void* skySphereStage04Vtable[];

extern "C" void __dt__15CSkySphereStageFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" TObject* skySphereStage04Dtor(TObject* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = skySphereStage04Vtable;

		__dt__15CSkySphereStageFv(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
