#include "types.h"

// TObjSystem1, the first of the four system objects every stage module ships.
// The class name is spelled in the module's own data, at the word the
// constructor reads: "TObjSystem1". Its registration record is already carved,
// in rel/system_object1_register.c.
//
// The claim is .text 0x4D634 to 0x4D78C, the same code at the same address in
// nine of the fourteen stage modules: stage01D, 03D, 05D, 07D, 09D, 11D, 31D,
// 32D and 33D. All 86 instructions are identical across those nine once the
// per module label names are set aside. stage13D, 26D, 27D and 28D are a
// different revision this far in, and stage40D everywhere, which is the same
// set the registration file claims.
//
// The lower bound is not where the gap starts. The gap opens at 0x4D62C with an
// adjustor thunk, `subi r3, r3, 0x28` then a branch to the stub at 0x4D37C, and
// that stub sits inside the goal ring's run. CodeWarrior emits an adjustor
// thunk at the end of the translation unit that owns the function it forwards
// to, so the thunk is the goal ring's tail, not this file's head. The three
// siblings settle it: systemObject2, 3 and 4 each open with a lone blr and have
// no thunk in front of them, at 0x4D8BC, 0x4DB6C and 0x4DE1C. So the blr is the
// first function of an object's own run, and this one starts at 0x4D634.
//
// The upper bound stops short of the factory at 0x4D78C for the reason
// rel/sample1_object.c already records: the original keeps the allocator's
// result and the pointer the construction runs on in separate registers, `mr
// r0, r3` and then `mr r31, r0`, and no source form reproduces the extra copy.
// It stays assembly here as it does there.
//
// The object is the base plus one embedded second base and nothing else: the
// constructor writes 0x30 as the instance size, and the second base starts at
// 0x28, which is the eight bytes of Motion. The vtable is fourteen words; the
// second base's vtable pointer is the same block plus 0x2C, so it aliases slot
// eleven, exactly as the two sample objects do.
//
// Slot four holds the empty hook below. The name is a guess, taken from the
// same slot in the sample objects, where the project already calls it Disp.
// Nothing in the binary spells it.

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
} TObject;

typedef struct Frame Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;

typedef struct SystemObject1 {
	TObject base;  // 0x00
	Motion motion; // 0x28
} SystemObject1;   // 0x30

// Msg_KillOk, the bit Exec raises once the path is spent. Same bit and same
// pair of tests the sample objects use.
#define SIGNAL_KILL_OK 1

extern "C" void* lbl_8042C148;

extern "C" void dtor_800186D0(TObject* object, s32 flags);
extern "C" void fn_80018818(TObject* object, void* owner);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_8005BE6C(Motion* motion);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* systemObject1ClassName;
extern "C" void* systemObject1Vtable[];

extern "C" void systemObject1Disp(void) { }

extern "C" void systemObject1Exec(SystemObject1* object)
{
	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= SIGNAL_KILL_OK;
	}
}

extern "C" SystemObject1* systemObject1Dtor(SystemObject1* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = systemObject1Vtable;
		object->motion.vtable = systemObject1Vtable + 0xB;
		dtor_8005BD3C(&object->motion, 0);
		dtor_800186D0(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" SystemObject1* systemObject1Ctor(SystemObject1* object, void* owner)
{
	fn_80018818(&object->base, owner);
	fn_8005BE6C(&object->motion);

	object->base.vtable   = systemObject1Vtable;
	object->motion.vtable = systemObject1Vtable + 0xB;

	object->base.className  = systemObject1ClassName;
	object->base.objectSize = 0x30;
	return object;
}

extern "C" void systemObject1Reset(void) { }

extern "C" void systemObject1Unload(void) { }

extern "C" void systemObject1Load(void) { }
