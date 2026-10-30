#include "types.h"

// TObjBossKingPawnLance's destructor (kingPawnLanceDtor here; the class name is the
// string its constructor stores in the class-name word). It restores the
// vtable and runs its base down, the parts' shared base of
// rel/king_pawn_part_dtor.cpp, then frees the object when the delete flag asks
// for it. Only stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnLanceVtable[];

extern "C" void kingPawnPartDtor(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" TObject* kingPawnLanceDtor(TObject* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = kingPawnLanceVtable;

		kingPawnPartDtor(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
