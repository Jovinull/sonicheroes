#include "types.h"

// TObjDashPanel's destructor. It restores both vtable pointers, releases the
// collision mesh it registered with the stage, frees the scroll buffer, runs the
// embedded base down and then the object base, and hands the object back to the
// heap when the caller asks for it.
//
// The claim is .text 0x7EB0 to 0x7F84 and nothing else. The vtable stays in each
// module's data and is renamed to the shared name below; it reads no constant,
// so it owns no rodata.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// Same shape as rel/set_collision_dtor.cpp, with two differences: it also frees
// a buffer through operator delete, and the world it unregisters the mesh from
// sits at a different offset in the same global.
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

typedef struct DashPanel {
	TObject base;   // 0x00
	Motion motion;  // 0x28
	u8 unk30[0x30]; // 0x30
	void* mesh;     // 0x60
	void* scroll;   // 0x64
} DashPanel;        // 0x68

extern "C" void* lbl_8042C148;
extern "C" u8* lbl_8042C1D0;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __dl__FPv(void* memory);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8015BBF8(void* world, void* mesh);
extern "C" void fn_80150958(void* mesh);

// Defined by each module, renamed to this name in its own symbols.txt.
extern "C" void* dashpanelVtable[];

extern "C" DashPanel* dashpanelDtor(DashPanel* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = dashpanelVtable;
		object->motion.vtable = dashpanelVtable + 0xB;

		if (object->mesh != NULL) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 29276), object->mesh);
			fn_80150958(object->mesh);
			object->mesh = NULL;
		}

		if (object->scroll != NULL) {
			__dl__FPv(object->scroll);
			object->scroll = NULL;
		}

		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
