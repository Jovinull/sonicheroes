#include "types.h"

// TObjBigRings's destructor. It restores both vtable pointers, frees the ring
// array it built through operator delete[] when the motion frame's 0x10000
// flag is set it flushes the motion base first, runs the motion base down and
// then the object base, and hands the object back to the heap when the
// caller asks for it.
//
// The claim is .text 0x1E910 to 0x1E9D8 and nothing else. The vtable stays in
// each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where bigRingsCtor
// begins.
//
// The run is the same in all twelve stage modules that share the engine core.
// Unlike most of the other TObj destructors in this family, TObjBigRings has
// no embedded Volume base, so there is no dtor_8003C52C call here.
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

typedef struct Frame {
	u8 unk0[0x18]; // 0x00
	u32 flags;     // 0x18
} Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __destroy_new_array(void* array, void (*destructor)(void*, int));
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8005BC04(Motion* motion);
extern "C" void bigRingsElementDtor(void*, int);

typedef struct BigRings {
	TObject base;    // 0x00
	Motion motion;   // 0x28
	u8 unk30[0x38];  // 0x30
	void* ringArray; // 0x68
} BigRings;          // 0x6C

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* bigRingsVtable[];

extern "C" BigRings* bigRingsDtor(BigRings* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = bigRingsVtable;
		object->motion.vtable = bigRingsVtable + 0xB;

		if (object->ringArray != NULL) {
			__destroy_new_array(object->ringArray, bigRingsElementDtor);
			object->ringArray = NULL;
		}

		if (object->motion.frame->flags & 0x10000) {
			fn_8005BC04(&object->motion);
		}

		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
