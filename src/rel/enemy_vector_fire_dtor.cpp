#include "types.h"

// TObjEnemyVectorFire's destructor (enemyVectorFireDtor here; the class name is the string its
// constructor stores in the class-name word). It restores the vtable, destroys
// its collision volume and the object base, and frees the object when the
// delete flag asks for it, the body of rel/weight_ext_dtor.cpp. Only stage27D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct EnemyVectorFire {
	TObject base;   // 0x00
	u8 volume[0x4]; // 0x28
} EnemyVectorFire;

extern "C" void* lbl_8042C148;
extern "C" void* enemyVectorFireVtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* volume, s32 flags);

extern "C" EnemyVectorFire* enemyVectorFireDtor(EnemyVectorFire* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = enemyVectorFireVtable;

		__dt__7C_COLLIFv(object->volume, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
