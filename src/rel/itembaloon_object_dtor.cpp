#include "types.h"

// ITEMBALOON OBJECT's destructor. It restores both vtable pointers, drops
// the model it built, runs the embedded volume and motion bases down and
// then the object base, and hands the object back to the heap when the
// caller asks for it.
//
// The claim is .text 0x3CDB0 to 0x3CE58 and nothing else. The vtable stays
// in each module's data and is renamed to the shared name below; it reads
// no constant, so it owns no rodata.
//
// itembaloonObjectCreate (rel/itembaloon_register.cpp) constructs objects
// with the same vtable this run writes, which is how the family is
// identified: no *Ctor boundary sits next to this run, so the name comes
// from tracing the vtable's other user instead.
//
// The model is released without a null check first, the same shape as
// rel/item_box_dtor.cpp.
//
// The run is the same in the nine stage modules that carry it.
//
// The delete flag is a short. It is sign extended before the test, so a
// plain s32 parameter does not reproduce the compare.

typedef struct TObject {
	const char* className;  // 0x00
	u16 signal;             // 0x04
	u16 tag;                // 0x06
	struct TObject* prev;   // 0x08
	struct TObject* next;   // 0x0C
	struct TObject* parent; // 0x10
	struct TObject* child;  // 0x14
	void** vtable;          // 0x18
	s16 unk1C;              // 0x1C
	s16 objectSize;         // 0x1E
	s16 unk20;              // 0x20
	s16 unk22;              // 0x22
	s16 unk24;              // 0x24
	s16 unk26;              // 0x26
} TObject;                  // 0x28

typedef struct Frame Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

typedef struct Volume {
	u8 unk0[0x88]; // 0x00
} Volume;          // 0x88

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_80150958(void* mesh);

typedef struct ItembaloonObject {
	TObject base;   // 0x00
	Motion motion;  // 0x28
	Volume volume;  // 0x30
	u8 unkB8[0x38]; // 0xB8
	void* model;    // 0xF0
} ItembaloonObject; // 0xF4

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* itembaloonObjectVtable[];

extern "C" ItembaloonObject* itembaloonObjectDtor(ItembaloonObject* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = itembaloonObjectVtable;
		object->motion.vtable = itembaloonObjectVtable + 0xB;

		fn_80150958(object->model);
		object->model = NULL;

		dtor_8003C52C(&object->volume, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
