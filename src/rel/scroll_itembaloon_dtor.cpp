#include "types.h"

// The scroll item balloon's destructor (TObjScrollItembaloon in the PS2 build;
// scrollItembaloonDtor here). It restores its own vtables, then runs
// TObjItembaloon's destructor inlined (rel/itembaloon_object_dtor.cpp): the
// base vtables, the model released and cleared, the collision, placement and
// object bases; last it frees the object when the delete flag asks for it.
// The inlined base keeps its own NULL test, which the original tests again on
// the flags the first test left.

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
extern "C" void __dt__7C_COLLIFv(Volume* volume, s32 flags);
extern "C" void __dt__10TObjSetObjFv(Motion* motion, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void fn_80150958(void* mesh);

typedef struct ItembaloonObject {
	TObject base;   // 0x00
	Motion motion;  // 0x28
	Volume volume;  // 0x30
	u8 unkB8[0x38]; // 0xB8
	void* model;    // 0xF0
} ItembaloonObject; // 0xF4

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* __vt__14TObjItembaloon[];
extern "C" void* __vt__20TObjScrollItembaloon[];

extern "C" ItembaloonObject* scrollItembaloonDtor(ItembaloonObject* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = __vt__20TObjScrollItembaloon;
		object->motion.vtable = __vt__20TObjScrollItembaloon + 0xB;

		if (object != NULL) {
			object->base.vtable   = __vt__14TObjItembaloon;
			object->motion.vtable = __vt__14TObjItembaloon + 0xB;

			fn_80150958(object->model);
			object->model = NULL;

			__dt__7C_COLLIFv(&object->volume, 0);
			__dt__10TObjSetObjFv(&object->motion, 0);
			__dt__7TObjectFv(&object->base, 0);
		}

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
