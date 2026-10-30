#include "types.h"

// TObjBossKingPawnSlash's destructor (kingPawnSlashDtor here; the class name is
// the string its constructor stores in the class-name word). It restores the
// vtable, deletes the material helper at 0x128 and destroys the clump at
// 0x114 when they were made, runs its base down (the parts' shared base of
// rel/king_pawn_part_dtor.cpp) and frees the object when the delete flag asks
// for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct KingPawnSlash {
	TObject base;    // 0x00
	u8 unk28[0xEC];  // 0x28
	void* clump;     // 0x114
	u8 unk118[0x10]; // 0x118
	void* material;  // 0x128, a DealMaterial
} KingPawnSlash;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnSlashVtable[];

extern "C" void __dt__12DealMaterialFv(void* material, s32 flags);
extern "C" void fn_80150958(void* clump);
extern "C" void kingPawnPartDtor(KingPawnSlash* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, KingPawnSlash* object);

extern "C" KingPawnSlash* kingPawnSlashDtor(KingPawnSlash* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = kingPawnSlashVtable;

		if (object->material != NULL) {
			__dt__12DealMaterialFv(object->material, 1);
		}
		if (object->clump != NULL) {
			fn_80150958(object->clump);
		}

		kingPawnPartDtor(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
