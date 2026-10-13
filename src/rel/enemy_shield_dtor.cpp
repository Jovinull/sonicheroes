#include "types.h"

// ENEMY_SHIELD's destructor (the PS2 build's name): it restores the vtable,
// destroys the shield's collision and the object base, and frees the object
// when the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct EnemyShield {
	TObject base;  // 0x00
	u8 colli[0x4]; // 0x28
} EnemyShield;

extern "C" void* lbl_8042C148;
extern "C" void* __vt__12ENEMY_SHIELD[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);

extern "C" EnemyShield* __dt__12ENEMY_SHIELDFv(EnemyShield* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = __vt__12ENEMY_SHIELD;

		__dt__7C_COLLIFv(object->colli, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
