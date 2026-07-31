#include "types.h"

// TObjInvokeCollision's destructor. It restores both vtable pointers, drops the
// trigger it registered, tells itself to detach while it still has motion, runs
// the two embedded bases down and then the object base, and hands the object
// back to the heap when the caller asks for it.
//
// The claim is .text 0x4F6F0 to 0x4F7D4 and nothing else. The vtable stays in
// each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The run is the same in the nine stage modules that carry this revision of the
// engine core - 01D, 03D, 05D, 07D, 09D, 11D, 31D, 32D and 33D - which is the
// same set rel/system_object1_object.cpp records. The other stage modules are a
// different revision this far in.
//
// The detach is a real virtual call on the object itself, through the object's
// own vtable at 0x18 and the thirteenth slot. MWCC puts an eight-byte header
// ahead of the entries, so the 56 in the original is index twelve.
//
// The delete flag is a short. It is sign extended before the test, so a plain
// s32 parameter does not reproduce the compare.

typedef struct Frame {
	u8 unk0[0x2A]; // 0x00
	u8 slot;       // 0x2A
} Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

typedef struct Volume {
	u8 unk0[0x88]; // 0x00
} Volume;          // 0x88

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, void* object);
extern "C" s32 fn_8005B8D8(Motion* motion);
extern "C" void fn_80063E7C(void* trigger, s32 mode);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* invokeCollisionVtable[];

// The object's data up to where the compiler puts the vtable pointer, so the
// pointer lands at 0x18 the way TObject's does.
struct InvokeCollisionData {
	u8 unk0[0x18]; // 0x00
};

struct InvokeCollision : public InvokeCollisionData {
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void detach(u8 slot, s32 mode);

	// vtable pointer at 0x18
	u8 unk1C[0xC]; // 0x1C
	Motion motion; // 0x28
	Volume volume; // 0x30
	void* trigger; // 0xB8
};

extern "C" InvokeCollision* invokeCollisionDtor(InvokeCollision* object, s16 flags)
{
	if (object != NULL) {
		*(void***)((u8*)object + 0x18) = invokeCollisionVtable;
		object->motion.vtable          = invokeCollisionVtable + 0xB;

		if (object->trigger != NULL) {
			fn_80063E7C(object->trigger, 1);
			object->trigger = NULL;
		}

		if (fn_8005B8D8(&object->motion) != 0) {
			object->detach(object->motion.frame->slot, 0);
		}

		dtor_8003C52C(&object->volume, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(object, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, object);
		}
	}
	return object;
}
