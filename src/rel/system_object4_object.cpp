#include "types.h"

// TObjSystem4, the last of the four system objects every stage module ships.
// The class name is spelled in the module's own data, at the word the
// constructor reads: "TObjSystem4". Its registration record is already carved,
// in rel/system_object4_register.cpp.
//
// The claim is .text 0x4DE1C to 0x4DF74, the same code at the same address in
// the same nine stage modules rel/system_object1_object.cpp claims, and all 86
// instructions are identical across those nine once the per module label names
// are set aside.
//
// This is rel/system_object1_object.cpp function for function, and the argument
// for the bounds is written there. Like the first system object and unlike the
// second and third, all three of Reset, Unload and Load are empty, so the run
// is 86 instructions rather than 96. It has no adjustor thunk in front of it
// either: the run before it is the third system object's registration record.

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

typedef struct SystemObject4 {
	TObject base;  // 0x00
	Motion motion; // 0x28
} SystemObject4;   // 0x30

#define SIGNAL_KILL_OK 1

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_8005BE6C(Motion* motion);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* systemObject4ClassName;
extern "C" void* systemObject4Vtable[];

extern "C" void systemObject4Disp(void) { }

extern "C" void systemObject4Exec(SystemObject4* object)
{
	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= SIGNAL_KILL_OK;
	}
}

extern "C" SystemObject4* systemObject4Dtor(SystemObject4* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = systemObject4Vtable;
		object->motion.vtable = systemObject4Vtable + 0xB;
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" SystemObject4* systemObject4Ctor(SystemObject4* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);

	object->base.vtable   = systemObject4Vtable;
	object->motion.vtable = systemObject4Vtable + 0xB;

	object->base.className  = systemObject4ClassName;
	object->base.objectSize = 0x30;
	return object;
}

extern "C" void systemObject4Reset(void) { }

extern "C" void systemObject4Unload(void) { }

extern "C" void systemObject4Load(void) { }
