#include "types.h"

// TObjDashRing's destructor. It restores both vtable pointers, unregisters the
// two meshes it built from the world's scene and drops them, frees a buffer
// through operator delete, runs the embedded motion base down and then the
// object base, and hands the object back to the heap when the caller asks
// for it.
//
// The claim is .text 0xDC58 to 0xDD5C and nothing else. The vtable stays in
// each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where dashRingCtor
// begins.
//
// The run is the same in all twelve stage modules that share the engine core.
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
} Motion;          // 0x08

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	void* scene;     // 0x725C
} World;

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __dl__FPv(void* memory);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8015BBF8(void* scene, void* mesh);
extern "C" void fn_80150958(void* mesh);

typedef struct DashRing {
	TObject base;   // 0x00
	Motion motion;  // 0x28
	u8 unk30[0x30]; // 0x30
	void* mesh1;    // 0x60
	void* mesh2;    // 0x64
	void* buffer;   // 0x68
} DashRing;

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* dashRingVtable[];

extern "C" DashRing* dashRingDtor(DashRing* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = dashRingVtable;
		object->motion.vtable = dashRingVtable + 0xB;

		if (object->mesh1 != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->mesh1);
			fn_80150958(object->mesh1);
			object->mesh1 = NULL;
		}

		if (object->mesh2 != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->mesh2);
			fn_80150958(object->mesh2);
			object->mesh2 = NULL;
		}

		if (object->buffer != NULL) {
			__dl__FPv(object->buffer);
			object->buffer = NULL;
		}

		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
