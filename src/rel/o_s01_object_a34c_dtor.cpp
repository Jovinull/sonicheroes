#include "types.h"

// The destructor of the second object class in the translation unit that starts
// at 0x0007C9CC. It restores both vtable pointers, releases the handle it
// registered and the collision mesh it built, runs the embedded motion base
// down and then the object base, and hands the object back to the heap when the
// caller asks for it.
//
// The claim is .text 0x0007D0C8 to 0x0007D1A4 and nothing else. The vtable stays
// in the module's data and is renamed to the name below; the function reads no
// constant, so it owns no rodata.
//
// This is a different class from the one rel/o_s01_base.cpp reconstructs: that
// one installs the vtable at data 0xA1C8, this one the vtable at 0xA34C, and
// this one carries no volume: there is no dtor_8003C52C call and the fields at
// +0x34 and +0x38 sit where the other class has its volume. The two classes
// share the translation unit; 0xA34C is also reached by fn_3_7D1A4, which is
// this class's other method and is still assembly.
//
// The names are keyed to the vtable address and are provisional. The class name
// is not recoverable: __ct__7TObjectFP7TObject sets the name field and nothing
// here overwrites it, and no caller in the reconstructed sources reaches this
// class yet. Renaming is mechanical once it is identified, exactly as
// s01ObjA1C8* became s01ObjectBase* once its callers turned up.
//
// The mesh release is written out rather than shared with
// rel/o_s01_base_collision.cpp because the original inlines it here: the same
// three calls appear in the body instead of a branch to that unit's copy.
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

typedef struct S01ObjectA34C {
	TObject base;  // 0x00
	Motion motion; // 0x28
	u32 unk30;     // 0x30
	void* mesh;    // 0x34
	void* handle;  // 0x38
} S01ObjectA34C;   // 0x3C

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_8005FD8C(void* handle, s32 slot);
extern "C" void* fn_8015BD78(void* mesh);
extern "C" void fn_8015BBF8(void* scene, void* mesh);
extern "C" void fn_80150958(void* mesh);

// Defined by the module, renamed to this name in its own symbols.txt.
extern "C" void* s01ObjectA34CVtable[];

extern "C" S01ObjectA34C* s01ObjectA34CDtor(S01ObjectA34C* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = s01ObjectA34CVtable;
		object->motion.vtable = s01ObjectA34CVtable + 0xB;

		if (object->handle != NULL) {
			fn_8005FD8C(object->handle, -1);
			object->handle = NULL;
		}

		if (object->mesh != NULL) {
			fn_8015BBF8(fn_8015BD78(object->mesh), object->mesh);
			fn_80150958(object->mesh);
			object->mesh = NULL;
		}

		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
