#include "types.h"

// TObjSystem3, the third of the four system objects every stage module ships.
// The class name is spelled in the module's own data, at the word the
// constructor reads: "TObjSystem3". Its registration record is already carved,
// in rel/system_object3_register.cpp.
//
// The claim is .text 0x4DB6C to 0x4DCEC, the same code at the same address in
// the same nine stage modules rel/system_object1_object.cpp claims, and all 96
// instructions are identical across those nine once the per module label names
// are set aside.
//
// This is rel/system_object2_object.cpp function for function, and the argument
// for the bounds is in rel/system_object1_object.cpp. The single difference from
// the second system object is the engine entry point Load hands the scene
// pointer to: fn_8005B268 here against fn_8005B2C4 there. Normalising the label
// names, the two runs are 96 instructions that differ in exactly that one
// branch target.

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

typedef struct SystemObject3 {
	TObject base;  // 0x00
	Motion motion; // 0x28
} SystemObject3;   // 0x30

#define SIGNAL_KILL_OK 1

extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C298;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8005B268(void* scene);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_8005BE6C(Motion* motion);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const char* systemObject3ClassName;
extern "C" void* systemObject3Vtable[];

extern "C" void systemObject3Disp(void) { }

extern "C" void systemObject3Exec(SystemObject3* object)
{
	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= SIGNAL_KILL_OK;
	}
}

extern "C" SystemObject3* systemObject3Dtor(SystemObject3* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = systemObject3Vtable;
		object->motion.vtable = systemObject3Vtable + 0xB;
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" SystemObject3* systemObject3Ctor(SystemObject3* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);

	object->base.vtable   = systemObject3Vtable;
	object->motion.vtable = systemObject3Vtable + 0xB;

	object->base.className  = systemObject3ClassName;
	object->base.objectSize = 0x30;
	return object;
}

extern "C" void systemObject3Reset(void) { }

extern "C" void systemObject3Unload(void) { }

extern "C" void systemObject3Load(void)
{
	fn_8005B268(lbl_8042C298);
}
