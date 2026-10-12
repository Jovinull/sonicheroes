#include "types.h"

// TObjFormGateSub's destructor (formgateSubDtor here): it restores the vtable,
// destroys the collision volume and the object base, and frees the object when
// the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct FormgateSub {
	TObject base;   // 0x00
	u8 volume[0x4]; // 0x28
} FormgateSub;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__15TObjFormGateSub[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* volume, s32 flags);

extern "C" FormgateSub* formgateSubDtor(FormgateSub* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = __vt__15TObjFormGateSub;

		__dt__7C_COLLIFv(object->volume, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
