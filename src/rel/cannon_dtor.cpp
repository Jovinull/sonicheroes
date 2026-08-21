#include "types.h"

// TObjCannon's destructor. It restores both vtable pointers, unregisters the
// mesh it built from the world's scene and drops it, runs the embedded
// volume and motion bases down and then the object base, and hands the
// object back to the heap when the caller asks for it.
//
// The claim is .text 0x19EBC to 0x19F84 and nothing else. The vtable stays
// in each module's data and is renamed to the shared name below; it reads
// no constant, so it owns no rodata.
//
// cannonCreate (rel/cannon_register.cpp) constructs objects with the same
// vtable this run writes, which is how the family is identified: no *Ctor
// boundary sits next to this run (the constructor at 0x1A1A8 is rodata-heavy
// and shares constants with the module's dialogue data, so it stays out of
// scope here), so the name comes from tracing the vtable's other user
// instead.
//
// The run is the same in all twelve stage modules that share the engine
// core.
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

typedef struct Volume {
	u8 unk0[0x88]; // 0x00
} Volume;          // 0x88

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	void* scene;     // 0x725C
} World;

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8015BBF8(void* scene, void* mesh);
extern "C" void fn_80150958(void* mesh);

typedef struct Cannon {
	TObject base;   // 0x00
	Motion motion;  // 0x28
	Volume volume;  // 0x30
	u8 unkB8[0x5C]; // 0xB8
	void* mesh;     // 0x114
} Cannon;           // 0x118

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* cannonVtable[];

extern "C" Cannon* cannonDtor(Cannon* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = cannonVtable;
		object->motion.vtable = cannonVtable + 0xB;

		if (object->mesh != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->mesh);
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
