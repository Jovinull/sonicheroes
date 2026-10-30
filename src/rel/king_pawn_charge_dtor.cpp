#include "types.h"

// TObjBossKingPawnCharge's destructor (kingPawnChargeDtor here; the class name is
// the string its constructor stores in the class-name word). It restores the
// vtable, destroys the two effect clumps from 0x124 that were made, runs its
// base down (the parts' shared base of rel/king_pawn_part_dtor.cpp) and frees
// the object when the delete flag asks for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct KingPawnCharge {
	TObject base;   // 0x00
	u8 unk28[0xFC]; // 0x28
	void* clump[2]; // 0x124
} KingPawnCharge;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnChargeVtable[];

extern "C" void fn_80150958(void* clump);
extern "C" void kingPawnPartDtor(KingPawnCharge* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, KingPawnCharge* object);

extern "C" KingPawnCharge* kingPawnChargeDtor(KingPawnCharge* object, s16 flags)
{
	if (object != NULL) {
		s32 i;

		object->base.vtable = kingPawnChargeVtable;

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
