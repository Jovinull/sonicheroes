#include "types.h"

// S31 BOB DUMMY's destructor. It restores both vtable pointers, runs the
// embedded motion base down and then the object base, and hands the object
// back to the heap when the caller asks for it. The object is the base plus
// one embedded second base and nothing else, the same shape as the four
// system objects.
//
// The claim is .text 0xC218C to 0xC2218 and nothing else. The vtable stays
// in each module's data and is renamed to the shared name below; it reads
// no constant, so it owns no rodata.
//
// s31bobObjectdummyCreate (rel/s31_bob_dummy_register.cpp) constructs
// objects with the same vtable this run writes, which is how the family is
// identified: no *Ctor boundary sits next to this run, so the name comes
// from tracing the vtable's other user instead. The constructor sits right
// after this run at every address below, but is left as assembly here.
//
// The run is the same in all twelve stage modules that share the engine
// core, each at its own address:
//   stage01D 0xC218C   stage03D 0xB1CC4   stage05D 0x7C104   stage07D 0xD0A4C
//   stage09D 0xAA51C   stage11D 0x87C70   stage26D 0x71F9C   stage27D 0x74A58
//   stage28D 0x75F4C   stage31D 0x70CE8   stage32D 0x70CE8   stage33D 0x736C4
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

typedef struct S31BobDummy {
	TObject base;  // 0x00
	Motion motion; // 0x28
} S31BobDummy;     // 0x30

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* s31bobObjectdummyVtable[];

extern "C" S31BobDummy* s31bobObjectdummyDtor(S31BobDummy* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = s31bobObjectdummyVtable;
		object->motion.vtable = s31bobObjectdummyVtable + 0xB;

		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
