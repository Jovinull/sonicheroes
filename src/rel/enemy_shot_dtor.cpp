#include "types.h"

// The destructor of the class the module's data names ENEMY_SHOT (enemyShotDtor
// here): it restores the vtable, destroys the shot's collision volume and the
// object base, and frees the object when the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct EnemyShot {
	TObject base;   // 0x00
	u8 unk28[0x38]; // 0x28
	u8 volume[0x4]; // 0x60
} EnemyShot;

extern "C" void* lbl_8042C148;
extern "C" void* enemyShotVtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* volume, s32 flags);

extern "C" EnemyShot* enemyShotDtor(EnemyShot* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = enemyShotVtable;

		__dt__7C_COLLIFv(object->volume, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
