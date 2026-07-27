#include "types.h"

// TObjSystem2, the second of the four system objects every stage module ships.
// The class name is spelled in the module's own data, at the word the
// constructor reads: "TObjSystem2". Its registration record is already carved,
// in rel/system_object2_register.c.
//
// The claim is .text 0x4D8BC to 0x4DA3C, the same code at the same address in
// the same nine stage modules rel/system_object1_object.c claims, and all 96
// instructions are identical across those nine once the per module label names
// are set aside.
//
// The shape is rel/system_object1_object.c's, and the argument for the bounds
// is written there: the run opens with the empty hook that fills vtable slot
// four and stops before the factory, whose register use no source form
// reproduces. Two things differ from the first system object. There is no
// adjustor thunk in front of this one, because the run before it is the
// registration record rather than a class with a second base. And Load is not
// empty: it hands the module's scene pointer to the engine, where the first and
// fourth system objects do nothing. The third does the same with a different
// engine entry point, fn_8005B268.

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

typedef struct SystemObject2 {
	TObject base;  // 0x00
	Motion motion; // 0x28
} SystemObject2;   // 0x30

#define SIGNAL_KILL_OK 1

extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C298;

extern "C" void dtor_800186D0(TObject* object, s32 flags);
extern "C" void fn_80018818(TObject* object, void* owner);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8005B2C4(void* scene);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_8005BE6C(Motion* motion);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* systemObject2ClassName;
extern "C" void* systemObject2Vtable[];

extern "C" void systemObject2Disp(void) { }

extern "C" void systemObject2Exec(SystemObject2* object)
{
	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= SIGNAL_KILL_OK;
	}
}

extern "C" SystemObject2* systemObject2Dtor(SystemObject2* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = systemObject2Vtable;
		object->motion.vtable = systemObject2Vtable + 0xB;
		dtor_8005BD3C(&object->motion, 0);
		dtor_800186D0(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" SystemObject2* systemObject2Ctor(SystemObject2* object, void* owner)
{
	fn_80018818(&object->base, owner);
	fn_8005BE6C(&object->motion);

	object->base.vtable   = systemObject2Vtable;
	object->motion.vtable = systemObject2Vtable + 0xB;

	object->base.className  = systemObject2ClassName;
	object->base.objectSize = 0x30;
	return object;
}

extern "C" void systemObject2Reset(void) { }

extern "C" void systemObject2Unload(void) { }

extern "C" void systemObject2Load(void)
{
	fn_8005B2C4(lbl_8042C298);
}
