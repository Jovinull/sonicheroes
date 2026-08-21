#include "types.h"

// TObjTriSpring's destructor. It restores both vtable pointers, releases
// three meshes it registered with the world's scene and three buffers
// through the same loop, runs the embedded volume and motion bases down and
// then the object base, and hands the object back to the heap when the
// caller asks for it.
//
// The claim is .text 0x282C to 0x2920 and nothing else. The vtable stays in
// each module's data and is renamed to the shared name below; it reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where
// triSpringCtor begins.
//
// The run is the same in all thirteen stage modules that share the engine
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

typedef struct TriSpring {
	TObject base;     // 0x00
	Motion motion;    // 0x28
	Volume volume;    // 0x30
	u8 unkB8[0x40];   // 0xB8
	void* meshes[3];  // 0xF8
	void* buffers[3]; // 0x104
} TriSpring;          // 0x110

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* triSpringVtable[];

extern "C" TriSpring* triSpringDtor(TriSpring* object, s16 flags)
{
	s32 i;

	if (object != NULL) {
		object->base.vtable   = triSpringVtable;
		object->motion.vtable = triSpringVtable + 0xB;

		for (i = 0; i < 3; i++) {
			if (object->meshes[i] != NULL) {
				fn_8015BBF8(lbl_8042C1D0->scene, object->meshes[i]);
				fn_80150958(object->meshes[i]);
				object->meshes[i] = NULL;
			}

			if (object->buffers[i] != NULL) {
				fn_80150958(object->buffers[i]);
				object->buffers[i] = NULL;
			}
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
