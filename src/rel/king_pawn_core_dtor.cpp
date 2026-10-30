#include "types.h"

// TObjBossKingPawnCore's destructor (kingPawnCoreDtor here; the class name is
// the string its constructor stores in the class-name word). It restores the
// vtable, closes the enemy icon at 0x120 and deletes the material helper at
// 0x134 when they were made, takes the clump at 0x12C out of the world it is
// in and destroys it, runs its base down (the parts' shared base of
// rel/king_pawn_part_dtor.cpp) and frees the object when the delete flag asks
// for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct KingPawnCore {
	TObject base;   // 0x00
	u8 unk28[0xF8]; // 0x28
	void* icon;     // 0x120, a TEnemyIconMan
	u8 unk124[0x8]; // 0x124
	void* clump;    // 0x12C
	u8 unk130[0x4]; // 0x130
	void* material; // 0x134, a DealMaterial
} KingPawnCore;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnCoreVtable[];

extern "C" void Close__13TEnemyIconManFv(void* icon);
extern "C" void __dt__12DealMaterialFv(void* material, s32 flags);
extern "C" void* fn_8015BD78(void* clump);
extern "C" void fn_8015BBF8(void* world, void* clump);
extern "C" void fn_80150958(void* clump);
extern "C" void kingPawnPartDtor(KingPawnCore* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, KingPawnCore* object);

extern "C" KingPawnCore* kingPawnCoreDtor(KingPawnCore* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = kingPawnCoreVtable;

		if (object->icon != NULL) {
			Close__13TEnemyIconManFv(object->icon);
		}
		if (object->material != NULL) {
			__dt__12DealMaterialFv(object->material, 1);
		}
		if (object->clump != NULL) {
			void* world = fn_8015BD78(object->clump);

			if (world != NULL) {
				fn_8015BBF8(world, object->clump);
			}
			fn_80150958(object->clump);
		}

		kingPawnPartDtor(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
