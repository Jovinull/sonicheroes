#include "types.h"

// Drops the five models an object can be holding, unregistering each from the
// world it was added to before letting go of it, and TObjIronBall's destructor,
// which is the only caller that gets the loop inlined into it.
//
// The claim is .text 0x6E78 to 0x6FDC and the vtable each module keeps in its
// own data, renamed to the shared name below. Everything else it touches is a
// DOL symbol.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// The two live together because the destructor's copy of the release loop is
// the inlined one: the standalone function puts the index in the lower callee
// saved register and the cursor above it, and the copy inside the destructor
// has them the other way round. Only a call the compiler can see reproduces
// that, so splitting them into separate units does not match.
//
// The delete flag is a short. It is sign extended before the test, so a plain
// s32 parameter does not reproduce the compare.

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	void* scene;     // 0x725C
} World;

typedef struct Object {
	u8 unk0[0xE0];   // 0x00
	void* models[5]; // 0xE0
} Object;

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

typedef struct Ironball {
	TObject base;    // 0x00
	Motion motion;   // 0x28
	Volume volume;   // 0x30
	s32 mode;        // 0xB8
	f32 unkBC[9];    // 0xBC
	void* models[5]; // 0xE0
} Ironball;          // 0xF4

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_80150958(void* model);
extern "C" void fn_8015BBF8(void* scene, void* model);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* ironballVtable[];

extern "C" void objReleaseModels(Object* object)
{
	s32 i;

	for (i = 0; i < 5; i++) {
		if (object->models[i] != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->models[i]);
			fn_80150958(object->models[i]);
			object->models[i] = NULL;
		}
	}
}

extern "C" Ironball* ironballDtor(Ironball* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = ironballVtable;
		object->motion.vtable = ironballVtable + 0xB;

		objReleaseModels((Object*)object);

		dtor_8003C52C(&object->volume, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
