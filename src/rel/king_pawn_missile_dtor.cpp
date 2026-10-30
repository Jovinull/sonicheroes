#include "types.h"

// TObjBossKingPawnMissile's destructor (kingPawnMissileDtor here; the class
// name is the string its constructor stores in the class-name word). It
// restores the vtable, releases the frame of the second clump (the clump's
// parent word) and destroys the two clumps from 0x118 that were made, runs
// its base down (the parts' shared base of rel/king_pawn_part_dtor.cpp) and
// frees the object when the delete flag asks for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct Clump {
	u8 unk00[0x4];
	void* frame; // 0x04
} Clump;

typedef struct KingPawnMissile {
	TObject base;    // 0x00
	u8 unk28[0xF0];  // 0x28
	Clump* clump[2]; // 0x118
} KingPawnMissile;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnMissileVtable[];

extern "C" void fn_8019EA2C(void* frame);
extern "C" void fn_80150958(Clump* clump);
extern "C" void kingPawnPartDtor(KingPawnMissile* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, KingPawnMissile* object);

extern "C" KingPawnMissile* kingPawnMissileDtor(KingPawnMissile* object, s16 flags)
{
	if (object != NULL) {
		s32 i;

		object->base.vtable = kingPawnMissileVtable;

		if (object->clump[1] != NULL && object->clump[1]->frame != NULL) {
			fn_8019EA2C(object->clump[1]->frame);
		}

		for (i = 0; i != 2; i++) {
			if (object->clump[i] != NULL) {
				fn_80150958(object->clump[i]);
			}
		}

		kingPawnPartDtor(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
