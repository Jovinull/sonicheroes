#include "types.h"

// The destructor of the class the module's own data names ENEMY_SHIELD_SPLINTER.
// The plainest of the family: it restores the one vtable, runs the object base
// down and hands the object back to the heap when the caller asks for it. The
// class embeds no second base and registers nothing, so there is no second
// vtable pointer and nothing to release.
//
// The name is read out of the binary, not guessed from the neighbourhood: the
// constructor that follows at 0x37280 stores the string at 0x3A78 into the
// object's class-name word, and that string is ENEMY_SHIELD_SPLINTER.
//
// The claim is .text 0x3720C to 0x37280 and nothing else. The vtable stays in
// each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The run is the same in the nine stage modules that carry this revision of the
// engine core — 01D, 03D, 05D, 07D, 09D, 11D, 31D, 32D and 33D — the same set
// rel/system_object1_object.cpp records.
//
// The delete flag is a short. It is sign extended before the test, so a plain
// s32 parameter does not reproduce the compare.

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

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* shieldSplinterVtable[];

extern "C" TObject* shieldSplinterDtor(TObject* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = shieldSplinterVtable;

		__dt__7TObjectFv(object, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, object);
		}
	}
	return object;
}
