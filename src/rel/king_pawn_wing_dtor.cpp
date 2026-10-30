#include "types.h"

// TObjBossKingPawnWing's destructor (kingPawnWingDtor here; the class name is
// the string its constructor stores in the class-name word). It restores the
// vtable, destroys the three wing clumps from 0x124 that were made, runs its
// base down (the parts' shared base of rel/king_pawn_part_dtor.cpp) and frees
// the object when the delete flag asks for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct KingPawnWing {
	TObject base;   // 0x00
	u8 unk28[0xFC]; // 0x28
	void* clump[3]; // 0x124
} KingPawnWing;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnWingVtable[];

extern "C" void fn_80150958(void* clump);
extern "C" void kingPawnPartDtor(KingPawnWing* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, KingPawnWing* object);

extern "C" KingPawnWing* kingPawnWingDtor(KingPawnWing* object, s16 flags)
{
	if (object != NULL) {
		s32 i;

		object->base.vtable = kingPawnWingVtable;

		for (i = 0; i != 3; i++) {
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
