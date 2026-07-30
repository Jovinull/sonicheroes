#include "types.h"

// TObjSetCollision's destructor. It restores both vtable pointers, releases the
// collision mesh it registered with the stage, runs the two embedded bases down
// and then the object base, and finally hands the object back to the heap when
// the caller asks for it.
//
// The claim is .text 0x5A34 to 0x5AFC and nothing else. The vtable stays in each
// module's data and is renamed to the shared name below. The constructor that
// follows at 0x5AFC is a separate change; rel/set_collision_object.cpp already
// carves the guard, the hooks and the factory from 0x5F4C on.
//
// The destructor sits below the constructor in address order, the same way
// round rel/switch_dtor.cpp and rel/switch_object.cpp are laid out.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
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

typedef struct Frame Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;

typedef struct Volume {
	u8 unk0[0xB4]; // 0x00
} Volume;

typedef struct SetCollision {
	TObject base;  // 0x00
	Motion motion; // 0x28
	Volume volume; // 0x30
	void* mesh;    // 0xE4
} SetCollision;    // 0xE8

extern "C" void* lbl_8042C148;
extern "C" u8* lbl_8042C1D0;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8015BBF8(void* world, void* mesh);
extern "C" void fn_80150958(void* mesh);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* setCollisionVtable[];

extern "C" SetCollision* setCollisionDtor(SetCollision* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = setCollisionVtable;
		object->motion.vtable = setCollisionVtable + 0xB;

		if (object->mesh != NULL) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 29348), object->mesh);
			fn_80150958(object->mesh);
			object->mesh = NULL;
		}

		dtor_8003C52C(&object->volume, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
