#include "types.h"

// S02 WATER's destructor. It restores both vtable pointers, unregisters the
// clump's atomic from wherever it was registered and drops the clump, runs
// the embedded motion base down and then the object base, and hands the
// object back to the heap when the caller asks for it. The object embeds no
// Volume base, only Motion.
//
// The claim is .text 0xA2EA8 to 0xA2F68 and nothing else. The vtable stays
// in each module's data and is renamed to the shared name below; it reads
// no constant, so it owns no rodata.
//
// s02WaterCreate (rel/s02_water_register.cpp) constructs objects with the
// same vtable this run writes, which is how the family is identified: no
// *Ctor boundary sits next to this run, so the name comes from tracing the
// vtable's other user instead.
//
// The clump release is the same three-call shape as flowerDtor in
// rel/o_s01_hana.cpp: look up the atomic from the clump first, then
// unregister the atomic/clump pair, then drop the clump itself.
//
// stage01D only.
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

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void* fn_8015BD78(void* clump);
extern "C" void fn_8015BBF8(void* atomic, void* clump);
extern "C" void fn_80150958(void* clump);

typedef struct S02Water {
	TObject base;  // 0x00
	Motion motion; // 0x28
	void* clump;   // 0x30
} S02Water;        // 0x34

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* s02WaterVtable[];

extern "C" S02Water* s02WaterDtor(S02Water* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = s02WaterVtable;
		object->motion.vtable = s02WaterVtable + 0xB;

		if (object->clump != NULL) {
			void* clump  = object->clump;
			void* atomic = fn_8015BD78(clump);
			fn_8015BBF8(atomic, clump);
			fn_80150958(object->clump);
			object->clump = NULL;
		}

		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
