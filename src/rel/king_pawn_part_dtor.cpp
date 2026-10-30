#include "types.h"

// The destructor of the base the King Pawn's parts share (kingPawnPartDtor
// here: the class stores no name of its own and has no PS2 counterpart, whose
// parts derive from TObject directly). It restores the vtable, runs the
// collision block at 0x28 and then the object base down, and frees the object
// when the delete flag asks for it. The parts' destructors
// (rel/king_pawn_armor_dtor.cpp and the others) run it as their base. Only
// stage26D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct KingPawnPart {
	TObject base;   // 0x00
	u8 colli[0x88]; // 0x28, a C_COLLI
} KingPawnPart;

extern "C" void* lbl_8042C148;
extern "C" void* kingPawnPartVtable[];

extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" KingPawnPart* kingPawnPartDtor(KingPawnPart* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = kingPawnPartVtable;

		__dt__7C_COLLIFv(object->colli, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
