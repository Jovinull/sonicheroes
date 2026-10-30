#include "types.h"

// TObjBossKingPawnShieldCore's destructor (kingPawnShieldCoreDtor here; the
// class name is the string its constructor stores in the class-name word). It
// restores the vtable, closes the enemy icon at 0x11C, deletes the material
// helper at 0x12C and destroys the frame at 0x140 when they were made, runs
// its base down (the parts' shared base of rel/king_pawn_part_dtor.cpp) and
// frees the object when the delete flag asks for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct KingPawnShieldCore {
	TObject base;    // 0x00
	u8 unk28[0xF4];  // 0x28
	void* icon;      // 0x11C, a TEnemyIconMan
	u8 unk120[0xC];  // 0x120
	void* material;  // 0x12C, a DealMaterial
	u8 unk130[0x10]; // 0x130
	void* frame;     // 0x140, an RwFrame
} KingPawnShieldCore;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnShieldCoreVtable[];

extern "C" void Close__13TEnemyIconManFv(void* icon);
extern "C" void __dt__12DealMaterialFv(void* material, s32 flags);
extern "C" void fn_8019E480(void* frame);
extern "C" void kingPawnPartDtor(KingPawnShieldCore* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, KingPawnShieldCore* object);

extern "C" KingPawnShieldCore* kingPawnShieldCoreDtor(KingPawnShieldCore* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = kingPawnShieldCoreVtable;

		if (object->icon != NULL) {
			Close__13TEnemyIconManFv(object->icon);
		}
		if (object->material != NULL) {
			__dt__12DealMaterialFv(object->material, 1);
		}
		if (object->frame != NULL) {
			fn_8019E480(object->frame);
		}

		kingPawnPartDtor(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
