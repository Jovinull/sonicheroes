#include "types.h"

// TObjCase's destructor. It restores both vtable pointers, unregisters the model
// it built from the world's scene and drops it, puts the volume back into its
// idle state, runs the embedded volume and motion bases down and then the object
// base, and hands the object back to the heap when the caller asks for it.
//
// The claim is .text 0x00040F64 to 0x00041034 in stage01D/03D/05D/07D/09D/
// 11D/31D/32D/33D, and 0x39B2C to 0x39BFC in stage26D/27D/28D: the same
// bytes, but the surrounding unclaimed code is laid out differently between
// the two revisions of the shared engine core, so the run sits at a
// different address in each. The vtable stays
// in each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where caseObjCtor
// begins.
//
// The store of 7 at +0x3A is inside the volume rather than the object's own
// fields, which is why the volume carries a named halfword here. It runs
// whether or not there was a model to drop, so it sits outside that guard.//
// The run is the same in all twelve stage modules that share the engine
// core, checked by
// normalising the disassembly and comparing across modules.
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

typedef struct Volume {
	u8 unk0[0x0A];  // 0x00
	u16 state;      // 0x0A
	u8 unk0C[0x7C]; // 0x0C
} Volume;           // 0x88

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

typedef struct CaseObj {
	TObject base;   // 0x00
	Motion motion;  // 0x28
	Volume volume;  // 0x30
	u8 unkB8[0x2C]; // 0xB8
	void* model;    // 0xE4
} CaseObj;          // 0xE8

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* caseObjVtable[];

extern "C" CaseObj* caseObjDtor(CaseObj* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = caseObjVtable;
		object->motion.vtable = caseObjVtable + 0xB;

		if (object->model != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->model);
			fn_80150958(object->model);
			object->model = NULL;
		}

		object->volume.state = 7;

		dtor_8003C52C(&object->volume, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
